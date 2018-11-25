#pragma once

#include "TeGLRenderAPIPrerequisites.h"
#include "RenderAPI/TeRenderAPI.h"

namespace te
{
    class GLRenderAPI: public RenderAPI
    {
    public:
        GLRenderAPI();
        ~GLRenderAPI();

        void Initialize() override;
        void Update() override;
    };
}