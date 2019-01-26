#pragma once

#include "TeCorePrerequisites.h"
#include "Importer/TeImportOptions.h"

namespace te
{
	/** Contains import options you may use to control how is a texture imported. */
	class TE_CORE_EXPORT TextureImportOptions : public ImportOptions
	{
	public:
		TextureImportOptions() = default;
    };
}