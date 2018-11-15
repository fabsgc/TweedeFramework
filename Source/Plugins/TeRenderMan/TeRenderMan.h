#pragma once

#include "TeRenderManPrerequisites.h"
#include "Renderer/TeRenderer.h"

namespace te
{
    class TE_PLUGIN_EXPORT RenderMan: public Renderer
    {
    public:
        RenderMan();
        ~RenderMan();
    };
}