#include "Private/Win32/TeWin32Platform.h"
#include "RenderAPI/TeRenderWindow.h"
#include "TeCoreApplication.h"
#include "Utility/TeEvent.h"
#include "Math/TeVector2I.h"
#include "Utility/TePlatformUtility.h"
#include "TeCoreApplication.h"

namespace te
{
    Event<void(const Vector2I&, const OSPointerButtonStates&)> Platform::OnCursorMoved;
    Event<void(const Vector2I&, OSMouseButton button, const OSPointerButtonStates&)> Platform::OnCursorButtonPressed;
    Event<void(const Vector2I&, OSMouseButton button, const OSPointerButtonStates&)> Platform::OnCursorButtonReleased;
    Event<void(const Vector2I&, const OSPointerButtonStates&)> Platform::OnCursorDoubleClick;
    Event<void(float)> Platform::OnMouseWheelScrolled;
    Event<void(UINT32)> Platform::OnCharInput;

    Event<void()> Platform::OnMouseCaptureChanged;

    Platform::~Platform()
    {

    }

    Vector2I Platform::GetCursorPosition()
    {
        return Vector2I(0, 0);
    }

    void Platform::SetCursorPosition(const Vector2I& screenPos)
    {
    }

    void Platform::CaptureMouse(const RenderWindow& window)
    {
    }

    void Platform::ReleaseMouseCapture()
    {
    }

    bool Platform::IsPointOverWindow(const RenderWindow& window, const Vector2I& screenPos)
    {
        return false;
    }

    void Platform::ClipCursorToWindow(const RenderWindow& window)
    {
    }

    void Platform::ClipCursorToRect(const Rect2I& screenRect)
    {
    }

    void Platform::ClipCursorDisable()
    {
    }

    void Platform::HideCursor()
    {
    }

    void Platform::ShowCursor()
    {
    }

    bool Platform::IsCursorHidden()
    {
        return false;
    }

    void Platform::Update()
    {
        MessagePump();
    }

    void Platform::MessagePump()
    {
        MSG  msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    LRESULT CALLBACK Win32Platform::_win32WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (uMsg == WM_CREATE)
        {	// Store pointer to Win32Window in user data area
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)(((LPCREATESTRUCT)lParam)->lpCreateParams));

            RenderWindow* newWindow = (RenderWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
            if (newWindow != nullptr)
            {
                ShowWindow(hWnd, SW_SHOWNORMAL);
            }
            else
            {
                ShowWindow(hWnd, SW_SHOWNORMAL);
            }

            return 0;
        }

        RenderWindow* win = (RenderWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (!win)
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        switch (uMsg)
        {
            case WM_CLOSE: {
                gCoreApplication().OnStopRequested();
                return 0;
            }
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}