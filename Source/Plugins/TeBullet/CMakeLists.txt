# Source files and their filters
include(CMakeSources.cmake)

# Target
add_library (TeBullet SHARED ${TE_BULLET_SRC})

# Defines
target_compile_definitions (TeBullet PRIVATE -DTE_OA_EXPORTS)

if (WIN32)
    if (${CMAKE_SYSTEM_VERSION} EQUAL 6.1) # Windows 7
        target_compile_definitions (TeBullet PRIVATE -DTE_WIN_SDK_7)
    elseif (${CMAKE_SYSTEM_VERSION} EQUAL 6.2) # Windows 8
        target_compile_definitions (TeBullet PRIVATE -DTE_WIN_SDK_8)
    elseif (${CMAKE_SYSTEM_VERSION} EQUAL 10.0) # Windows 10
        target_compile_definitions (TeBullet PRIVATE -DTE_WIN_SDK_10)
    endif ()
endif ()

# Includes
target_include_directories (TeBullet PRIVATE "./")

# Libraries
## External libs: FLAC, Vorbis, Ogg, OpenAL

## Local libs
target_link_libraries (TeBullet PRIVATE tef)

# IDE specific
set_property (TARGET TeBullet PROPERTY FOLDER Plugins)

# Install
if (AUDIO_MODULE MATCHES "Bullet")
   install_tef_target (TeBullet)
endif ()