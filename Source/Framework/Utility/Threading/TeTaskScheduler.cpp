#include "Threading/TeTaskScheduler.h"
#include "Threading/TeThreadPool.h"

namespace te
{
    Task::Task(const String& name, std::function<void()> taskWorker,
        TaskPriority priority, SPtr<Task> dependency)
        : _name(name)
        , _priority(priority)
        , _taskWorker(std::move(taskWorker))
        , _taskDependency(std::move(dependency))
    {

    }

    SPtr<Task> Task::Create(const String& name, std::function<void()> taskWorker, TaskPriority priority, SPtr<Task> dependency)
    {
        return te_shared_ptr_new<Task>(name, std::move(taskWorker), priority, std::move(dependency));
    }

    bool Task::IsComplete() const
    {
        return _state == Task::TaskCompleted;
    }

    bool Task::IsCanceled() const
    {
        return _state == Task::TaskCanceled;
    }

    void Task::Wait()
    {
        if (_parent != nullptr)
            _parent->WaitUntilComplete(this);
    }

    void Task::Cancel()
    {
        _state = Task::TaskCanceled;
    }

    TaskScheduler::TaskScheduler()
        : _taskQueue(&TaskScheduler::TaskCompare)
    {
        _maxActiveTasks = TE_THREAD_HARDWARE_CONCURRENCY;
        _taskSchedulerThread = ThreadPool::Instance().Run("TaskScheduler", std::bind(&TaskScheduler::RunMain, this));
    }

    TaskScheduler::~TaskScheduler()
    {
        // Wait until all tasks complete
        {
            Lock activeTaskLock(_readyMutex);

            while (_activeTasks.size() > 0)
            {
                SPtr<Task> task = _activeTasks[0];
                activeTaskLock.unlock();

                task->Wait();
                activeTaskLock.lock();
            }
        }

        // Start shutdown of the main queue worker and wait until it exits
        {
            Lock lock(_readyMutex);
            _shutdown = true;
        }

        _taskReadyCond.notify_one();
        _taskSchedulerThread->BlockUntilComplete();
    }

    void TaskScheduler::AddTask(SPtr<Task> task)
    {
        Lock lock(_readyMutex);

        assert(task->_state != Task::TaskInProgress && "Task is already executing, it cannot be executed again until it finishes.");

        task->_parent = this;
        task->_taskId = _nextTaskId++;
        task->_state.store(Task::TaskInactive); // Reset state in case the task is getting re-queued

        _checkTasks = true;
        _taskQueue.insert(std::move(task));

        // Wake main scheduler thread
        _taskReadyCond.notify_one();
    }

    void TaskScheduler::AddWorker()
    {
        Lock lock(_readyMutex);

        _maxActiveTasks++;

        // A spot freed up, queue new tasks on main scheduler thread if they exist
        _taskReadyCond.notify_one();
    }

    void TaskScheduler::RemoveWorker()
    {
        Lock lock(_readyMutex);

        if (_maxActiveTasks > 0)
            _maxActiveTasks--;
    }

    void TaskScheduler::RunMain()
    {
        while (true)
        {
            Lock lock(_readyMutex);

            while ((!_checkTasks || (UINT32)_activeTasks.size() >= _maxActiveTasks) && !_shutdown)
                _taskReadyCond.wait(lock);

            _checkTasks = false;

            if (_shutdown)
                break;

            for (auto iter = _taskQueue.begin(); iter != _taskQueue.end();)
            {
                if ((UINT32)_activeTasks.size() >= _maxActiveTasks)
                    break;

                SPtr<Task> curTask = *iter;

                if (curTask->IsCanceled())
                {
                    iter = _taskQueue.erase(iter);
                    continue;
                }

                if (curTask->_taskDependency != nullptr && !curTask->_taskDependency->IsComplete())
                {
                    ++iter;
                    continue;
                }

                iter = _taskQueue.erase(iter);

                curTask->_state.store(1);
                _activeTasks.push_back(curTask);

                ThreadPool::Instance().Run(curTask->_name, std::bind(&TaskScheduler::RunTask, this, curTask));
            }
        }
    }

    void TaskScheduler::RunTask(SPtr<Task> task)
    {
        task->_taskWorker();

        {
            Lock lock(_readyMutex);

            auto findIter = std::find(_activeTasks.begin(), _activeTasks.end(), task);
            if (findIter != _activeTasks.end())
                _activeTasks.erase(findIter);
        }

        {
            Lock lock(_completeMutex);
            task->_state.store(Task::TaskCompleted);

            _taskCompleteCond.notify_all();
        }

        // Wake the main scheduler thread in case there are other tasks waiting or this task was someone's dependency
        {
            Lock lock(_readyMutex);

            _checkTasks = true;
            _taskReadyCond.notify_one();
        }
    }

    void TaskScheduler::WaitUntilComplete(const Task* task)
    {
        if (task->IsCanceled())
            return;

        {
            Lock lock(_completeMutex);

            while (!task->IsComplete())
            {
                AddWorker();
                _taskCompleteCond.wait(lock);
                RemoveWorker();
            }
        }
    }

    bool TaskScheduler::TaskCompare(const SPtr<Task>& lhs, const SPtr<Task>& rhs)
    {
        // If one tasks priority is higher, that one goes first
        if (lhs->_priority > rhs->_priority)
            return true;

        // Otherwise we go by smaller id, as that task was queued earlier than the other
        return lhs->_taskId < rhs->_taskId;
    }
}