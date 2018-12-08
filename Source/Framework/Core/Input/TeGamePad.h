#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
    struct GamePadInfo;

    /** Represents a single hardware gamepad. Used by the Input to report gamepad input events. */
    class TE_CORE_EXPORT GamePad
    {
    public:
        GamePad(const String& name, const GamePadInfo& gamepadInfo, Input* owner);
        ~GamePad();

    private:
        friend class Input;

        String _name;
        Input* _owner;
    };
}