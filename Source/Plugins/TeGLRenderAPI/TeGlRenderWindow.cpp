#include "TeGLRenderWindow.h"

namespace te
{
    GLRenderWindow::GLRenderWindow(const RENDER_WINDOW_DESC& desc)
        : RenderWindow(desc)
    {
    }

    void GLRenderWindow::Update()
    {
    }

    void GLRenderWindow::Initialize()
    {
    }

    void GLRenderWindow::GetCustomAttribute(const String& name, void* pData) const
    {
        RenderWindow::GetCustomAttribute(name, pData);
    }
}