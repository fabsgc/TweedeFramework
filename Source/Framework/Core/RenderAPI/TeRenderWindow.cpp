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
        //NOT IMPLEMENTED
    }

    void RenderWindow::Resize(UINT32 width, UINT32 height)
    {
        //TODO
    }

    void RenderWindow::SetHidden(bool hidden)
    {
        //TODO
    }

    void RenderWindow::SetActive(bool state)
    {
        //TODO
    }

    void RenderWindow::Move(INT32 left, INT32 top)
    {
        //TODO
    }

    void RenderWindow::Hide()
    {
        //TODO
    }

    void RenderWindow::Show()
    {
        //TODO
    }

    void RenderWindow::Minimize()
    {
        //TODO
    }

    void RenderWindow::Maximize()
    {
        //TODO
    }

    void RenderWindow::Restore()
    {
        //TODO
    }

    void RenderWindow::SetFullscreen(UINT32 width, UINT32 height, float refreshRate, UINT32 monitorIdx)
    {
        //TODO
    }

    void RenderWindow::SetFullscreen(const VideoMode& videoMode)
    {
        //TODO
    }

    void RenderWindow::SetWindowed(UINT32 width, UINT32 height)
    {
        //TODO
    }

    void RenderWindow::Destroy()
    {
        NotifyCloseRequested();
    }

    void RenderWindow::NotifyWindowEvent(WindowEventType type)
    {
        //TODO

        const RenderWindowProperties& props = GetRenderWindowProperties();

        switch (type)
        {
            case WindowEventType::Resized:
            {
                std::cout << "Event resized" << std::endl;

                WindowMovedOrResized();
                NotifyMovedOrResized();
                
                break;
            }
            case WindowEventType::Moved:
            {
                std::cout << "Event moved" << std::endl;
                break;
            }
            case WindowEventType::FocusReceived:
            {
                std::cout << "Event focus received" << std::endl;
                break;
            }
            case WindowEventType::FocusLost:
            {
                std::cout << "Event fosuc lost" << std::endl;
                break;
            }
            case WindowEventType::Minimized:
            {
                std::cout << "Event minimized" << std::endl;
                break;
            }
            case WindowEventType::Maximized:
            {
                std::cout << "Event maximized" << std::endl;
                break;
            }
            case WindowEventType::Restored:
            {
                std::cout << "Event restored" << std::endl;
                break;
            }
            case WindowEventType::MouseLeft:
            {
                std::cout << "Event mouse left" << std::endl;
                break;
            }
            case WindowEventType::CloseRequested:
            {
                std::cout << "Event close requested" << std::endl;
                break;
            }
        }
    }

    void RenderWindow::NotifyWindowDestroyed()
    {
    }

    void RenderWindow::NotifyFocusReceived()
    {
    }

    void RenderWindow::NotifyFocusLost()
    {
    }

    void RenderWindow::NotifyMovedOrResized()
    {
    }

    void RenderWindow::NotifyMouseLeft()
    {
    }

    void RenderWindow::NotifyCloseRequested()
    {
    }
}