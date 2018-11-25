#pragma once

#include "Prerequisites/TePrerequisitesUtility.h"
#include "Utility/TeModule.h"
#include "Threading/TeThreading.h"

namespace te
{
    /**	Wrapper around a thread that is used within ThreadPool. */
	class TE_UTILITY_EXPORT PooledThread
	{
    public:
        PooledThread(const String& name = "task")
            :_name(name)
        { }

        ~PooledThread() = default;

        /**	Initializes the pooled thread. Must be called right after the object is constructed. */
        void Initialize();

        /**
         * Starts executing the given worker method.
         *
         * @note
         * Caller must ensure worker method is not null and that the thread is currently idle, otherwise undefined behavior
         * will occur.
         */
        void Start(std::function<void()> workerMethod, UINT32 id);

        /**
         * Attempts to join the currently running thread and destroys it. Caller must ensure that any worker method
         * currently running properly returns, otherwise this will block indefinitely.
         */
        void Destroy();

        /**	Returns true if the thread is idle and new worker method can be scheduled on it. */
        bool IsIdle();

        /** Returns how long has the thread been idle. Value is undefined if thread is not idle. */
        time_t IdleTime();

        /**	Sets a name of the thread. */
        void SetName(const String& name);

        /**	Gets unique ID of the currently executing thread. */
        UINT32 GetId() const;

        /**	Blocks the current thread until this thread completes. Returns immediately if the thread is idle. */
        void BlockUntilComplete();

        /**	Called when the thread is first created. */
        virtual void OnThreadStarted(const String& name);

        /**	Called when the thread is being shut down. */
        virtual void OnThreadEnded(const String& name);

    protected:
        void Run();

    protected:
        std::function<void()> _workerMethod;
        String _name;
        UINT32 _id = 0;
        bool _idle = true;
        bool _threadStarted = false;
        bool _threadReady = false;

        time_t _idleTime = 0;

        Thread* _thread;
        mutable Mutex _mutex;
        Signal _startedCond;
        Signal _readyCond;
        Signal _workerEndedCond;
    };

    /**
	 * Class that maintains a pool of threads we can easily retrieve and use for any task. This saves on the cost of
	 * creating and destroying threads.
	 */
	class TE_UTILITY_EXPORT ThreadPool : public Module<ThreadPool>
	{
	public:
        /**
         * Constructs a new thread pool
         *
         * @param[in]	threadCapacity	Default thread capacity, the pool will always try to keep this many threads available.
         * @param[in]	maxCapacity   	(optional) Maximum number of threads the pool can create.
         * @param[in]	idleTimeout   	(optional) How many seconds do threads need to be idle before we remove them from the pool.
         */
        ThreadPool(UINT32 threadCapacity = TE_THREAD_HARDWARE_CONCURRENCY, UINT32 maxCapacity = 16, UINT32 idleTimeout = 60);
        ~ThreadPool();

        /**
         * Find an unused thread (or creates a new one) and runs the specified worker method on it.
         *
         * @param[in]	name			A name you may use for more easily identifying the thread.
         * @param[in]	workerMethod	The worker method to be called by the thread.
         * @return						A thread
         */
        PooledThread* Run(const String& name, std::function<void()> workerMethod);

    protected:
        /**	Creates a new thread to be used by the pool. */
        PooledThread* CreateThread(const String& name);

        /**	Destroys the specified thread. Caller needs to make sure the thread is actually shut down beforehand. */
        void DestroyThread(PooledThread* thread);

        /**
         * Returns the first unused thread if one exists, otherwise creates a new one.
         * @param[in]	name	Name to assign the thread.
         * @note	Throws an exception if we have reached our maximum thread capacity.
         */
        PooledThread* GetThread(const String& name);

        /**
         * Stops all threads and destroys them. Caller must ensure each threads worker method returns otherwise this will
         * never return.
         */
        void StopAll();

        /** Clear any unused threads that are over the capacity. */
        void ClearUnused();

        /**	Returns the number of unused threads in the pool. */
        UINT32 GetNumAvailable() const;

        /**	Returns the number of running threads in the pool. */
        UINT32 GetNumActive() const;

        /**	Returns the total number of created threads in the pool	(both running and unused). */
        UINT32 GetNumAllocated() const;

    protected:
        Vector<PooledThread*> _threads;

        UINT32 _defaultCapacity;
        UINT32 _maxCapacity;
        UINT32 _idleTimeout;
        UINT32 _age = 0;

        std::atomic_uint _uniqueId;
        mutable Mutex _mutex;

    };
}