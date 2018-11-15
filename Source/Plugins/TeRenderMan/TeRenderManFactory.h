#pragma once

#include "TeRenderManPrerequisites.h"
#include "Renderer/TeRendererFactory.h"

namespace te
{
    class RenderManFactory : public RendererFactory
    {
    public:
        static constexpr const char* SystemName = "TeRenderMan";

        SPtr<Renderer> create() override;

        const String& name() const override;
    };
}