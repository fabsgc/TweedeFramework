# Source files and their filters
include (CMakeSources.cmake)
    
# Target
add_library (TeD3D11RenderAPI SHARED ${TE_D3D11RENDERAPI_SRC})

# Defines
target_compile_definitions (TeD3D11RenderAPI PRIVATE -DTE_D3D11_EXPORTS)

# Includes
target_include_directories (TeD3D11RenderAPI PRIVATE "./")

# Libraries
if(BS_64BIT)
    link_directories ("$(DXSDK_DIR)Lib/x64")
else()
    link_directories ("$(DXSDK_DIR)Lib/x86")
endif()
    
## External lib: DirectX 11
target_link_libraries (TeD3D11RenderAPI d3d11 dxgi dxguid D3DCompiler)  
    
## Local libs
target_link_libraries (TeD3D11RenderAPI tef)

# IDE specific
set_property (TARGET TeD3D11RenderAPI PROPERTY FOLDER Plugins)

# Install
if(RENDER_API_MODULE MATCHES "DirectX 11" AND !WIN32)
    install_tef_target(TeD3D11RenderAPI)
endif()