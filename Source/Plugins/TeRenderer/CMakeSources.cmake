set (TE_RENDERER_INC_NOFILTER
    "TeRendererPrerequisites.h"
    "TeRenderer.h"
)

set (TE_RENDERER_SRC_NOFILTER
    "TeRenderer.cpp"
)

source_group ("" FILES ${TE_RENDERER_SRC_NOFILTER} ${TE_RENDERER_INC_NOFILTER})

set (TE_RENDERER_SRC
    ${TE_RENDERER_INC_NOFILTER}
    ${TE_RENDERER_SRC_NOFILTER}
)