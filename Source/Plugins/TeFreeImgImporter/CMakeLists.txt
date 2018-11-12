# Source files and their filters
include(CMakeSources.cmake)
    
# Target
add_library (TeFreeImgImporter SHARED ${TE_FREEIMGIMPORTER_SRC})

# Defines
target_compile_definitions (TeFreeImgImporter PRIVATE -DTE_FREEIMG_EXPORTS)

# Includes
target_include_directories (TeFreeImgImporter PRIVATE "./")

# Libraries
## External libs: FLAC, Vorbis, Ogg, OpenAL
target_link_libraries(TeFreeImgImporter ${freeimg_LIBRARIES})

## Local libs
target_link_libraries (TeFreeImgImporter tef)

# IDE specific
set_property (TARGET TeFreeImgImporter PROPERTY FOLDER Plugins)

# Install
if (!WIN32)
    install_tef_target (TeFreeImgImporter)
endif ()