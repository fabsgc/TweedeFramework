#pragma once

#include "Prerequisites/TePrerequisitesUtility.h"
#include "Threading/TeThreading.h"

namespace te
{
    /** 
	 * Locks access to files on the same drive, allowing only one file to be read at a time, per drive. This prevents
	 * multiple threads accessing multiple files on the same drive at once, ruining performance on mechanical drives.
	 */
	class TE_UTILITY_EXPORT FileLocker final
	{
	public:
		/** 
		 * Locks access and doesn't allow other threads to get past this point until access is unlocked. Any scheduled
		 * file access should happen past this point.
		 */
		static void Acquire()
		{
			// Note: File path should be analyzed and determined on which drive does the path belong to. Locks can then
			// be issued on a per-drive basis, instead of having one global lock. This would allow multiple files to be
			// accessed at the same time, as long as they're on different drives.
			_mutex.lock();
		}

		/** 
		 * Unlocks access and allows another thread to lock file access. Must be provided with the same file path as
		 * lock().
		 */
		static void Unlock()
		{
			_mutex.unlock();
		}

		/**
		 * Returns a lock object that immediately locks access (same as lock()), and then calls unlock() when it goes
		 * out of scope.
		 */
		static Lock GetLock()
		{
			return Lock(_mutex);
		}

	private:
		static Mutex _mutex;
	};
}