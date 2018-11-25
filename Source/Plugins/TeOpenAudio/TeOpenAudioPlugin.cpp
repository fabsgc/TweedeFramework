#include "TeOpenAudioPrerequisites.h"
#include "Audio/TeAudioFactory.h"
#include "Audio/TeAudio.h"
#include "TeOpenAudio.h"

namespace te
{
	class OpenAudioFactory : public AudioFactory
	{
	public:
		void StartUp() override
		{
			Audio::StartUp<OpenAudio>();
		}

		void ShutDown() override
		{
			Audio::ShutDown();
		}
	};

	/**	Returns a name of the plugin. */
	extern "C" TE_PLUGIN_EXPORT const char* GetPluginName()
	{
		static const char* pluginName = "OpenAudio";
		return pluginName;
	}

	/**	Entry point to the plugin. Called by the engine when the plugin is loaded. */
	extern "C" TE_PLUGIN_EXPORT OpenAudioFactory* LoadPlugin()
	{
		return te_new<OpenAudioFactory>();
	}

	/**	Exit point of the plugin. Called by the engine before the plugin is unloaded. */
	extern "C" TE_PLUGIN_EXPORT void UnloadPlugin(OpenAudioFactory* instance)
	{
		if(instance != nullptr)
        {
            te_delete(instance);
        }
	}
}