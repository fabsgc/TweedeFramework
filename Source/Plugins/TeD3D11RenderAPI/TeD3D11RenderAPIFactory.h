#pragma once

#include "TeD3D11RenderAPIPrerequisites.h"
#include "RenderAPI/TeRenderAPIFactory.h"

namespace te
{
    class D3D11RenderAPIFactory : public RenderAPIFactory
    {
    public:
        static constexpr const char* SystemName = "TeD3D11RenderAPI";

        SPtr<RenderAPI> create() override;

        const String& name() const override;
    };
}