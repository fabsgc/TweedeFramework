#include "RenderAPI/TeRenderWindow.h"

namespace te
{
    RenderWindow::RenderWindow(const RENDER_WINDOW_DESC& desc)
        : _desc(desc)
    {
    }

    RenderWindow::~RenderWindow()
    {
    }

    void RenderWindow::GetCustomAttribute(const String& name, void* pData) const
    {
    }
}