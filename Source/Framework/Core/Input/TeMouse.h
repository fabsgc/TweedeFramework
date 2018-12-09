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

        /** Returns the name of the device. */
        const String& getName() const { return _name; }

        /** Captures the input since the last call and triggers the events on the parent Input. */
        void Capture();

    private:
        friend class Input;

        String _name;
        Input* _owner;
    };
}