#pragma once

#include "TeCorePrerequisites.h"
#include "Resources/TeResource.h"
#include "Utility/TeUUID.h"
#include "Threading/TeThreading.h"

namespace te
{
    /**	Data that is shared between all resource handles. */
	struct TE_CORE_EXPORT ResourceHandleData
	{
		SPtr<Resource> _ptr;
		UUID _uuid;
		bool _isCreated = false;
		std::atomic<std::uint32_t> _refCount{0};
	};

    /**
	 * Represents a handle to a resource. Handles are similar to a smart pointers, but they have two advantages:
	 *	- When loading a resource asynchronously you can be immediately returned the handle that you may use throughout
	 *    the engine. The handle will be made valid as soon as the resource is loaded.
	 */
	class TE_CORE_EXPORT ResourceHandleBase
	{
	public:
		/**
		 * Checks if the resource is loaded. Until resource is loaded this handle is invalid and you may not get the 
		 * internal resource from it.
		 * @param[in]	checkDependencies	If true, and if resource has any dependencies, this method will also check if 
		 *									they are loaded.
		 */
		bool IsLoaded(bool checkDependencies = true) const;

		/**
		 * Blocks the current thread until the resource is fully loaded.		
		 * @note	Careful not to call this on the thread that does the loading.
		 */
		void BlockUntilLoaded(bool waitForDependencies = true) const;

		/**
		 * Releases an internal reference to this resource held by the resources system, if there is one.		
		 * @see		Resources::release(ResourceHandleBase&)
		 */
		void Release();

		/** Returns the UUID of the resource the handle is referring to. */
		const UUID& GetUUID() const { return _data != nullptr ? _data->_uuid : UUID::EMPTY; }

	public: // ***** INTERNAL ******
		
		/**	Gets the handle data. For internal use only. */
		const SPtr<ResourceHandleData>& GetHandleData() const { return _data; }

	protected:
		/**	Destroys the resource the handle is pointing to. */
		void Destroy();

		/**
		 * Sets the created flag to true and assigns the resource pointer. Called by the constructors, or if you 
		 * constructed just using a UUID, then you need to call this manually before you can access the resource from 
		 * this handle.
		 * 			
		 * @note	
		 * This is needed because two part construction is required due to  multithreaded nature of resource loading.
		 * @note
		 * Internal method.
		 */
		void SetHandleData(const SPtr<Resource>& ptr, const UUID& uuid);

		/**
		 * Clears the created flag and the resource pointer, making the handle invalid until the resource is loaded again
		 * and assigned through setHandleData().
		 */
		void ClearHandleData();

		/** Increments the reference count of the handle. Only to be used by Resources for keeping internal references. */
		void AddInternalRef();

		/** Decrements the reference count of the handle. Only to be used by Resources for keeping internal references. */
		void RemoveInternalRef();

		/** 
		 * @note	
		 * All handles to the same source must share this same handle data. Otherwise things like counting number of 
		 * references or replacing pointed to resource become impossible without additional logic. */
		SPtr<ResourceHandleData> _data;

	private:
		friend class Resources;

		static Signal _resourceCreatedCondition;
		static Mutex _resourceCreatedMutex;

	protected:
		void AbortIfNotLoaded() const;
	};
}