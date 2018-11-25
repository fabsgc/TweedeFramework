#pragma once

#include "Prerequisites/TePrerequisitesUtility.h"
#include "Threading/TeThreadPool.h"
#include "Utility/TeModule.h"

namespace te
{
    enum class TaskPriority
    {
        VeryLow = 98,
		Low = 99,
		Normal = 100,
		High = 101,
		VeryHigh = 102 
    };

    /**
	 * Represents a single task that may be queued in the TaskScheduler.
	 * @note	Thread safe.
	 */
	class TE_UTILITY_EXPORT Task
	{
    public:
        Task(const String& name, std::function<void()> taskWorker, TaskPriority priority, SPtr<Task> dependency);
        ~Task() = default;

        /**
         * Creates a new task. Task should be provided to TaskScheduler in order for it to start.
         *
         * @param[in]	name		Name you can use to more easily identify the task.
         * @param[in]	taskWorker	Worker method that does all of the work in the task.
         * @param[in]	priority  	(optional) Higher priority means the tasks will be executed sooner.
         * @param[in]	dependency	(optional) Task dependency if one exists. If provided the task will
         * 							not be executed until its dependency is complete.
         */
        static SPtr<Task> Create(const String& name, std::function<void()> taskWorker,
            TaskPriority priority = TaskPriority::Normal, SPtr<Task> dependency = nullptr);

        /** Returns true if the task has completed. */
        bool IsComplete() const;

        /**	Returns true if the task has been canceled. */
        bool IsCanceled() const;

        /**
         * Blocks the current thread until the task has completed.
         * @note	While waiting adds a new worker thread, so that the blocking threads core can be utilized.
         */
        void Wait();

        /** Cancels the task and removes it from the TaskSchedulers queue. */
        void Cancel();

    public:
        enum
        {
            TaskInactive = 0,
            TaskInProgress = 1,
            TaskCompleted = 2,
            TaskCanceled = 3
        };

    private:
        friend class TaskScheduler;

        String _name;
        TaskPriority _priority;
        UINT32 _taskId = 0;
        std::function<void()> _taskWorker;
        SPtr<Task> _taskDependency;
        std::atomic<UINT32> _state { Task::TaskInactive }; /**< 0 - Inactive, 1 - In progress, 2 - Completed, 3 - Canceled */

        TaskScheduler* _parent = nullptr;
    };

    /**
	 * Represents a task scheduler running on multiple threads. You may queue tasks on it from any thread and they will be
	 * executed in user specified order on any available thread.
	 * @note
	 * Thread safe.
	 * @note
	 * This type of task scheduler uses a global queue and is best used for coarse granularity of tasks. (Number of tasks
	 * in the order of hundreds. Higher number of tasks might require different queuing and locking mechanism, potentially
	 * at the cost of flexibility.)
	 * @note
	 * By default the task scheduler will create as many threads as there are physical CPU cores. You may add or remove
	 * threads using addWorker()/removeWorker() methods.
	 */
	class TE_UTILITY_EXPORT TaskScheduler : public Module<TaskScheduler>
	{
	public:
		TaskScheduler();
		~TaskScheduler();

        /** Queues a new task. */
        void AddTask(SPtr<Task> task);

        /**	Adds a new worker thread which will be used for executing queued tasks. */
        void AddWorker();

        /**	Removes a worker thread (as soon as its current task is finished). */
        void RemoveWorker();

        /** Returns the maximum available worker threads (maximum number of tasks that can be executed simultaneously). */
        UINT32 getNumWorkers() const { return _maxActiveTasks; }

    protected:
        /**	Main task scheduler method that dispatches tasks to other threads. */
        void RunMain();

        /**	Worker method that runs a single task. */
        void RunTask(SPtr<Task> task);

        /**	Blocks the calling thread until the specified task has completed. */
        void WaitUntilComplete(const Task* task);

        /**	Method used for sorting tasks. */
        static bool TaskCompare(const SPtr<Task>& lhs, const SPtr<Task>& rhs);

        void OnStartUp() override;

    protected:
        friend Task;

        PooledThread* _taskSchedulerThread;
        Set<SPtr<Task>, std::function<bool(const SPtr<Task>&, const SPtr<Task>&)>> _taskQueue;
        Vector<SPtr<Task>> _activeTasks;
        UINT32 _maxActiveTasks = 0;
        UINT32 _nextTaskId = 0;
        bool _shutdown = false;
        bool _checkTasks = false;

        Mutex _readyMutex;
        Mutex _completeMutex;
        Signal _taskReadyCond;
        Signal _taskCompleteCond;
    };

    /**	Provides easy access to CoreApplication. */
    TE_UTILITY_EXPORT TaskScheduler& gTaskScheduler();
    TE_UTILITY_EXPORT TaskScheduler* gTaskSchedulerPtr();
}