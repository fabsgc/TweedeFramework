#pragma once

#include "TeCorePrerequisites.h"

namespace te
{

    /** Represents a single hardware keyboard. Used by the Input to report keyboard input events. */
    class TE_CORE_EXPORT Keyboard
    {
    public:
        Keyboard(const String& name, Input* owner);
        ~Keyboard();

    private:
        friend class Input;

        String _name;
        Input* _owner;
    };
}