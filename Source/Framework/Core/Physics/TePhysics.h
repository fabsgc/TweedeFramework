#pragma once

#include "TeCorePrerequisites.h"
#include "Utility/TeModule.h"

namespace te
{
    class TE_CORE_EXPORT Physics: public Module<Physics>
    {
    public:
        virtual ~Physics() = default;
        virtual void Update() = 0;
    };

    /** Provides easier access to Physics. */
	TE_CORE_EXPORT Physics& gPhysics();
	TE_CORE_EXPORT Physics* gPhysicsPtr();
}