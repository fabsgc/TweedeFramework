include(CheckCXXCompilerFlag)

if ("${PROJECT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
	set(TE_TOP_LEVEL True)
endif ()

# Configuration types
if (NOT CMAKE_CONFIGURATION_TYPES) # Multiconfig generator?
	if (NOT CMAKE_BUILD_TYPE)
		message(STATUS "Defaulting to release build.")
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Release")
	endif ()
endif ()

# Includes required for various find_package calls
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${TE_SOURCE_DIR}/CMake/Modules/")

if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	set(TE_64BIT true)
else ()
	message( FATAL_ERROR "The framework should not be compiled on a x86 architecture" )
endif ()

if (UNIX AND NOT APPLE)
	set (LINUX TRUE)
endif ()

# Global compile & linker flags
## Compiler-agnostic settings
### Target at least C++17
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED TRUE)

set (CMAKE_INSTALL_RPATH "\$ORIGIN")

## Compiler-specific settings
if(MSVC)
	# Linker
	set (TE_LINKER_FLAGS_COMMON "/DYNAMICBASE /NOLOGO")

	set (TE_LINKER_FLAGS_DEBUG "${TE_LINKER_FLAGS_COMMON} /DEBUG")
	set (TE_LINKER_FLAGS_RELWITHDEBINFO "${TE_LINKER_FLAGS_COMMON} /LTCG:incremental /INCREMENTAL:NO /OPT:REF /DEBUG")
	set (TE_LINKER_FLAGS_MINSIZEREL "${TE_LINKER_FLAGS_COMMON} /DEBUG /LTCG /INCREMENTAL:NO /OPT:REF")
	set (TE_LINKER_FLAGS_RELEASE "${TE_LINKER_FLAGS_COMMON} /DEBUG /LTCG /INCREMENTAL:NO /OPT:REF")

	if (TE_64BIT)
		set (TE_LINKER_FLAGS_RELWITHDEBINFO "${TE_LINKER_FLAGS_RELWITHDEBINFO} /OPT:ICF")
		set (TE_LINKER_FLAGS_MINSIZEREL "${TE_LINKER_FLAGS_MINSIZEREL} /OPT:ICF")
		set (TE_LINKER_FLAGS_RELEASE "${TE_LINKER_FLAGS_RELEASE} /OPT:ICF")
	endif()

	set (CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DLL ${TE_LINKER_FLAGS_DEBUG}")
	set (CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} /DLL ${TE_LINKER_FLAGS_DEBUG}")
	set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${TE_LINKER_FLAGS_DEBUG}")

	set (CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} /DLL ${TE_LINKER_FLAGS_RELWITHDEBINFO}")
	set (CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO} /DLL ${TE_LINKER_FLAGS_RELWITHDEBINFO}")
	set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} ${TE_LINKER_FLAGS_RELWITHDEBINFO}")

	set (CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "${CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL} /DLL ${TE_LINKER_FLAGS_MINSIZEREL}")
	set (CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL "${CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL} /DLL ${TE_LINKER_FLAGS_MINSIZEREL}")
	set (CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} ${TE_LINKER_FLAGS_MINSIZEREL}")

	set (CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DLL ${TE_LINKER_FLAGS_RELEASE}")
	set (CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} /DLL ${TE_LINKER_FLAGS_RELEASE}")
	set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${TE_LINKER_FLAGS_RELEASE}")

	# Compiler
	set (TE_COMPILER_FLAGS_COMMON "/GS- /W3 /GR- /WX- /MP /nologo /bigobj /wd\"4577\" /wd\"4530\"")
	set (CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS")

	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${TE_COMPILER_FLAGS_COMMON} /Od /RTC1 /MDd -DDEBUG")

	if (TE_64BIT) # Debug edit and continue for 64-bit
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
	else () # Normal debug for 32-bit
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
	endif ()

	set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${TE_COMPILER_FLAGS_COMMON} /GL /Gy /Zi /O2 /Oi /MD -DDEBUG")
	set (CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${TE_COMPILER_FLAGS_COMMON} /GL /Gy /Zi /O2 /Oi /MD -DNDEBUG")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${TE_COMPILER_FLAGS_COMMON} /GL /Gy /Zi /O2 /Oi /MD -DNDEBUG")

	# Global defines
	#add_definitions (-D_HAS_EXCEPTIONS=0)

elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
	# Note: Optionally add -ffunction-sections, -fdata-sections, but with linker option --gc-sections
	# TODO: Use link-time optimization -flto. Might require non-default linker.
	set (TE_COMPILER_FLAGS_COMMON "-Wall -Wextra -Wno-unused-parameter -fPIC -fno-exceptions -fno-strict-aliasing -fno-rtti -fno-ms-compatibility -msse4.1")

	if (APPLE)
		set (TE_COMPILER_FLAGS_COMMON "${TE_COMPILER_FLAGS_COMMON} -fobjc-arc -std=c++1z")
	endif ()

	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${TE_COMPILER_FLAGS_COMMON} -ggdb -O0 -DDEBUG")
	set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${TE_COMPILER_FLAGS_COMMON} -ggdb -O2 -DDEBUG -Wno-unused-variable")
	set (CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${TE_COMPILER_FLAGS_COMMON} -ggdb -O2 -DNDEBUG -Wno-unused-variable")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${TE_COMPILER_FLAGS_COMMON} -ggdb -O2 -DNDEBUG -Wno-unused-variable")

	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -no-pie")
		set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -no-pie")
		set (CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -no-pie")
		set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -no-pie")
	endif ()

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	# TODO: Use link-time optimization -flto. Might require non-default linker.
	set (TE_COMPILER_FLAGS_COMMON "-Wall -Wextra -Wno-unused-parameter -fPIC -fno-exceptions -fno-strict-aliasing -fno-rtti -msse4.1")

	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${TE_COMPILER_FLAGS_COMMON} -ggdb -O0 -DDEBUG")
	set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${TE_COMPILER_FLAGS_COMMON} -ggdb -O2 -DDEBUG -Wno-unused-variable")
	set (CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${TE_COMPILER_FLAGS_COMMON} -ggdb -O2 -DNDEBUG -Wno-unused-variable")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${TE_COMPILER_FLAGS_COMMON} -ggdb -O2 -DNDEBUG -Wno-unused-variable")

	set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -no-pie")
	set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -no-pie")
	set (CMAKE_EXE_LINKER_FLAGS_MINSIZEDEL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEDEL} -no-pie")
	set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -no-pie")
else()
# TODO_OTHER_COMPILERS_GO_HERE
endif()

# Enable colored output
if (CMAKE_GENERATOR STREQUAL "Ninja")
	check_cxx_compiler_flag ("-fdiagnostics-color=always" F_DIAGNOSTIC_COLOR_ALWAYS)
	if (F_DIAGNOSTIC_COLOR_ALWAYS)
		add_compile_options ("-fdiagnostics-color=always")
	endif ()
endif ()

set (CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC "YES")
set (CMAKE_FIND_FRAMEWORK "LAST")

# Output
if (TE_64BIT)
	set(TE_OUTPUT_DIR_PREFIX x64)
else ()
	set(TE_OUTPUT_DIR_PREFIX x86)
endif ()

set (TE_BINARY_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/bin/${TE_OUTPUT_DIR_PREFIX})
set (TE_LIBRARY_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/lib/${TE_OUTPUT_DIR_PREFIX})

if (TE_TOP_LEVEL)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TE_BINARY_OUTPUT_DIR}/Debug)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TE_BINARY_OUTPUT_DIR}/RelWithDebInfo)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${TE_BINARY_OUTPUT_DIR}/MinSizeRel)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TE_BINARY_OUTPUT_DIR}/Release)

	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TE_BINARY_OUTPUT_DIR}/Debug)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TE_BINARY_OUTPUT_DIR}/RelWithDebInfo)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${TE_BINARY_OUTPUT_DIR}/MinSizeRel)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TE_BINARY_OUTPUT_DIR}/Release)

	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TE_LIBRARY_OUTPUT_DIR}/Debug)
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TE_LIBRARY_OUTPUT_DIR}/RelWithDebInfo)
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${TE_LIBRARY_OUTPUT_DIR}/MinSizeRel)
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TE_LIBRARY_OUTPUT_DIR}/Release)

	set_property (GLOBAL PROPERTY USE_FOLDERS TRUE)
endif()