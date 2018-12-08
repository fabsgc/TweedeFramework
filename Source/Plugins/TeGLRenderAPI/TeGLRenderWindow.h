#pragma once

#include "TeGLRenderAPIPrerequisites.h"
#include "RenderAPI/TeRenderWindow.h"

namespace te
{
    class GLRenderWindow : public RenderWindow
	{
	public:
        GLRenderWindow(const RENDER_WINDOW_DESC& desc);
		~GLRenderWindow() = default;

        void Update() override;
        void Initialize() override;
        void GetCustomAttribute(const String& name, void* pData) const override;
    };
}