#pragma once

#include "TeGLRenderAPIPrerequisites.h"
#include "RenderAPI/TeRenderAPI.h"

namespace te
{
    class TE_PLUGIN_EXPORT GLRenderAPI: public RenderAPI
    {
    public:
        GLRenderAPI();
        ~GLRenderAPI();
    };
}