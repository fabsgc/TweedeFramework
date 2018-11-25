#pragma once

#include "TeCorePrerequisites.h"
#include "Utility/TeModule.h"
#include "RenderAPI/TeRenderAPI.h"
#include "RenderAPI/TeRenderAPIFactory.h"

namespace te
{
     /** Manager that handles render system start up. */
    class TE_CORE_EXPORT RenderAPIManager : public Module<RenderAPIManager>
    {
    public:
        /**
         * Starts the render API with the provided name and creates the primary render window.
         *
         * @param[in]	name				Name of the render system to start. Factory for this render system must be
         *									previously registered.
         * @param[in]	primaryWindowDesc	Contains options used for creating the primary window.
         */
        void Initialize(const String& name, const RENDER_WINDOW_DESC& windowDesc);

        /**	Registers a new render API factory responsible for creating a specific render system type. */
        void RegisterFactory(SPtr<RenderAPIFactory> factory);

        /**	Returns the current renderer. Null if no renderer is active. */
        SPtr<RenderAPI> GetRenderAPI() { return _renderAPI; }
    private:
        Vector<SPtr<RenderAPIFactory>> _availableFactories;
        SPtr<RenderAPI> _renderAPI;
    };

    /** @} */
}
