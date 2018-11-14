set (TE_CORE_INC_RENDERAPI
    "Core/RenderAPI/TeRenderAPI.h"
    "Core/RenderAPI/TeRenderWindow.h"
    "Core/RenderAPI/TeVideoMode.h"
)
set (TE_CORE_SRC_RENDERAPI
    "Core/RenderAPI/TeRenderAPI.cpp"
    "Core/RenderAPI/TeRenderWindow.cpp"
    "Core/RenderAPI/TeVideoMode.cpp"
)

set (TE_CORE_INC_PLATFORM_WIN32
    "Core/Private/Win32/TeWin32Window.h"
)
set (TE_CORE_SRC_PLATFORM_WIN32
    "Core/Private/Win32/TeWin32Window.cpp"
)

set (TE_CORE_INC_PLATFORM_LINUX
    "Core/Private/Linux/TeWin32Window.h"
)
set (TE_CORE_SRC_PLATFORM_LINUX
    "Core/Private/Linux/TeWin32Window.cpp"
)

set (TE_CORE_INC_PLATFORM_MACOS
    "Core/Private/MacOS/TeWin32Window.h"
)
set (TE_CORE_SRC_PLATFORM_MACOS
    "Core/Private/MacOS/TeWin32Window.cpp"
)

set(TE_CORE_INC_NOFILTER
	"Core/TeCoreApplication.h"
	"Core/TeCorePrerequisites.h"
)
set(TE_CORE_SRC_NOFILTER
	"Core/TeCoreApplication.cpp"
)

set(TE_CORE_INC_PLATFORM)

if (WIN32)
    list(APPEND TE_CORE_INC_PLATFORM ${TE_CORE_INC_PLATFORM_WIN32})
    list(APPEND TE_CORE_SRC_PLATFORM ${TE_CORE_SRC_PLATFORM_WIN32})
elseif (LINUX)
    list(APPEND TE_CORE_INC_PLATFORM ${TE_CORE_INC_PLATFORM_LINUX})
    list(APPEND TE_CORE_SRC_PLATFORM ${TE_CORE_SRC_PLATFORM_LINUX})
elseif (APPLE)
    list(APPEND TE_CORE_INC_PLATFORM ${TE_CORE_INC_PLATFORM_MACOS})
    list(APPEND TE_CORE_SRC_PLATFORM ${TE_CORE_SRC_PLATFORM_MACOS})
endif ()

source_group("Core\\RenderAPI" FILES ${TE_CORE_INC_RENDERAPI} ${TE_CORE_SRC_RENDERAPI})
source_group("Core\\Platform" FILES ${TE_CORE_INC_PLATFORM} ${TE_CORE_SRC_PLATFORM})
source_group("Core" FILES ${TE_CORE_INC_NOFILTER} ${TE_CORE_SRC_NOFILTER})

set(TE_CORE_SRC
    ${TE_CORE_SRC_RENDERAPI}
    ${TE_CORE_INC_RENDERAPI}
    ${TE_CORE_SRC_PLATFORM}
    ${TE_CORE_INC_PLATFORM}
    ${TE_CORE_SRC_NOFILTER}
    ${TE_CORE_INC_NOFILTER}
)