# Source files and their filters
include(CMakeSources.cmake)
    
# Target
add_library (TeRenderer SHARED ${TE_RENDERER_SRC})

# Defines
target_compile_definitions (TeRenderer PRIVATE -DTE_RSRND_EXPORTS)

# Includes
target_include_directories (TeRenderer PRIVATE "./")

# Libraries
## Local libs
target_link_libraries (TeRenderer tef)

# IDE specific
set_property (TARGET TeRenderer PROPERTY FOLDER Plugins)

# Install
if (!WIN32)
    install_tef_target (TeRenderer)
endif ()