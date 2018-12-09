#pragma once

#include "TeCorePrerequisites.h"
#include "RenderAPI/TeVideoMode.h"

namespace te
{
    /** Structure that is used for initializing a render window. */
    struct TE_CORE_EXPORT RENDER_WINDOW_DESC
    {
        RENDER_WINDOW_DESC()
            : Fullscreen(false), Vsync(false), Hidden(false), DepthBuffer(true)
            , MultisampleCount(0), MultisampleHint(""), Gamma(false), Left(-1), Top(-1), Title("Application")
            , ShowTitleBar(true), ShowBorder(true), AllowResize(true), ToolWindow(false), Modal(false)
            , HideUntilSwap(false)
        { }

        VideoMode Mode; /**< Output monitor, frame buffer resize and refresh rate. */
        bool Fullscreen; /**< Should the window be opened in fullscreen mode. */
        bool Vsync; /**< Should the window wait for vertical sync before swapping buffers. */
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

    /**	Contains various properties that describe a render window. */
    class TE_CORE_EXPORT RenderWindowProperties
    {
    public:
        RenderWindowProperties(const RENDER_WINDOW_DESC& desc);
        virtual ~RenderWindowProperties() = default;

        /** Width of the render target, in pixels. */
        UINT32 Width = 0;

        /** Height of the render target, in pixels. */
        UINT32 Height = 0;

        /**
         * True if the render target will wait for vertical sync before swapping buffers. This will eliminate
         * tearing but may increase input latency.
         */
        bool Vsync = false;

        /** Controls how many samples are used for multisampling. (0 or 1 if multisampling is not used). */
        UINT32 MultisampleCount = 0;

        /**	True if window is running in fullscreen mode. */
        bool IsFullScreen = false;

        /**	Horizontal origin of the window in pixels. */
        INT32 Left = 0;

        /**	Vertical origin of the window in pixels. */
        INT32 Top = 0;

        /**	Indicates whether the window currently has keyboard focus. */
        bool HasFocus = false;

        /**	True if the window is hidden. */
        bool IsHidden = false;

        /**	True if the window is maximized. */
        bool IsMaximized = false;

        /**
         * Does the texture need to be vertically flipped because of different screen space coordinate systems.	(Determines
         * is origin top left or bottom left. Engine default is top left.)
         */
        bool RequiresTextureFlipping = false;
    };

    class TE_CORE_EXPORT RenderWindow
    {
    public:
        RenderWindow(const RENDER_WINDOW_DESC& desc);
        ~RenderWindow();

        virtual void Update() = 0;
        virtual void Initialize() = 0;
        virtual void Destroy() = 0;

        /** Queries the render target for a custom attribute. This may be anything and is implementation specific. */
        virtual void GetCustomAttribute(const String& name, void* pData) const;

    protected:
        RENDER_WINDOW_DESC _desc;
    };
}