#pragma once

#include "TeFontImporterPrerequisites.h"
#include "Importer/BaseImporter.h"

namespace te
{
    class TE_PLUGIN_EXPORT FontImporter: public BaseImporter
    {
    public:
        FontImporter();
        ~FontImporter();
    };
}