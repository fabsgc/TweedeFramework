# Source files and their filters
include(CMakeSources.cmake)

# Target
add_library (TeOpenAudio SHARED ${TE_OPENAUDIO_SRC})

# Defines
target_compile_definitions (TeOpenAudio PRIVATE -DTE_OA_EXPORTS)

# Includes
target_include_directories (TeOpenAudio PRIVATE "./")

# Libraries
## External libs: FLAC, Vorbis, Ogg, OpenAL
target_link_libraries(TeOpenAudio PRIVATE ${OpenAL_LIBRARIES})
target_link_libraries(TeOpenAudio PRIVATE ${vorbis_LIBRARIES})
target_link_libraries(TeOpenAudio PRIVATE ${FLAC_LIBRARIES})
target_link_libraries(TeOpenAudio PRIVATE ${ogg_LIBRARIES})

## OS libs
if(APPLE) # MacOS
	target_link_framework(TeOpenAudio CoreAudio)
	target_link_framework(TeOpenAudio AudioUnit)
	target_link_framework(TeOpenAudio AudioToolbox)
endif()

## Local libs
target_link_libraries (TeOpenAudio PRIVATE tef)

# IDE specific
set_property (TARGET TeOpenAudio PROPERTY FOLDER Plugins)

# Install
if (AUDIO_MODULE MATCHES "OpenAudio")
   install_tef_target (TeOpenAudio)
endif ()