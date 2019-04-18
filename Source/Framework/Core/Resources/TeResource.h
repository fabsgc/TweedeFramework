#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
	/**	Base class for all resources. */
	class TE_CORE_EXPORT Resource
	{
	public:
		Resource();
		virtual ~Resource() = default;

        /**	Sets the name of the resource.  */
        void SetName(const String& name);

        /**	Returns the name of the resource. */
        const String& GetName() const;

        /**	Retrieves meta-data containing various information describing a resource. */
        SPtr<ResourceMetaData> GetMetaData() const { return _metaData; }

        /**	Returns whether or not this resource is allowed to be asynchronously loaded. */
        virtual bool AllowAsyncLoading() const { return true; }

    protected:
        friend class Resources;
        friend class ResourceHandleBase;

        /**	Retrieves a list of all resources that this resource depends on. */
        virtual void GetResourceDependencies(Vector<HResource>& dependencies) const { }

        /**	Checks if all the resources this object is dependent on are fully loaded. */
        bool AreDependenciesLoaded() const;

    protected:
        UINT32 mSize;
		SPtr<ResourceMetaData> _metaData;

        /**
         * Signal to the resource implementation if original data should be kept in memory. This is sometimes needed if
         * the resource destroys original data during normal usage, but it might still be required for special purposes
         * (like saving in the editor).
         */
        bool _keepSourceData;
    };
}