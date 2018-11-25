#include "TeBulletPrerequisites.h"
#include "Physics/TePhysicsFactory.h"
#include "Physics/TePhysics.h"
#include "TeBullet.h"

namespace te
{
	class BulletFactory : public PhysicsFactory
	{
	public:
		void StartUp() override
		{
			Physics::StartUp<Bullet>();
		}

		void ShutDown() override
		{
			Physics::ShutDown();
		}
	};

	/**	Returns a name of the plugin. */
	extern "C" TE_PLUGIN_EXPORT const char* GetPluginName()
	{
		static const char* pluginName = "Bullet";
		return pluginName;
	}

	/**	Entry point to the plugin. Called by the engine when the plugin is loaded. */
	extern "C" TE_PLUGIN_EXPORT BulletFactory* LoadPlugin()
	{
		return te_new<BulletFactory>();
	}

	/**	Exit point of the plugin. Called by the engine before the plugin is unloaded. */
	extern "C" TE_PLUGIN_EXPORT void UnloadPlugin(BulletFactory* instance)
	{
		if(instance != nullptr)
        {
            te_delete(instance);
        }
	}
}