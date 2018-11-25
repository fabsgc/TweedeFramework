#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
    class TE_CORE_EXPORT RenderAPI
    {
    public:
        RenderAPI();
        ~RenderAPI();

        virtual void Initialize() = 0;
        virtual void Update() = 0;
    };
}