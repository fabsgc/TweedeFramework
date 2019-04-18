#include "Resources/TeResourceManager.h"
#include "Resources/TeResource.h"
#include "Threading/TeTaskScheduler.h"
#include "Utility/TeUUID.h"
#include "Utility/TeUtility.h"

namespace te
{
	ResourceManager::ResourceManager()
	{
	}

	ResourceManager::~ResourceManager()
	{
	}

    HResource ResourceManager::Load(const String& filePath, ResourceLoadFlag loadFlags)
    {
        HResource resource;
        return resource;
    }
}