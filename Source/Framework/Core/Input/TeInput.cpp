#include "Input/TeInput.h"
#include "Input/TeMouse.h"
#include "Input/TeKeyboard.h"
#include "Input/TeGamePad.h"
#include "Platform/TePlatform.h"
#include "TeCoreApplication.h"

using namespace std::placeholders;

namespace te
{   
    Input::DeviceData::DeviceData()
    {
        for (UINT32 i = 0; i < BC_Count; i++)
            KeyStates[i] = ButtonState::Off;
    }

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

        gCoreApplication().GetWindow()->OnFocusGained.Connect(std::bind(&Input::InputWindowChanged, this, _1));
        gCoreApplication().GetWindow()->OnFocusLost.Connect(std::bind(&Input::InputFocusLost, this));

        for (int i = 0; i < 3; i++)
            _pointerButtonStates[i] = ButtonState::Off;

        _mouseSampleAccumulator[0] = 0;
        _mouseSampleAccumulator[1] = 0;
        _totalMouseSamplingTime[0] = 1.0f / 125.0f; // Use 125Hz as initial pooling rate for mice
        _totalMouseSamplingTime[1] = 1.0f / 125.0f;
        _totalMouseNumSamples[0] = 1;
        _totalMouseNumSamples[1] = 1;
        _mouseSmoothedAxis[0] = 0.0f;
        _mouseSmoothedAxis[1] = 0.0f;
        _mouseZeroTime[0] = 0.0f;
        _mouseZeroTime[1] = 0.0f;

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
        // Toggle states only remain active for a single frame before they are transitioned
        // into permanent state

        for (auto& deviceData : _devices)
        {
            for (UINT32 i = 0; i < BC_Count; i++)
            {
                if (deviceData.KeyStates[i] == ButtonState::ToggledOff || deviceData.KeyStates[i] == ButtonState::ToggledOnOff)
                    deviceData.KeyStates[i] = ButtonState::Off;
                else if (deviceData.KeyStates[i] == ButtonState::ToggledOn)
                    deviceData.KeyStates[i] = ButtonState::On;
            }

            UINT32 numAxes = (UINT32)deviceData.Axes.size();
            for (UINT32 i = 0; i < numAxes; i++)
                deviceData.Axes[i] = 0.0f;
        }

        for (UINT32 i = 0; i < 3; i++)
        {
            if (_pointerButtonStates[i] == ButtonState::ToggledOff || _pointerButtonStates[i] == ButtonState::ToggledOnOff)
                _pointerButtonStates[i] = ButtonState::Off;
            else if (_pointerButtonStates[i] == ButtonState::ToggledOn)
                _pointerButtonStates[i] = ButtonState::On;
        }

        _pointerDelta = Vector2I::ZERO; // Reset delta in case we don't receive any mouse input this frame
        _pointerDoubleClicked = false;

        // Capture raw input
        if (_mouse != nullptr)
            _mouse->Capture();

        if (_keyboard != nullptr)
            _keyboard->Capture();

        for (auto& gamepad : _gamepads)
            gamepad->Capture();

        float rawXValue = (float)_mouseSampleAccumulator[0];
        float rawYValue = (float)_mouseSampleAccumulator[1];

        rawXValue *= 0.1f;
        rawYValue *= 0.1f;

        _mouseSampleAccumulator[0] = 0;
        _mouseSampleAccumulator[1] = 0;

        AxisMoved(0, -rawXValue, (UINT32)InputAxis::MouseX);
        AxisMoved(0, -rawYValue, (UINT32)InputAxis::MouseY);
    }

    void Input::TriggerCallbacks()
    {
        //TODO
    }

    void Input::InputWindowChanged(RenderWindow& win)
    {
        UINT64 hWnd = 0;
        win.GetCustomAttribute("WINDOW", &hWnd);

        _keyboard->ChangeCaptureContext(hWnd);
        _mouse->ChangeCaptureContext(hWnd);

        for (auto& gamepad : _gamepads)
        {
            gamepad->ChangeCaptureContext(hWnd);
        } 
    }

    void Input::InputFocusLost()
    {
        _keyboard->ChangeCaptureContext((UINT64)-1);
        _mouse->ChangeCaptureContext((UINT64)-1);

        for (auto& gamepad : _gamepads)
        {
            gamepad->ChangeCaptureContext((UINT64)-1);
        }
    }

    Vector2I Input::GetPointerPosition() const
    {
        return _pointerPosition;
    }

    float Input::GetAxisValue(UINT32 type, UINT32 deviceIdx) const
    {
        //TODO
        return 0.0f;
    }

    bool Input::IsButtonHeld(ButtonCode keyCode, UINT32 deviceIdx) const
    {
        //TODO
        return false;
    }

    bool Input::IsButtonUp(ButtonCode keyCode, UINT32 deviceIdx) const
    {
        //TODO
        return false;
    }

    bool Input::IsButtonDown(ButtonCode keyCode, UINT32 deviceIdx) const
    {
        //TODO
        return false;
    }

    bool Input::IsPointerButtonHeld(PointerEventButton pointerButton) const
    {
        //TODO
        return false;
    }

    bool Input::IsPointerButtonUp(PointerEventButton pointerButton) const
    {
        //TODO
        return false;
    }

    bool Input::IsPointerButtonDown(PointerEventButton pointerButton) const
    {
        //TODO
        return false;
    }

    bool Input::IsPointerDoubleClicked() const
    {
        return _pointerDoubleClicked;
    }

    void Input::NotifyMouseMoved(INT32 relX, INT32 relY, INT32 relZ)
    {
        //TODO
    }

    void Input::NotifyAxisMoved(UINT32 gamepadIdx, UINT32 axisIdx, INT32 value)
    {
        //TODO
    }

    void Input::NotifyButtonPressed(UINT32 deviceIdx, ButtonCode code, UINT64 timestamp)
    {
        ButtonDown(deviceIdx, code, timestamp);
    }

    void Input::NotifyButtonReleased(UINT32 deviceIdx, ButtonCode code, UINT64 timestamp)
    {
        ButtonUp(deviceIdx, code, timestamp);
    }

    void Input::CharInput(UINT32 chr)
    {
        //TODO
    }

    void Input::CursorMoved(const Vector2I& cursorPos, const OSPointerButtonStates& btnStates)
    {
        _pointerPosition = cursorPos;
        _pointerState = btnStates;
    }

    void Input::CursorPressed(const Vector2I& cursorPos, OSMouseButton button, const OSPointerButtonStates& btnStates)
    {
        //TODO
    }

    void Input::CursorReleased(const Vector2I& cursorPos, OSMouseButton button, const OSPointerButtonStates& btnStates)
    {
        //TODO
    }

    void Input::CursorDoubleClick(const Vector2I& cursorPos, const OSPointerButtonStates& btnStates)
    {
        //TODO
    }

    void Input::MouseWheelScrolled(float scrollPos)
    {
        //TODO
    }

    void Input::ButtonDown(UINT32 deviceIdx, ButtonCode code, UINT64 timestamp)
    {
        Lock lock(_mutex);

        //TODO
    }

    void Input::ButtonUp(UINT32 deviceIdx, ButtonCode code, UINT64 timestamp)
    {
        Lock lock(_mutex);

        //TODO
    }

    void Input::AxisMoved(UINT32 deviceIdx, float value, UINT32 axis)
    {
        //TODO
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