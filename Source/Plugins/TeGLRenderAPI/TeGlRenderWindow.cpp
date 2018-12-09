#include "TeGLRenderWindow.h"

namespace te
{
    GLRenderWindow::GLRenderWindow(const RENDER_WINDOW_DESC& desc)
        : RenderWindow(desc)
        , _properties(desc)
    {
    }

    void GLRenderWindow::Destroy()
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