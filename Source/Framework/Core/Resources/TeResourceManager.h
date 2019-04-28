#pragma once

#include "TeCorePrerequisites.h"
#include "Utility/TeModule.h"

namespace te
{
    /** Flags that can be used to control resource loading. */
    enum class ResourceLoadFlag
    {
        /** No flags. */
        None = 0,
        /** If enabled all resources referenced by the root resource will be loaded as well. */
        LoadDependencies = 1
    };

    /**
	 * Manager for dealing with all engine resources. It allows you to save new resources and load existing ones.
	 */
	class TE_CORE_EXPORT ResourceManager: public Module<ResourceManager>
	{
    public:
		ResourceManager();
		~ResourceManager();

        /**
         * Loads the resource from a given path. Returns an empty handle if resource can't be loaded. Resource is loaded
         * synchronously.
         *
         * @param[in]	filePath	File path to the resource to load. This can be absolute or relative to the working folder.
         * @param[in]	loadFlags	Flags used to control the load process.
         */
        HResource Load(const String& filePath, ResourceLoadFlag loadFlags = ResourceLoadFlag::None);
    };
}