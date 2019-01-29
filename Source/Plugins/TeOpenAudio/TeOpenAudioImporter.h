#pragma once

#include "TeObjectPrerequisites.h"
#include "Importer/BaseImporter.h"

namespace te
{
    class OpenAudioImporter: public BaseImporter
    {
    public:
        OpenAudioImporter();
        ~OpenAudioImporter();
    };
}