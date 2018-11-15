set (TE_D3D11RENDERAPI_INC_NOFILTER
    "TeD3D11RenderAPIPrerequisites.h"
    "TeD3D11RenderAPIFactory.h"
    "TeD3D11RenderAPI.h"
    "TeDDSTextureLoader.h"
)

set (TE_D3D11RENDERAPI_SRC_NOFILTER
    "TeD3D11RenderAPIFactory.cpp"
    "TeD3D11RenderAPI.cpp"
    "TeDDSTextureLoader.cpp"
)

source_group ("" FILES ${TE_D3D11RENDERAPI_SRC_NOFILTER} ${TE_D3D11RENDERAPI_INC_NOFILTER})

set (TE_D3D11RENDERAPI_SRC
    ${TE_D3D11RENDERAPI_INC_NOFILTER}
    ${TE_D3D11RENDERAPI_SRC_NOFILTER}
)