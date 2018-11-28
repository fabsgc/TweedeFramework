#pragma once

#include "TeCorePrerequisites.h"
#include "RenderAPI/TeVideoMode.h"

namespace te
{
    /** Structure that is used for initializing a render window. */
    struct TE_CORE_EXPORT RENDER_WINDOW_DESC
    {
        RENDER_WINDOW_DESC()
            : Fullscreen(false), Vsync(false), VsyncInterval(1), Hidden(false), DepthBuffer(true)
            , MultisampleCount(0), MultisampleHint(""), Gamma(false), Left(-1), Top(-1), Title("Application")
            , ShowTitleBar(true), ShowBorder(true), AllowResize(true), ToolWindow(false), Modal(false)
            , HideUntilSwap(false)
        { }

        VideoMode Mode; /**< Output monitor, frame buffer resize and refresh rate. */
        bool Fullscreen; /**< Should the window be opened in fullscreen mode. */
        bool Vsync; /**< Should the window wait for vertical sync before swapping buffers. */
        UINT32 VsyncInterval; /**< Determines how many vsync intervals occur per frame. FPS = refreshRate/interval. Usually 1 when vsync active. */
        bool Hidden; /**< Should the window be hidden initially. */
        bool DepthBuffer; /**< Should the window be created with a depth/stencil buffer. */
        UINT32 MultisampleCount; /**< If higher than 1, texture containing multiple samples per pixel is created. */
        String MultisampleHint; /**< Hint about what kind of multisampling to use. Render system specific. */
        bool Gamma; /**< Should the written color pixels be gamma corrected before write. */
        INT32 Left; /**< Window origin on X axis in pixels. -1 == screen center. Relative to monitor provided in videoMode. */
        INT32 Top; /**< Window origin on Y axis in pixels. -1 == screen center. Relative to monitor provided in videoMode. */
        String Title; /**< Title of the window. */
        bool ShowTitleBar; /**< Determines if the title-bar should be shown or not. */
        bool ShowBorder; /**< Determines if the window border should be shown or not. */
        bool AllowResize; /**< Determines if the user can resize the window by dragging on the window edges. */
        bool ToolWindow; /**< Tool windows have no task bar entry and always remain on top of their parent window. */
        bool Modal; /**< When a modal window is open all other windows will be locked until modal window is closed. */
        bool HideUntilSwap; /**< Window will be created as hidden and only be shown when the first framebuffer swap happens. */
    };

    class TE_CORE_EXPORT RenderWindow
    {
    public:
        RenderWindow();
        ~RenderWindow();
    };
}