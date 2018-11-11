# Source files and their filters
include(CMakeSources.cmake)

add_executable(
    HelloWorld
    ${TE_HELLOWORLD_SRC}
)

# Libraries
## Local libs
target_link_libraries (HelloWorld tef)

