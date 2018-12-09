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
    }
}