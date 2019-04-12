#pragma once

#include "Prerequisites/TePrerequisitesUtility.h"
#include "Math/TeVector2I.h"

namespace te
{
    /**	Descriptor used for creating a platform specific native window. */
    struct TE_UTILITY_EXPORT WINDOW_DESC
    {
        WINDOW_DESC() = default;
    };

    /**	Represents a Windows native window. */
    class TE_UTILITY_EXPORT MacOSWindow
    {
    public:
        MacOSWindow(const WINDOW_DESC& desc);
        ~MacOSWindow();

    private:
        struct Pimpl;
        Pimpl* _data;
    };
}