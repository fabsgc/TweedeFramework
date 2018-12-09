#include "Input/TeKeyboard.h"
#include "Input/TeInput.h"
#include "Private/Win32/TeWin32Input.h"

namespace te
{
    /** Contains private data for the Win32 Keyboard implementation. */
    struct Keyboard::Pimpl
    {
        IDirectInput8* directInput;
        IDirectInputDevice8* keyboard;
        DWORD coopSettings;
        HWND hWnd;

        UINT8 keyBuffer[256];
    };

    Keyboard::Keyboard(const String& name, Input* owner)
        : _name(name), _owner(owner)
    {
    }

    Keyboard::~Keyboard()
    {
    }

    void Keyboard::Capture()
    {
    }
}