#include "Input/TeGamePad.h"
#include "Input/TeInput.h"
#include "Private/Win32/TeWin32Input.h"

namespace te
{
    GamePad::GamePad(const String& name, const GamePadInfo& gamepadInfo, Input* owner)
        : _name(name), _owner(owner)
    {
    }

    GamePad::~GamePad()
    {
    }

    void GamePad::Capture()
    {
        //TODO
    }

    void GamePad::ChangeCaptureContext(UINT64 windowHandle)
    {
        HWND newhWnd = (HWND)windowHandle;

        /*if (_data->HWnd != newhWnd)
        {
            ReleaseDirectInput(_data);

            if (windowHandle != (UINT64)-1)
                InitializeDirectInput(_data, newhWnd);
            else
                _data->HWnd = (HWND)-1;
        }*/

        //TODO
    }
}