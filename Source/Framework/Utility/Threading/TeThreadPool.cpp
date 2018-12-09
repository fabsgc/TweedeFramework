#include "Threading/TeThreadPool.h"

#if TE_PLATFORM == TE_PLATFORM_WIN32
#include "windows.h"

#if TE_COMPILER == TE_COMPILER_MSVC
// disable: nonstandard extension used: 'X' uses SEH and 'Y' has destructor
// We don't care about this as any exception is meant to crash the program.
#pragma warning(disable: 4509)
#endif // TE_COMPILER == TE_COMPILER_MSVC

#endif // TE_PLATFORM == TE_PLATFORM_WIN32

namespace te
{
    static constexpr int UNUSED_CHECK_PERIOD = 32;

    HThread::HThread(ThreadPool* pool, UINT32 threadId)
        : _threadId(threadId), _pool(pool)
    { }

    void HThread::BlockUntilComplete()
    {
        PooledThread* parentThread = nullptr;

        {
            Lock lock(_pool->_mutex);

            for (auto& thread : _pool->_threads)
            {
                if (thread->GetId() == _threadId)
                {
                    parentThread = thread;
                    break;
                }
            }
        }

        if (parentThread != nullptr)
        {
            Lock lock(parentThread->_mutex);

            if (parentThread->_id == _threadId) // Check again in case it changed
            {
                while (!parentThread->_idle)
                    parentThread->_workerEndedCond.wait(lock);
            }
        }
    }

    void PooledThread::Initialize()
    {
        _thread = te_new<Thread>(std::bind(&PooledThread::Run, this));

        Lock lock(_mutex);

        while (!_threadStarted)
            _startedCond.wait(lock, [&]() { return _threadStarted; });
    }

    void PooledThread::Start(std::function<void()> workerMethod, UINT32 id)
    {
        {
            Lock lock(_mutex);

            _workerMethod = workerMethod;
            _idle = false;
            _idleTime = std::time(nullptr);
            _threadReady = true;
            _id = id;
        }

        _readyCond.notify_one();
    }

    void PooledThread::Run()
    {
        OnThreadStarted(_name);

        {
            Lock lock(_mutex);
            _threadStarted = true;
        }

        _startedCond.notify_one();

        while (true)
        {
            std::function<void()> worker = nullptr;

            {
                {
                    Lock lock(_mutex);

                    while (!_threadReady)
                        _readyCond.wait(lock, [&]() { return _threadReady; });

                    worker = _workerMethod;
                }

                if (worker == nullptr)
                {
                    OnThreadEnded(_name);
                    return;
                }
            }

            worker();

            {
                Lock lock(_mutex);

                _idle = true;
                _idleTime = std::time(nullptr);
                _threadReady = false;
                _workerMethod = nullptr; // Make sure to clear as it could have bound shared pointers and similar

                _workerEndedCond.notify_one();
            }
        }
    }

    void PooledThread::Destroy()
    {
        BlockUntilComplete();

        {
            Lock lock(_mutex);
            _workerMethod = nullptr;
            _threadReady = true;
        }

        _readyCond.notify_one();
        _thread->join();
        te_delete(_thread);
    }

    void PooledThread::BlockUntilComplete()
    {
        Lock lock(_mutex);

        while (!_idle)
            _workerEndedCond.wait(lock);
    }

    void PooledThread::OnThreadStarted(const String& name)
    {
        return;
    }

    void PooledThread::OnThreadEnded(const String& name)
    {
        return;
    }

    bool PooledThread::IsIdle()
    {
        Lock lock(_mutex);

        return _idle;
    }

    time_t PooledThread::IdleTime()
    {
        Lock lock(_mutex);

        return (time(nullptr) - _idleTime);
    }

    void PooledThread::SetName(const String& name)
    {
        _name = name;
    }

    UINT32 PooledThread::GetId() const
    {
        Lock lock(_mutex);

        return _id;
    }

    ThreadPool::ThreadPool(UINT32 threadCapacity, UINT32 maxCapacity, UINT32 idleTimeout)
        : _defaultCapacity(threadCapacity)
        , _maxCapacity(maxCapacity)
        , _idleTimeout(idleTimeout)
    {

    }

    ThreadPool::~ThreadPool()
    {
        StopAll();
    }

    HThread ThreadPool::Run(const String& name, std::function<void()> workerMethod)
    {
        PooledThread* thread = GetThread(name);
        thread->Start(workerMethod, _uniqueId++);

        return HThread(this, thread->GetId());
    }

    void ThreadPool::StopAll()
    {
        Lock lock(_mutex);
        for (auto& thread : _threads)
        {
            DestroyThread(thread);
        }

        _threads.clear();
    }

    void ThreadPool::ClearUnused()
    {
        Lock lock(_mutex);
        _age = 0;

        if (_threads.size() <= _defaultCapacity)
            return;

        Vector<PooledThread*> idleThreads;
        Vector<PooledThread*> expiredThreads;
        Vector<PooledThread*> activeThreads;

        idleThreads.reserve(_threads.size());
        expiredThreads.reserve(_threads.size());
        activeThreads.reserve(_threads.size());

        for (auto& thread : _threads)
        {
            if (thread->IsIdle())
            {
                if (thread->IdleTime() >= _idleTimeout)
                    expiredThreads.push_back(thread);
                else
                    idleThreads.push_back(thread);
            }
            else
            {
                activeThreads.push_back(thread);
            }
        }

        idleThreads.insert(idleThreads.end(), expiredThreads.begin(), expiredThreads.end());
        UINT32 limit = std::min((UINT32)idleThreads.size(), _defaultCapacity);

        UINT32 i = 0;
        _threads.clear();

        for (auto& thread : idleThreads)
        {
            if (i < limit)
            {
                _threads.push_back(thread);
                i++;
            }
            else
                DestroyThread(thread);
        }

        _threads.insert(_threads.end(), activeThreads.begin(), activeThreads.end());
    }

    PooledThread* ThreadPool::CreateThread(const String& name)
    {
        PooledThread* newThread = te_new<PooledThread>(name);
        newThread->Initialize();

        return newThread;
    }

    void ThreadPool::DestroyThread(PooledThread* thread)
    {
        thread->Destroy();
        te_delete(thread);
    }

    PooledThread* ThreadPool::GetThread(const String& name)
    {
        UINT32 age = 0;
        {
            Lock lock(_mutex);
            age = ++_age;
        }

        if (age == UNUSED_CHECK_PERIOD)
            ClearUnused();

        Lock lock(_mutex);

        for (auto& thread : _threads)
        {
            if (thread->IsIdle())
            {
                thread->SetName(name);
                return thread;
            }
        }

        TE_ASSERT_ERROR(_threads.size() < _maxCapacity, "Unable to create a new thread in the pool because maximum capacity has been reached.");

        PooledThread* newThread = CreateThread(name);
        _threads.push_back(newThread);

        return newThread;
    }

    UINT32 ThreadPool::GetNumAvailable() const
    {
        UINT32 numAvailable = 0;

        Lock lock(_mutex);
        for (auto& thread : _threads)
        {
            if (thread->IsIdle())
                numAvailable++;
        }

        return numAvailable;
    }

    UINT32 ThreadPool::GetNumActive() const
    {
        UINT32 numActive = 0;

        Lock lock(_mutex);
        for (auto& thread : _threads)
        {
            if (!thread->IsIdle())
                numActive++;
        }

        return numActive;
    }

    UINT32 ThreadPool::GetNumAllocated() const
    {
        Lock lock(_mutex);

        return (UINT32)_threads.size();
    }
}