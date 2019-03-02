#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
	/**	Base class for all resources. */
	class TE_CORE_EXPORT Resource
	{
	public:
		Resource() = default;
		virtual ~Resource() = default;

        void SetName(const String& name);
        const String& GetName() const;

        bool AreDependenciesLoaded() const;

    protected:
        String _name;
    };
}