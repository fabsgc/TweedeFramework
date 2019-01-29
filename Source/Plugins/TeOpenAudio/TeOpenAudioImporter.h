#pragma once

#include "TeOpenAudioPrerequisites.h"
#include "Importer/TeBaseImporter.h"

namespace te
{
    class OpenAudioImporter: public BaseImporter
    {
    public:
        OpenAudioImporter();
        ~OpenAudioImporter();
    };
}