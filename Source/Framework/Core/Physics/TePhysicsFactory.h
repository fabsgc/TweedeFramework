#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
    /** Creates and destroys a specific audio system implementation. */
	class TE_CORE_EXPORT PhysicsFactory
	{
	public:
        virtual ~PhysicsFactory();

		/** Initializes the physics system. */
		virtual void StartUp() = 0;

		/** Shuts down the physics system. */
		virtual void ShutDown() = 0;
	};

}