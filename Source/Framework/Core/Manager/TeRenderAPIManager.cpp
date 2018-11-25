#include "Manager/TeRenderAPIManager.h"
#include "RenderAPI/TeRenderAPI.h"
#include "RenderAPI/TeRenderAPIFactory.h"
#include "Utility/TeDynLib.h"
#include "Utility/TeDynLibManager.h"

namespace te
{
    void RenderAPIManager::Initialize(const String& pluginFilename, RENDER_WINDOW_DESC& primaryWindowDesc)
    {
        DynLib* loadedLibrary = gDynLibManager().Load(pluginFilename);
        const char* name = "";

        if (loadedLibrary != nullptr)
        {
            typedef const char* (*GetPluginNameFunc)();

            GetPluginNameFunc getPluginNameFunc = (GetPluginNameFunc)loadedLibrary->GetSymbol("GetPluginName");
            name = getPluginNameFunc();
        }

        for (auto iter = _availableFactories.begin(); iter != _availableFactories.end(); ++iter)
        {
            if ((*iter)->Name() == name)
            {
                SPtr<RenderAPI> newRenderAPI = (*iter)->Create();
                if (newRenderAPI != nullptr)
                {
                    if (_renderAPI != nullptr)
                        te_delete(&_renderAPI);

                    _renderAPI = newRenderAPI;
                }
            }
        }

        TE_ASSERT_ERROR(_renderAPI != nullptr, "Cannot initialize renderer. Renderer with the name '" + pluginFilename + "' cannot be found.");
    }

    void RenderAPIManager::RegisterFactory(SPtr<RenderAPIFactory> factory)
    {
        assert(factory != nullptr);

        _availableFactories.push_back(factory);
    }
}