#include "TeFontImporterPrerequisites.h"
#include "TeFontImporter.h"

namespace te
{
	/**	Returns a name of the plugin. */
	extern "C" TE_PLUGIN_EXPORT const char* getPluginName()
	{
		static const char* pluginName = "FontImporter";
		return pluginName;
	}

	/**	Entry point to the plugin. Called by the engine when the plugin is loaded. */
	extern "C" TE_PLUGIN_EXPORT void* loadPlugin()
	{
		FontImporter* importer = te_new<FontImporter>();

		return nullptr;
	}
}