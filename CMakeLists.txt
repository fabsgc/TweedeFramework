cmake_minimum_required (VERSION 3.9.0)

project (TweedeEngineFramework)

set (TE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/Source)
set (APP_ROOT_DIR ${PROJECT_SOURCE_DIR})

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if (LINUX)
        set(CMAKE_INSTALL_PREFIX /usr/local/opt/tef CACHE PATH "..." FORCE) 	
    endif () 
endif ()

include (Source/CMake/Properties.cmake)
include (Source/CMake/FindPackageOrBuild.cmake)
include (Source/CMake/HelperMethods.cmake)

add_subdirectory (Source)
