# Source files and their filters
include(CMakeSources.cmake)
    
# Target
add_library (TeFontImporter SHARED ${TE_FONTIMPORTER_SRC})

# Defines
target_compile_definitions (TeFontImporter PRIVATE -DTE_FONT_EXPORTS)

if (WIN32)
    if (${CMAKE_SYSTEM_VERSION} EQUAL 6.1) # Windows 7
        target_compile_definitions (TeD3D11RenderAPI PRIVATE -DTE_WIN_SDK_7)
    elseif (${CMAKE_SYSTEM_VERSION} EQUAL 6.2) # Windows 8
        target_compile_definitions (TeD3D11RenderAPI PRIVATE -DTE_WIN_SDK_8)
    elseif (${CMAKE_SYSTEM_VERSION} EQUAL 10.0) # Windows 10
        target_compile_definitions (TeD3D11RenderAPI PRIVATE -DTE_WIN_SDK_10)
    endif ()
endif ()

# Includes
target_include_directories (TeFontImporter PRIVATE "./")

# Libraries
## External libs: FLAC, Vorbis, Ogg, OpenAL
target_link_libraries(TeFontImporter ${freetype_LIBRARIES})

## Local libs
target_link_libraries (TeFontImporter tef)

# IDE specific
set_property (TARGET TeFontImporter PROPERTY FOLDER Plugins)

# Install
if (!WIN32)
    install_tef_target (TeFontImporter)
endif ()