#include "RenderAPI/TeRenderWindow.h"
#include "TeCoreApplication.h"

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
        , _moveOrResized(false)
        , _mouseLeft(false)
        , _closeRequested(false)
        , _focusReceived(false)
        , _focusLost(false)
    {
    }

    RenderWindow::~RenderWindow()
    {
        NotifyWindowDestroyed();
    }

    void RenderWindow::TriggerCallback()
    {
        Lock lock(_windowMutex);

        if(_moveOrResized)
            OnResized();

        if (_mouseLeft)
            OnMouseLeftWindow(*this);

        if (_closeRequested)
        {
            OnCloseRequested();
            gCoreApplication().OnStopRequested();
        }

        if(_focusReceived)
            OnFocusGained(*this);

        if(_focusLost)
            OnFocusLost(*this);

        _moveOrResized = false;
        _mouseLeft = false;
        _closeRequested = false;
        _focusReceived = false;
        _focusLost = false;
    }

    void RenderWindow::SetHidden(bool hidden)
    {
        _properties.IsHidden = hidden;
    }

    void RenderWindow::Hide()
    {
        SetHidden(true);
    }

    void RenderWindow::Show()
    {
        SetHidden(false);
    }

    void RenderWindow::Destroy()
    {
        NotifyCloseRequested();
    }

    void RenderWindow::NotifyWindowEvent(WindowEventType type)
    {
        switch (type)
        {
            case WindowEventType::Resized:
            {
                WindowMovedOrResized();
                NotifyMovedOrResized();
                
                std::cout << "Event resized" << std::endl;
                break;
            }
            case WindowEventType::Moved:
            {
                WindowMovedOrResized();

                std::cout << "Event moved" << std::endl;
                break;
            }
            case WindowEventType::FocusReceived:
            {
                NotifyFocusReceived();
                std::cout << "Event focus received" << std::endl;
                break;
            }
            case WindowEventType::FocusLost:
            {
                NotifyFocusLost();
                std::cout << "Event focus lost" << std::endl;
                break;
            }
            case WindowEventType::Minimized:
            {
                _properties.IsMaximized = false;
                std::cout << "Event minimized" << std::endl;
                break;
            }
            case WindowEventType::Maximized:
            {
                _properties.IsMaximized = true;
                std::cout << "Event maximized" << std::endl;
                break;
            }
            case WindowEventType::Restored:
            {
                _properties.IsMaximized = false;
                std::cout << "Event restored" << std::endl;
                break;
            }
            case WindowEventType::MouseLeft:
            {
                NotifyMouseLeft();
                std::cout << "Event mouse left" << std::endl;
                break;
            }
            case WindowEventType::CloseRequested:
            {
                NotifyCloseRequested();
                std::cout << "Event close requested" << std::endl;
                break;
            }
        }
    }

    void RenderWindow::NotifyWindowDestroyed()
    {
        // Nothing because only one window in my implementation
    }

    void RenderWindow::NotifyFocusReceived()
    {
        _properties.HasFocus = true;
        _focusReceived = true;
    }

    void RenderWindow::NotifyFocusLost()
    {
        _properties.HasFocus = false;
        _focusLost = true;
    }

    void RenderWindow::NotifyMovedOrResized()
    {
        _moveOrResized = true;
    }

    void RenderWindow::NotifyMouseLeft()
    {
        _mouseLeft = true;
    }

    void RenderWindow::NotifyCloseRequested()
    {
        _closeRequested = true;
    }
}