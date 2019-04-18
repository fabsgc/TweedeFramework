#pragma once

#include "Prerequisites/TePrerequisitesUtility.h"
#include "Threading/TeThreading.h"
#include "Utility/TeUUID.h"

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
		 * @see		Resources::Release(ResourceHandleBase&)
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

    protected:
		/** 
		 * @note	
		 * All handles to the same source must share this same handle data. Otherwise things like counting number of 
		 * references or replacing pointed to resource become impossible without additional logic. */
		SPtr<ResourceHandleData> _data;

	private:
		friend class ResourceManager;

		static Signal _resourceCreatedCondition;
		static Mutex _resourceCreatedMutex;

	protected:
		void AbortIfNotLoaded() const;
	};

    template<typename T>
    class TE_CORE_EXPORT TResourceHandle : public ResourceHandleBase
    {
    public:
        TResourceHandle() = default;

        /**	Copy constructor. */
        TResourceHandle(const TResourceHandle& other)
        {
            this->_data = other.GetHandleData();
            this->AddRef();
        }

        /** Move constructor. */
        TResourceHandle(TResourceHandle&& other) = default;

        ~TResourceHandle()
        {
            this->ReleaseRef();
        }

        /**	Converts a specific handle to generic Resource handle. */
        operator TResourceHandle<Resource>() const
        {
            TResourceHandle<Resource> handle;
            handle.SetHandleData(this->GetHandleData());

            return handle;
        }

        /**
         * Returns internal resource pointer.
         *
         * @note	Throws exception if handle is invalid.
         */
        T* operator->() const { return get(); }

        /**
         * Returns internal resource pointer and dereferences it.
         *
         * @note	Throws exception if handle is invalid.
         */
        T& operator*() const { return *get(); }

        /** Clears the handle making it invalid and releases any references held to the resource. */
        TResourceHandle<T>& operator=(std::nullptr_t ptr)
        {
            this->ReleaseRef();
            this->_data = nullptr;

            return *this;
        }

        /**	Copy assignment. */
        TResourceHandle<T>& operator=(const TResourceHandle<T>& rhs)
        {
            SetHandleData(rhs.GetHandleData());
            return *this;
        }

        /**	Move assignment. */
        TResourceHandle& operator=(TResourceHandle&& other)
        {
            if (this == &other)
                return *this;

            this->ReleaseRef();
            this->_data = std::exchange(other._data, nullptr);

            return *this;
        }

        template<class _Ty>
        struct Bool_struct
        {
            int _member;
        };

        /**
         * Allows direct conversion of handle to bool.
         *
         * @note	This is needed because we can't directly convert to bool since then we can assign pointer to bool and
         *			that's weird.
         */
        operator int Bool_struct<T>::* () const
        {
            return ((this->_data != nullptr && !this->_data->_uuid.Empty()) ? &Bool_struct<T>::_member : 0);
        }

        /**
         * Returns internal resource pointer and dereferences it.
         *
         * @note	Throws exception if handle is invalid.
         */
        T* get() const
        {
            this->AbortIfNotLoaded();

            return reinterpret_cast<T*>(this->_data->_ptr.get());
        }

        /**
         * Returns the internal shared pointer to the resource.
         *
         * @note	Throws exception if handle is invalid.
         */
        SPtr<T> GetInternalPtr() const
        {
            this->AbortIfNotLoaded();

            return std::static_pointer_cast<T>(this->_data->_ptr);
        }

    protected:
        friend ResourceManager;
        template<class _Ty1, class _Ty2>
        friend TResourceHandle<_Ty1> static_resource_cast(const TResourceHandle<_Ty2>& other);

        void AddRef()
        {
            if (_data)
                _data->_refCount.fetch_add(1, std::memory_order_relaxed);
        };

        void ReleaseRef()
        {
            if (_data)
            {
                std::uint32_t refCount = _data->_refCount.fetch_sub(1, std::memory_order_release);

                if (refCount == 1)
                {
                    std::atomic_thread_fence(std::memory_order_acquire);
                    Destroy();
                }
            }
        };

        /**
         * Constructs a new valid handle for the provided resource with the provided UUID.
         *
         * @note	Handle will take ownership of the provided resource pointer, so make sure you don't delete it elsewhere.
         */
        explicit TResourceHandle(T* ptr, const UUID& uuid)
            : ResourceHandleBase()
        {
            this->_data = te_shared_ptr_new<ResourceHandleData>();
            this->AddRef();

            this->SetHandleData(SPtr<Resource>(ptr), uuid);
        }

        /**
         * Constructs an invalid handle with the specified UUID. You must call setHandleData() with the actual resource
         * pointer to make the handle valid.
         */
        TResourceHandle(const UUID& uuid)
        {
            this->_data = te_shared_ptr_new<ResourceHandleData>();
            this->_data->_uuid = uuid;

            this->AddRef();
        }

        /**	Constructs a new valid handle for the provided resource with the provided UUID. */
        TResourceHandle(const SPtr<T> ptr, const UUID& uuid)
        {
            this->_data = te_shared_ptr_new<ResourceHandleData>();
            this->AddRef();

            SetHandleData(ptr, uuid);
        }

        /**	Replaces the internal handle data pointer, effectively transforming the handle into a different handle. */
        void SetHandleData(const SPtr<ResourceHandleData>& data)
        {
            this->ReleaseRef();
            this->_data = data;
            this->AddRef();
        }

        using ResourceHandleBase::SetHandleData;
    };

    /**	Checks if two handles point to the same resource. */
    template<class _Ty1, class _Ty2>
    bool operator==(const TResourceHandle<_Ty1>& _Left, const TResourceHandle<_Ty2>& _Right)
    {
        if (_Left.GetHandleData() != nullptr && _Right.GetHandleData() != nullptr)
            return _Left.GetHandleData()->mPtr == _Right.GetHandleData()->mPtr;

        return _Left.GetHandleData() == _Right.GetHandleData();
    }

    /**	Checks if a handle is null. */
    template<class _Ty1, class _Ty2>
    bool operator==(const TResourceHandle<_Ty1>& _Left, std::nullptr_t  _Right)
    {
        return _Left.GetHandleData() == nullptr || _Left.GetHandleData()->mUUID.empty();
    }

    template<class _Ty1, class _Ty2>
    bool operator!=(const TResourceHandle<_Ty1>& _Left, const TResourceHandle<_Ty2>& _Right)
    {
        return (!(_Left == _Right));
    }

    /**	Casts one resource handle to another. */
    template<class _Ty1, class _Ty2>
    TResourceHandle<_Ty1> static_resource_cast(const TResourceHandle<_Ty2>& other)
    {
        TResourceHandle<_Ty1> handle;
        handle.SetHandleData(other.GetHandleData());

        return handle;
    }

    /** @copydoc ResourceHandleBase */
    template <typename T>
    using ResourceHandle = TResourceHandle<T>;
}