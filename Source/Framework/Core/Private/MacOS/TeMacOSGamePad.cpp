#include "Input/TeGamePad.h"
#include "Input/TeInput.h"
#include "Private/MacOS/TeMacOSInput.h"

namespace te
{
    GamePad::GamePad(const String& name, const GamePadInfo& gamepadInfo, Input* owner)
        : _name(name), _owner(owner)
    {
    }

    GamePad::~GamePad()
    {
    }
}