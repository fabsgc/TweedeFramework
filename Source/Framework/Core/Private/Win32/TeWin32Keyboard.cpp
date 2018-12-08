#include "Input/TeKeyboard.h"
#include "Input/TeInput.h"
#include "Private/Win32/TeWin32Input.h"

namespace te
{
    Keyboard::Keyboard(const String& name, Input* owner)
        : _name(name), _owner(owner)
    {
    }

    Keyboard::~Keyboard()
    {
    }
}