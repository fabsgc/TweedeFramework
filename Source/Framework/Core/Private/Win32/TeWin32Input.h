#pragma once

#include "TeCorePrerequisites.h"

#define WIN32_LEAN_AND_MEAN
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <windows.h>
#include <dinput.h>
#include <Xinput.h>

#include <wbemidl.h>
#include <oleauto.h>

namespace te
{
    // Max number of elements to collect from buffered DirectInput
    #define DI_BUFFER_SIZE_KEYBOARD 17
    #define DI_BUFFER_SIZE_MOUSE 128
    #define DI_BUFFER_SIZE_GAMEPAD 129
}