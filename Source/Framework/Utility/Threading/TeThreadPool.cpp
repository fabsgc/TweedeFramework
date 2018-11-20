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
            _workerEndedCond.wait(lock, [&]() { return _threadReady; });
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
}