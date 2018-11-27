#pragma once

#include "TeCorePrerequisites.h"
#include "Utility/TeModule.h"
#include "Utility/TeEvent.h"

namespace te
{
    class Mouse;
    class Keyboard;
    class Gamepad;

    class TE_CORE_EXPORT Input : public Module<Input>
    {
    public:
        Input();
        ~Input();

        void Update();

    public:
        /** Triggered whenever a button is first pressed. */
        Event<void(void)> OnButtonDown;

        /**	Triggered whenever a button is first released. */
        Event<void(void)> OnButtonUp;

        /**	Triggered whenever user inputs a text character. */
        Event<void(void)> OnCharInput;

        /**	Triggers when some pointing device (mouse cursor, touch) moves. */
        Event<void(void)> OnPointerMoved;

        /**	Triggers when some pointing device (mouse cursor, touch) button is pressed. */
        Event<void(void)> OnPointerPressed;

        /**	Triggers when some pointing device (mouse cursor, touch) button is released. */
        Event<void(void)> OnPointerReleased;

        /**	Triggers when some pointing device (mouse cursor, touch) button is double clicked. */
        Event<void(void)> OnPointerDoubleClick;

    protected:
        Mouse* _mouse;
        Keyboard* _keyboard;
        Vector<Gamepad*> _gamepads;
    };

    /**	Provides easy access to Input. */
    TE_CORE_EXPORT Input& gInput();
    TE_CORE_EXPORT Input* gInputPtr();
}