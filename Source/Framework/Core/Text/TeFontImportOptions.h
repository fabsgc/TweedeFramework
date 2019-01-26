#pragma once

#include "TeCorePrerequisites.h"
#include "Importer/TeImportOptions.h"
#include "Text/TeFont.h"

namespace te
{
	/**	Determines how is a font rendered into the bitmap texture. */
	enum class FontRenderMode
	{
		Smooth, /*< Render antialiased fonts without hinting (slightly more blurry). */
		Raster, /*< Render non-antialiased fonts without hinting (slightly more blurry). */
		HintedSmooth, /*< Render antialiased fonts with hinting. */
		HintedRaster /*< Render non-antialiased fonts with hinting. */
	};

	/**	Import options that allow you to control how is a font imported. */
	class TE_CORE_EXPORT FontImportOptions : public ImportOptions
	{
	public:
		FontImportOptions() = default;
    };
}