#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
    struct GamepadInfo;

    /** Represents a single hardware gamepad. Used by the Input to report gamepad input events. */
    class TE_CORE_EXPORT GamePad
    {
    public:
        GamePad();
        ~GamePad();
    };
}