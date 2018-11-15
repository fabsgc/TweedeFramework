#pragma once

#include "TeCorePrerequisites.h"
#include "Utility/TeModule.h"

namespace te
{
    class TE_CORE_EXPORT Audio: public Module<Audio>
    {
    public:
        virtual ~Audio() = default;
    };

    /** Provides easier access to Audio. */
	TE_CORE_EXPORT Audio& gAudio();
	TE_CORE_EXPORT Audio* gAudioPtr();
}