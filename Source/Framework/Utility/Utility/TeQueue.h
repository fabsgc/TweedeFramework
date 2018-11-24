#pragma once

#include "Prerequisites/TePrerequisitesUtility.h"
#include "Threading/TeThreading.h"

namespace te
{
    template <typename T>
	class Queue
	{
	public:
		T Pop()
		{
            Lock lock(_mutex);
			while (_queue.empty())
			{
				_cond.wait(mlock);
			}

			auto item = _queue.front();
			_queue.pop();
			return item;
		}

		void Pop(T& item)
		{
            Lock lock(_mutex);
			while (_queue.empty())
			{
				_cond.wait(mlock);
			}

			item = _queue.front();
			_queue.pop();
		}

		void Push(const T& item)
		{
            Lock lock(_mutex);
			_queue.push(item);
			mlock.unlock();
			_cond.notify_one();
		}

		void Push(T&& item)
		{
            Lock lock(_mutex);
			_queue.push(std::move(item));
			mlock.unlock();
			_cond.notify_one();
		}

		size_t Size()
		{
            Lock lock(_mutex);
			return _queue.size();
		}

	private:
		Queue<T> _queue;
		Mutex _mutex;
		Signal _cond;
	};
}