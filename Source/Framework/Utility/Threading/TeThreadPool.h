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
        PooledThread(const String& name)
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
        virtual void OnThreadStarted(const String& name) = 0;

        /**	Called when the thread is being shut down. */
        virtual void OnThreadEnded(const String& name) = 0;

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

    protected:


    protected:
        
    };
}