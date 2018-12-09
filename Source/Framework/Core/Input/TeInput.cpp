#include "Input/TeInput.h"
#include "Input/TeMouse.h"
#include "Input/TeKeyboard.h"
#include "Input/TeGamePad.h"
#include "Platform/TePlatform.h"
#include "TeCoreApplication.h"

using namespace std::placeholders;

namespace te
{
    Input::Input()
        : _mouse(nullptr)
        , _keyboard(nullptr)
    {
        SPtr<RenderWindow> window = gCoreApplication().GetWindow();
        window->GetCustomAttribute("WINDOW", &_windowHandle);

        _charInputConn = Platform::OnCharInput.Connect(std::bind(&Input::CharInput, this, _1));
        _cursorMovedConn = Platform::OnCursorMoved.Connect(std::bind(&Input::CursorMoved, this, _1, _2));
        _cursorPressedConn = Platform::OnCursorButtonPressed.Connect(std::bind(&Input::CursorPressed, this, _1, _2, _3));
        _cursorReleasedConn = Platform::OnCursorButtonReleased.Connect(std::bind(&Input::CursorReleased, this, _1, _2, _3));
        _cursorDoubleClickConn = Platform::OnCursorDoubleClick.Connect(std::bind(&Input::CursorDoubleClick, this, _1, _2));

        _mouseWheelScrolledConn = Platform::OnMouseWheelScrolled.Connect(std::bind(&Input::MouseWheelScrolled, this, _1));

        // Raw input
        InitRawInput();
    }

    Input::~Input()
    {
        CleanUpRawInput();

        _charInputConn.Disconnect();
        _cursorMovedConn.Disconnect();
        _cursorPressedConn.Disconnect();
        _cursorReleasedConn.Disconnect();
        _cursorDoubleClickConn.Disconnect();
        _mouseWheelScrolledConn.Disconnect();
    }

    void Input::Update()
    {
    }

    void Input::TriggerCallbacks()
    {

    }

    void Input::CharInput(UINT32 chr)
    {
    }

    void Input::CursorMoved(const Vector2I& cursorPos, const OSPointerButtonStates& btnStates)
    {
        _pointerPosition = cursorPos;
        _pointerState = btnStates;
    }

    void Input::CursorPressed(const Vector2I& cursorPos, OSMouseButton button, const OSPointerButtonStates& btnStates)
    {
    }

    void Input::CursorReleased(const Vector2I& cursorPos, OSMouseButton button, const OSPointerButtonStates& btnStates)
    {
    }

    void Input::CursorDoubleClick(const Vector2I& cursorPos, const OSPointerButtonStates& btnStates)
    {
    }

    void Input::MouseWheelScrolled(float scrollPos)
    {
    }

    Input& gInput()
    {
        return Input::Instance();
    }

    Input* gInputPtr()
    {
        return Input::InstancePtr();
    }
}