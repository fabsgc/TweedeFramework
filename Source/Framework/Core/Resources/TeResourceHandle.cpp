#include "TeCorePrerequisites.h"
#include "Resources/TeResourceHandle.h"
#include "Resources/TeResource.h"

namespace te
{
    Signal ResourceHandleBase::_resourceCreatedCondition;
	Mutex ResourceHandleBase::_resourceCreatedMutex;

    bool ResourceHandleBase::IsLoaded(bool checkDependencies) const
	{
		bool isLoaded = (_data != nullptr && _data->_isCreated && _data->_ptr != nullptr);

		if (checkDependencies && isLoaded)
			isLoaded = _data->_ptr->AreDependenciesLoaded();

		return isLoaded;
	}

    void ResourceHandleBase::BlockUntilLoaded(bool waitForDependencies) const
    {
        if (_data == nullptr)
            return;

        if (!_data->_isCreated)
        {
            Lock lock(_resourceCreatedMutex);
            while (!_data->_isCreated)
            {
                _resourceCreatedCondition.wait(lock);
            }

            // Send out ResourceListener events right away, as whatever called this method
            // probably also expects the listener events to trigger immediately as well
            //_resourceListenerManager::instance().notifyListeners(mData->mUUID);
            //TODO
        }

        if (waitForDependencies)
        {
            //TODO
        }
    }

    void ResourceHandleBase::Release()
    {
        //gResources().release(*this);
        //TODO
    }

    void ResourceHandleBase::Destroy()
    {
        //if (_data->_ptr)
        //    gResources().destroy(*this);
        //TODO
    }

    void ResourceHandleBase::SetHandleData(const SPtr<Resource> & ptr, const UUID & uuid)
    {
        _data->_ptr = ptr;

        if (_data->_ptr)
        {
            _data->_uuid = uuid;

            if (!_data->_isCreated)
            {
                Lock lock(_resourceCreatedMutex);
                {
                    _data->_isCreated = true;
                }

                _resourceCreatedCondition.notify_all();
            }
        }
    }

    void ResourceHandleBase::ClearHandleData()
    {
        _data->_ptr = nullptr;

        Lock lock(_resourceCreatedMutex);
        _data->_isCreated = false;
    }

    void ResourceHandleBase::AddInternalRef()
    {
        _data->_refCount.fetch_add(1, std::memory_order_relaxed);
    }

    void ResourceHandleBase::RemoveInternalRef()
    {
        _data->_refCount.fetch_sub(1, std::memory_order_relaxed);
    }

    void ResourceHandleBase::AbortIfNotLoaded() const
    {
#if TE_DEBUG_MODE
        if (!IsLoaded(false))
        {
            TE_ASSERT_ERROR(false, "Trying to access a resource that hasn't been loaded yet.");
        }
#endif
    }
}