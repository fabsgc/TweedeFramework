#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
    /** Creates and destroys a specific audio system implementation. */
	class TE_CORE_EXPORT AudioFactory
	{
	public:
        virtual ~AudioFactory();

		/** Initializes the audio system. */
		virtual void StartUp() = 0;

		/** Shuts down the audio system. */
		virtual void ShutDown() = 0;
	};

}