set (TE_CORE_INC_RENDERAPI
    "Core/RenderAPI/TeRenderAPI.h"
    "Core/RenderAPI/TeRenderWindow.h"
    "Core/RenderAPI/TeVideoMode.h"
    "Core/RenderAPI/TeRenderAPIFactory.h"
)
set (TE_CORE_SRC_RENDERAPI
    "Core/RenderAPI/TeRenderAPI.cpp"
    "Core/RenderAPI/TeRenderWindow.cpp"
    "Core/RenderAPI/TeVideoMode.cpp"
)

set (TE_CORE_INC_RENDERER
    "Core/Renderer/TeRenderer.h"
    "Core/Renderer/TeRendererFactory.h"
)
set (TE_CORE_SRC_RENDERER
    "Core/Renderer/TeRenderer.cpp"
)

set(TE_CORE_INC_PLATFORM
    "Core/Platform/TePlatform.h"
)
set(TE_CORE_SRC_PLATFORM 
)

set (TE_CORE_INC_PLATFORM_WIN32
    "Core/Private/Win32/TeWin32Window.h"
    "Core/Private/Win32/TeWin32Input.h"
    "Core/Private/Win32/TeWin32Platform.h"
)
set (TE_CORE_SRC_PLATFORM_WIN32
    "Core/Private/Win32/TeWin32Window.cpp"
    "Core/Private/Win32/TeWin32Input.cpp"
    "Core/Private/Win32/TeWin32GamePad.cpp"
    "Core/Private/Win32/TeWin32Keyboard.cpp"
    "Core/Private/Win32/TeWin32Mouse.cpp"
    "Core/Private/Win32/TeWin32Platform.cpp"
)

set (TE_CORE_INC_PLATFORM_LINUX
    "Core/Private/Linux/TeLinuxWindow.h"
    "Core/Private/Linux/TeLinuxInput.h"
    "Core/Private/Linux/TeLinuxPlatform.h"
)
set (TE_CORE_SRC_PLATFORM_LINUX
    "Core/Private/Linux/TeLinuxWindow.cpp"
    "Core/Private/Linux/TeLinuxInput.cpp"
    "Core/Private/Linux/TeLinuxGamePad.cpp"
    "Core/Private/Linux/TeLinuxKeyboard.cpp"
    "Core/Private/Linux/TeLinuxMouse.cpp"
    "Core/Private/Linux/TeLinuxPlatform.cpp"
)

set (TE_CORE_INC_PLATFORM_MACOS
    "Core/Private/MacOS/TeMacOSWindow.h"
    "Core/Private/MacOS/TeMacOSInput.h"
    "Core/Private/MacOS/TeMacOSPlatform.h"
)
set (TE_CORE_SRC_PLATFORM_MACOS
    "Core/Private/MacOS/TeMacOSWindow.cpp"
    "Core/Private/MacOS/TeMacOSInput.cpp"
    "Core/Private/MacOS/TeMacOSGamePad.cpp"
    "Core/Private/MacOS/TeMacOSKeyboard.cpp"
    "Core/Private/MacOS/TeMacOSMouse.cpp"
    "Core/Private/MacOS/TeMacOSPlatform.cpp"
)

set(TE_CORE_INC_NOFILTER
	"Core/TeCoreApplication.h"
	"Core/TeCorePrerequisites.h"
	"Core/TeEngineConfig.h"
)
set(TE_CORE_SRC_NOFILTER
	"Core/TeCoreApplication.cpp"
)

set (TE_CORE_INC_AUDIO
    "Core/Audio/TeAudio.h"
    "Core/Audio/TeAudioFactory.h"
)
set (TE_CORE_SRC_AUDIO
    "Core/Audio/TeAudio.cpp"
    "Core/Audio/TeAudioFactory.cpp"
)

set (TE_CORE_INC_PHYSICS
    "Core/Physics/TePhysics.h"
    "Core/Physics/TePhysicsFactory.h"
)
set (TE_CORE_SRC_PHYSICS
    "Core/Physics/TePhysics.cpp"
    "Core/Physics/TePhysicsFactory.cpp"
)

set (TE_CORE_INC_INPUT
    "Core/Input/TeInput.h"
    "Core/Input/TeGamePad.h"
    "Core/Input/TeKeyboard.h"
    "Core/Input/TeMouse.h"
    "Core/Input/TeInputData.h"
    "Core/Input/TeVirtualInput.h"
    "Core/Input/TeInputConfiguration.h"
)
set (TE_CORE_SRC_INPUT
    "Core/Input/TeInput.cpp"
    "Core/Input/TeVirtualInput.cpp"
    "Core/Input/TeInputConfiguration.cpp"
)

set (TE_CORE_INC_MANAGER
    "Core/Manager/TeRenderAPIManager.h"
    "Core/Manager/TeRendererManager.h"
    "Core/Manager/TePluginManager.h"
)
set (TE_CORE_SRC_MANAGER
    "Core/Manager/TeRenderAPIManager.cpp"
    "Core/Manager/TeRendererManager.cpp"
)

set (TE_CORE_INC_RESOURCES
    "Core/Resources/TeResource.h"
    "Core/Resources/TeResourceHandle.h"
)
set (TE_CORE_SRC_RESOURCES
    "Core/Resources/TeResource.cpp"
    "Core/Resources/TeResourceHandle.cpp"
)

set (TE_CORE_INC_TEXT
    "Core/Text/TeFont.h"
    "Core/Text/TeFontImportOptions.h"
)
set (TE_CORE_SRC_TEXT
    "Core/Text/TeFont.cpp"
    "Core/Text/TeFontImportOptions.cpp"
)

set (TE_CORE_INC_IMPORTER
    "Core/Importer/TeImporter.h"
    "Core/Importer/TeImportOptions.h"
    "Core/Importer/TeTextureImportOptions.cpp"
    "Core/Importer/TeBaseImporter.cpp"
)
set (TE_CORE_SRC_IMPORTER
    "Core/Importer/TeImporter.cpp"
    "Core/Importer/TeImportOptions.h"
    "Core/Importer/TeTextureImportOptions.h"
    "Core/Importer/TeBaseImporter.h"
)

set (TE_CORE_INC_IMAGE
    "Core/Image/TeTexture.h"
)
set (TE_CORE_SRC_IMAGE
    "Core/Image/TeTexture.cpp"
)

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

list(APPEND TE_CORE_INC_PLATFORM ${TE_CORE_INC_PLATFORM})
list(APPEND TE_CORE_SRC_PLATFORM ${TE_CORE_SRC_PLATFORM})

source_group("Core\\RenderAPI" FILES ${TE_CORE_INC_RENDERAPI} ${TE_CORE_SRC_RENDERAPI})
source_group("Core\\Renderer" FILES ${TE_CORE_INC_RENDERER} ${TE_CORE_SRC_RENDERER})
source_group("Core\\Platform" FILES ${TE_CORE_INC_PLATFORM} ${TE_CORE_SRC_PLATFORM})
source_group("Core\\Audio" FILES ${TE_CORE_INC_AUDIO} ${TE_CORE_SRC_AUDIO})
source_group("Core\\Physics" FILES ${TE_CORE_INC_PHYSICS} ${TE_CORE_SRC_PHYSICS})
source_group("Core\\Input" FILES ${TE_CORE_INC_INPUT} ${TE_CORE_SRC_INPUT})
source_group("Core\\Manager" FILES ${TE_CORE_INC_MANAGER} ${TE_CORE_SRC_MANAGER})
source_group("Core\\Resources" FILES ${TE_CORE_INC_RESOURCES} ${TE_CORE_SRC_RESOURCES})
source_group("Core\\Text" FILES ${TE_CORE_INC_TEXT} ${TE_CORE_SRC_TEXT})
source_group("Core\\Importer" FILES ${TE_CORE_INC_IMPORTER} ${TE_CORE_SRC_IMPORTER})
source_group("Core\\Image" FILES ${TE_CORE_INC_IMAGE} ${TE_CORE_SRC_IMAGE})
source_group("Core" FILES ${TE_CORE_INC_NOFILTER} ${TE_CORE_SRC_NOFILTER})

set(TE_CORE_SRC
    ${TE_CORE_SRC_RENDERAPI}
    ${TE_CORE_INC_RENDERAPI}
    ${TE_CORE_SRC_RENDERER}
    ${TE_CORE_INC_RENDERER}
    ${TE_CORE_SRC_PLATFORM}
    ${TE_CORE_INC_PLATFORM}
    ${TE_CORE_SRC_NOFILTER}
    ${TE_CORE_INC_NOFILTER}
    ${TE_CORE_INC_AUDIO}
    ${TE_CORE_SRC_AUDIO}
    ${TE_CORE_INC_PHYSICS}
    ${TE_CORE_SRC_PHYSICS}
    ${TE_CORE_INC_INPUT}
    ${TE_CORE_SRC_INPUT}
    ${TE_CORE_INC_MANAGER}
    ${TE_CORE_SRC_MANAGER}
    ${TE_CORE_INC_IMPORTER}
    ${TE_CORE_SRC_IMPORTER}
    ${TE_CORE_INC_RESOURCES}
    ${TE_CORE_SRC_RESOURCES}
)