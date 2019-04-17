#pragma once

#include "TeCorePrerequisites.h"
#include "Utility/TeModule.h"

namespace te
{
    /**
	 * Manager for dealing with all engine resources. It allows you to save new resources and load existing ones.
	 */
	class TE_CORE_EXPORT Resources: public Module<Resources>
	{
    public:
		Resources();
		~Resources();
    };
}