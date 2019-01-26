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
    };
}