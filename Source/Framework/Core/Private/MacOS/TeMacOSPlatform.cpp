#include "Private/MacOS/TeMacOSPlatform.h"
#include "RenderAPI/TeRenderWindow.h"
#include "TeCoreApplication.h"
#include "Math/TeVector2I.h"
#include "Math/TeRect2I.h"
#include "Threading/TeThreading.h"
#include "Utility/TeEvent.h"
#include "Utility/TePlatformUtility.h"

namespace te
{
    struct Platform::Pimpl
    {
    };

    Event<void(const Vector2I&, const OSPointerButtonStates&)> Platform::OnCursorMoved;
    Event<void(const Vector2I&, OSMouseButton button, const OSPointerButtonStates&)> Platform::OnCursorButtonPressed;
    Event<void(const Vector2I&, OSMouseButton button, const OSPointerButtonStates&)> Platform::OnCursorButtonReleased;
    Event<void(const Vector2I&, const OSPointerButtonStates&)> Platform::OnCursorDoubleClick;
    Event<void(float)> Platform::OnMouseWheelScrolled;
    Event<void(UINT32)> Platform::OnCharInput;

    Event<void()> Platform::OnMouseCaptureChanged;

    Platform::Pimpl* Platform::_data = te_new<Platform::Pimpl>();

    Platform::~Platform()
    {
    }

    Vector2I Platform::GetCursorPosition()
    {
        return Vector2I(0, 0);
    }

    void Platform::SetCursorPosition(const Vector2I& screenPos)
    {
        // TODO
    }

    void Platform::CaptureMouse(const RenderWindow& window)
    {
        // TODO
    }

    void Platform::ReleaseMouseCapture()
    {
        // TODO
    }

    bool Platform::IsPointOverWindow(const RenderWindow& window, const Vector2I& screenPos)
    {
        return false;
        // TODO
    }

    void Platform::ClipCursorToWindow(const RenderWindow& window)
    {
        // TODO
    }

    void Platform::ClipCursorToRect(const Rect2I& screenRect)
    {
        // TODO
    }

    void Platform::ClipCursorDisable()
    {
        // TODO
    }

    void Platform::HideCursor()
    {
        // TODO
    }

    void Platform::ShowCursor()
    {
        // TODO
    }

    bool Platform::IsCursorHidden()
    {
        return false;
        // TODO
    }

    void Platform::Update()
    {
        MessagePump();
    }

    void Platform::MessagePump()
    {
        // TODO
    }
}