#pragma once

#include "TeOpenAudioPrerequisites.h"
#include "Audio/TeAudio.h"

namespace te
{
    class OpenAudio: public Audio
    {
    public:
        OpenAudio();
        ~OpenAudio();

        void Update() override;
    };
}