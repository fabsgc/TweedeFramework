#pragma once

#include "TeObjectImporterPrerequisites.h"
#include "Importer/TeBaseImporter.h"

namespace te
{
    class ObjectImporter: public BaseImporter
    {
    public:
        ObjectImporter();
        ~ObjectImporter();
    };
}