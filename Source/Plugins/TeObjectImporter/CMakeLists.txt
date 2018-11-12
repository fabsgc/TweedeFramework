# Source files and their filters
include(CMakeSources.cmake)
    
# Target
add_library (TeObjectImporter SHARED ${TE_OBJECTIMPORTER_SRC})

# Defines
target_compile_definitions (TeObjectImporter PRIVATE -DTE_OBJECT_EXPORTS)

# Includes
target_include_directories (TeObjectImporter PRIVATE "./")

# Libraries
## External libs: FLAC, Vorbis, Ogg, OpenAL
target_link_libraries(TeObjectImporter ${assimp_LIBRARIES})

## Local libs
target_link_libraries (TeObjectImporter tef)

# IDE specific
set_property (TARGET TeObjectImporter PROPERTY FOLDER Plugins)

# Install
if (!WIN32)
    install_tef_target (TeObjectImporter)
endif ()