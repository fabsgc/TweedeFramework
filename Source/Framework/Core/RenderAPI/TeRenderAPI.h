#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
    class TE_CORE_EXPORT RenderAPI
    {
    public:
        RenderAPI();
        ~RenderAPI();

        void Initialize(const RENDER_WINDOW_DESC& _windowDesc);

        virtual void Initialize() = 0;
        virtual void Update() = 0;
    };
}