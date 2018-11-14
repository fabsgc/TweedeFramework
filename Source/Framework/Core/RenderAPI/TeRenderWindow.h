#pragma once

#include "TeCorePrerequisites.h"
#include "RenderAPI/TeVideoMode.h"

namespace te
{
    /** Structure that is used for initializing a render window. */
    struct TE_CORE_EXPORT RENDER_WINDOW_DESC
    {
        RENDER_WINDOW_DESC()
            : fullscreen(false), vsync(false), vsyncInterval(1), hidden(false), depthBuffer(true)
            , multisampleCount(0), multisampleHint(""), gamma(false), left(-1), top(-1), title("")
            , showTitleBar(true), showBorder(true), allowResize(true), toolWindow(false), modal(false)
            , hideUntilSwap(false)
        { }

        VideoMode videoMode; /**< Output monitor, frame buffer resize and refresh rate. */
        bool fullscreen; /**< Should the window be opened in fullscreen mode. */
        bool vsync; /**< Should the window wait for vertical sync before swapping buffers. */
        UINT32 vsyncInterval; /**< Determines how many vsync intervals occur per frame. FPS = refreshRate/interval. Usually 1 when vsync active. */
        bool hidden; /**< Should the window be hidden initially. */
        bool depthBuffer; /**< Should the window be created with a depth/stencil buffer. */
        UINT32 multisampleCount; /**< If higher than 1, texture containing multiple samples per pixel is created. */
        String multisampleHint; /**< Hint about what kind of multisampling to use. Render system specific. */
        bool gamma; /**< Should the written color pixels be gamma corrected before write. */
        INT32 left; /**< Window origin on X axis in pixels. -1 == screen center. Relative to monitor provided in videoMode. */
        INT32 top; /**< Window origin on Y axis in pixels. -1 == screen center. Relative to monitor provided in videoMode. */
        String title; /**< Title of the window. */
        bool showTitleBar; /**< Determines if the title-bar should be shown or not. */
        bool showBorder; /**< Determines if the window border should be shown or not. */
        bool allowResize; /**< Determines if the user can resize the window by dragging on the window edges. */
        bool toolWindow; /**< Tool windows have no task bar entry and always remain on top of their parent window. */
        bool modal; /**< When a modal window is open all other windows will be locked until modal window is closed. */
        bool hideUntilSwap; /**< Window will be created as hidden and only be shown when the first framebuffer swap happens. */
    };

    class TE_CORE_EXPORT RenderWindow
    {
    public:
        RenderWindow();
        ~RenderWindow();
    };
}