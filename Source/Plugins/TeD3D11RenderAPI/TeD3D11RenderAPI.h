#pragma once

#include "TeD3D11RenderAPIPrerequisites.h"
#include "RenderAPI/TeRenderAPI.h"

namespace te
{
    class D3D11RenderAPI: public RenderAPI
    {
    public:
        D3D11RenderAPI();
        ~D3D11RenderAPI();

        void Initialize() override;
        void Update() override;
    };
}