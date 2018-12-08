#include "Input/TeInput.h"
#include "Error/TeError.h"
#include "Private/Win32/TeWin32Input.h"
#include "Input/TeMouse.h"
#include "Input/TeKeyboard.h"
#include "Input/TeGamePad.h"

namespace te
{
    void Input::Update()
    {
    }

    void Input::InitRawInput()
    {
        _platformData = te_new<InputPrivateData>();

        if(IsWindow((HWND)_windowHandle) == 0)
            TE_ASSERT_ERROR(false, "RawInputManager failed to initialized. Invalid HWND provided.")

        HINSTANCE hInst = GetModuleHandle(0);

        HRESULT hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&_platformData->DirectInput, nullptr);
        if (FAILED(hr))
            TE_ASSERT_ERROR(false, "Unable to initialize DirectInput.");

        _platformData->KbSettings = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
        _platformData->MouseSettings = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;

        //TODO

        if (getDeviceCount(InputDevice::Keyboard) > 0)
            _keyboard = te_new<Keyboard>("Keyboard", this);

        if (getDeviceCount(InputDevice::Mouse) > 0)
            _mouse = te_new<Mouse>("Mouse", this);

        UINT32 numGamepads = getDeviceCount(InputDevice::Gamepad);
        for (UINT32 i = 0; i < numGamepads; i++)
            _gamepads.push_back(te_new<GamePad>(_platformData->GamepadInfos[i].Name, _platformData->GamepadInfos[i], this));
    }

    void Input::CleanUpRawInput()
    {
        if (_mouse != nullptr)
        {
            te_delete(_mouse);
        }

        if (_keyboard != nullptr)
        {
            te_delete(_keyboard);
        }

        for (auto& gamepad : _gamepads)
        {
            te_delete(gamepad);
        }

        if (_platformData->DirectInput)
        {
            _platformData->DirectInput->Release();
        }

        te_delete(_platformData);
    }

    UINT32 Input::getDeviceCount(InputDevice device) const
    {
        switch (device)
        {
            case InputDevice::Keyboard: return 1;
            case InputDevice::Mouse: return 1;
            case InputDevice::Gamepad: return (UINT32)_platformData->GamepadInfos.size();
            default:
            case InputDevice::Count: return 0;
        }
    }
}