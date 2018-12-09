#pragma once

#include "TeCorePrerequisites.h"
#include "Utility/TeModule.h"
#include "Utility/TeEvent.h"
#include "Platform/TePlatform.h"
#include "Math/TeVector2I.h"

namespace te
{
    class Mouse;
    class Keyboard;
    class Gamepad;
    struct InputPrivateData;

    /**	Types of input devices. */
    enum class InputDevice
    {
        Keyboard,
        Mouse,
        Gamepad,
        Count // Keep at end
    };

    class TE_CORE_EXPORT Input : public Module<Input>
    {
        enum class ButtonState
        {
            Off, /**< Button is not being pressed. */
            On, /**< Button is being pressed. */
            ToggledOn, /**< Button has been pressed this frame. */
            ToggledOff, /**< Button has been released this frame. */
            ToggledOnOff, /**< Button has been pressed and released this frame. */
        };

    public:
        Input();
        ~Input();

        void Update();

        void TriggerCallbacks();

        /** Returns internal, platform specific privata data. */
        InputPrivateData* GetPrivateData() const { return _platformData; }

        /** Returns a handle to the window that is currently receiving input. */
        UINT64 GetWindowHandle() const { return _windowHandle; }
        
        /**
         * Called from the message loop to notify user has entered a character.
         */
        void CharInput(UINT32 character);

        /**
         * Called from the message loop to notify user has moved the cursor.
         */
        void CursorMoved(const Vector2I& cursorPos, const OSPointerButtonStates& btnStates);

        /**
         * Called from the message loop to notify user has pressed a mouse button.
         */
        void CursorPressed(const Vector2I& cursorPos, OSMouseButton button, const OSPointerButtonStates& btnStates);

        /**
         * Called from the message loop to notify user has released a mouse button.
         */
        void CursorReleased(const Vector2I& cursorPos, OSMouseButton button, const OSPointerButtonStates& btnStates);

        /**
         * Called from the message loop to notify user has double-clicked a mouse button.
         */
        void CursorDoubleClick(const Vector2I& cursorPos, const OSPointerButtonStates& btnStates);

        /**
         * Called from the message loop to notify user has scrolled the mouse wheel.
         */
        void MouseWheelScrolled(float scrollPos);

    protected:
        /** Performs platform specific raw input system initialization. */
        void InitRawInput();

        /** Performs platform specific raw input system cleanup. */
        void CleanUpRawInput();

    public:
        /** Returns the number of detected devices of the specified type. */
        UINT32 getDeviceCount(InputDevice device) const;

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
        Vector<GamePad*> _gamepads;

        // OS input events
        HEvent _charInputConn;
        HEvent _cursorMovedConn;
        HEvent _cursorPressedConn;
        HEvent _cursorReleasedConn;
        HEvent _cursorDoubleClickConn;
        HEvent _inputCommandConn;
        HEvent _mouseWheelScrolledConn;

        Vector2I _pointerPosition;
        Vector2I _lastPointerPosition;
        Vector2I _pointerDelta;
        ButtonState mPointerButtonStates[3];
        OSPointerButtonStates _pointerState;
        float _mouseScroll;

        bool _pointerDoubleClicked;
        bool _lastPositionSet;

        UINT64 _windowHandle;
        InputPrivateData* _platformData;
    };

    /**	Provides easy access to Input. */
    TE_CORE_EXPORT Input& gInput();
    TE_CORE_EXPORT Input* gInputPtr();
}