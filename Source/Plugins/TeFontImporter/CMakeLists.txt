# Source files and their filters
include(CMakeSources.cmake)
    
# Target
add_library (TeFontImporter SHARED ${TE_FONTIMPORTER_SRC})

# Defines
target_compile_definitions (TeFontImporter PRIVATE -DTE_FONT_EXPORTS)

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