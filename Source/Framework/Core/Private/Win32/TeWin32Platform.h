#pragma once

#include "Platform/TePlatform.h"

#define WIN32_LEAN_AND_MEAN
#if !defined(NOMINMAX) && defined(_MSC_VER)
#	define NOMINMAX // Required to stop windows.h messing up std::min
#endif
#include <windows.h>
#include <windowsx.h>

namespace te
{
    struct Platform::Pimpl
    {
        bool IsCursorHidden = false;
        bool IsTrackingMouse = false;

        bool CursorClipping = false;
        HWND ClipWindow = 0;
        RECT ClipRect;

        bool IsActive = false;
    };

    /** Various Win32 specific functionality. Contains the main message loop. */
    class TE_CORE_EXPORT Win32Platform : public Platform
    {
    public:
        /** Main message loop callback that processes messages received from windows. */
        static LRESULT CALLBACK _win32WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };
}