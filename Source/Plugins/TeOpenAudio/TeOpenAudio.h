#pragma once

#include "TeOpenAudioPrerequisites.h"
#include "Audio/TeAudio.h"

namespace te
{
    class TE_PLUGIN_EXPORT OpenAudio: public Audio
    {
    public:
        OpenAudio();
        ~OpenAudio();
    };
}