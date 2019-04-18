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
        LoadDependencies = 1,
        /**
            * If enabled the resource system will keep an internal reference to the resource so it doesn't get destroyed when
            * it goes out of scope. You can call Resources::release() to release the internal reference. Each call to load will
            * create a new internal reference and therefore must be followed by the same number of release calls. If
            * dependencies are being loaded, they will not have internal references created regardless of this parameter.
            */
        KeepInternalRef = 2,
        /**
            * Determines if the loaded resource keeps original data loaded. Sometime resources will process loaded data
            * and discard the original (e.g. uncompressing audio on load). This flag can prevent the resource from discarding
            * the original data. The original data might be required for saving the resource (via Resources::save), but will
            * use up extra memory. Normally you want to keep this enabled if you plan on saving the resource to disk.
            */
        KeepSourceData = 3
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