#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
    /** Represents a single hardware mouse. Used by the Input to report mouse input events. */
    class TE_CORE_EXPORT Mouse
    {
    public:
        Mouse(const String& name, Input* owner);
        ~Mouse();

    private:
        friend class Input;

        String _name;
        Input* _owner;
    };
}