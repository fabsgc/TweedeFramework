#pragma once

#include "TeObjectImporterPrerequisites.h"
#include "Importer/BaseImporter.h"

namespace te
{
    class ObjectImporter: public BaseImporter
    {
    public:
        ObjectImporter();
        ~ObjectImporter();
    };
}