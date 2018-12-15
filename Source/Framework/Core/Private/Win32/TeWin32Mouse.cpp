#include "Input/TeMouse.h"
#include "Input/TeInput.h"
#include "Private/Win32/TeWin32Input.h"

namespace te
{
    Mouse::Mouse(const String& name, Input* owner)
        : _name(name), _owner(owner)
    {
    }

    Mouse::~Mouse()
    {
    }

    void Mouse::Capture()
    {
        //TODO
    }

    void Mouse::ChangeCaptureContext(UINT64 windowHandle)
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