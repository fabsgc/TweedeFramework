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
}