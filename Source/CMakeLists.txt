# Version
set (TE_FRAMEWORK_VERSION_MAJOR 0)
set (TE_FRAMEWORK_VERSION_MINOR 1)

# Options
if(WIN32)
    set (RENDER_API_MODULE "DirectX 11" CACHE STRING "Render API to use.")
    set_property(CACHE RENDER_API_MODULE PROPERTY STRINGS "DirectX 11" "OpenGL")
elseif(APPLE)
    set(RENDER_API_MODULE "OpenGL" CACHE STRING "Render API to use.")
    set_property(CACHE RENDER_API_MODULE PROPERTY STRINGS "OpenGL")
else()
    set(RENDER_API_MODULE "OpenGL" CACHE STRING "Render API to use.")
    set_property(CACHE RENDER_API_MODULE PROPERTY STRINGS "OpenGL")
endif()

set(RENDERER_MODULE "Renderer" CACHE STRING "Renderer backend to use.")
set_property(CACHE RENDERER_MODULE PROPERTY STRINGS Renderer)

# Config file 
## Note: Must happen before script binding generation 
## Set names of libraries used in the config file
if (RENDER_API_MODULE MATCHES "DirectX 11")
    set (RENDER_API_MODULE_LIB TeD3D11RenderAPI)
else ()
    set (RENDER_API_MODULE_LIB TeGLRenderAPI)
endif ()

set(RENDERER_MODULE_LIB TeRenderer)

set(INCLUDE_ALL_IN_WORKFLOW true CACHE BOOL "If true, all libraries (even those not selected) will be included in the generated workflow (e.g. Visual Studio solution). This is useful when working on engine internals with a need for easy access to all parts of it. Only relevant for workflow generators like Visual Studio or XCode.")

## Generate config files)
configure_file("${TE_SOURCE_DIR}/CMake/TeEngineConfig.h.in" "${TE_SOURCE_DIR}/Framework/Core/TeEngineConfig.h")

# Sub-directories
## Framework
add_subdirectory (Framework)

## Plugins
if (INCLUDE_ALL_IN_WORKFLOW AND MSVC)
	add_subdirectory (Plugins/TeD3D11RenderAPI)
	add_subdirectory (Plugins/TeGLRenderAPI)
else () # Otherwise include only chosen ones
	if (RENDER_API_MODULE MATCHES "DirectX 11")
		add_subdirectory (Plugins/TeD3D11RenderAPI)
	else ()
		add_subdirectory (Plugins/TeGLRenderAPI)
	endif ()
endif ()

add_subdirectory (Plugins/TeRenderer)

# Install
install (
	DIRECTORY ../Data
	DESTINATION bin/
)