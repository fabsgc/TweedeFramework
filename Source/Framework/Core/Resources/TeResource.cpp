#include "Resources/TeResource.h"
#include "Resources/TeResourceMetaData.h"

namespace te
{
	Resource::Resource()
		: mSize(0)
        , _keepSourceData(true)
	{ 
		_metaData = te_shared_ptr_new<ResourceMetaData>();
	}

	const String& Resource::GetName() const 
	{ 
		return _metaData->DisplayName; 
	}

	void Resource::SetName(const String& name) 
	{ 
		_metaData->DisplayName = name; 
	}

	bool Resource::AreDependenciesLoaded() const
	{
		bool areLoaded = true;
		{
			Vector<HResource> dependencies;
			GetResourceDependencies(dependencies);

			for (auto& dependency : dependencies)
			{
				if (dependency != nullptr && !dependency.IsLoaded())
				{
					areLoaded = false;
					break;
				}
			}
		}

		return areLoaded;
	}
}