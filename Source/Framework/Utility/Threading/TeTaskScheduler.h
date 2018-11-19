#pragma once

#include "Prerequisites/TePrerequisitesUtility.h"
#include "Utility/TeModule.h"

namespace te
{
    enum class TastPriority
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
        Task() {}
        ~Task() = default;
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
		TaskScheduler() {};
		~TaskScheduler() = default;
    };
}