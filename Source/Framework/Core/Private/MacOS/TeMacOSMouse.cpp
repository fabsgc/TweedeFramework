#include "Input/TeMouse.h"
#include "Input/TeInput.h"
#include "Private/MacOS/TeMacOSInput.h"

namespace te
{
    Mouse::Mouse(const String& name, Input* owner)
        : _name(name), _owner(owner)
    {
        // TODO
    }

    Mouse::~Mouse()
    {
        // TODO
    }

    void Mouse::Capture()
    {
        // TODO
    }

    void Mouse::ChangeCaptureContext(UINT64 windowHandle)
    {
        // TODO
    }
}