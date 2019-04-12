#include "Input/TeInput.h"
#include "Private/MacOS/TeMacOSInput.h"

namespace te
{
    void Input::InitRawInput()
    {
        // TODO
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
    }

    UINT32 Input::GetDeviceCount(InputDevice device) const
    {
        // TODO
        
        switch (device)
        {
            case InputDevice::Keyboard: return 1;
            case InputDevice::Mouse: return 1;
            case InputDevice::Gamepad: return 0;
            default:
            case InputDevice::Count: return 0;
        }
    }
}