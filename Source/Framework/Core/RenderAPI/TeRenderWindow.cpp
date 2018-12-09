#include "RenderAPI/TeRenderWindow.h"

namespace te
{
    RenderWindowProperties::RenderWindowProperties(const RENDER_WINDOW_DESC& desc)
    {
        Width = desc.Mode.GetWidth();
        Height = desc.Mode.GetHeight();
        Vsync = desc.Vsync;
        MultisampleCount = desc.MultisampleCount;
        Left = desc.Left;
        Top = desc.Top;
        IsFullScreen = desc.Fullscreen;
        IsHidden = desc.Hidden;
        RequiresTextureFlipping = false;
    }

    RenderWindow::RenderWindow(const RENDER_WINDOW_DESC& desc)
        : _desc(desc)
        , _properties(desc)
    {
    }

    RenderWindow::~RenderWindow()
    {
    }

    void RenderWindow::GetCustomAttribute(const String& name, void* pData) const
    {
    }
}