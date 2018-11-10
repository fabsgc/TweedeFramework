set (TE_CORE_INC_RENDERAPI
    "Core/RenderAPI/TeRenderAPI.h"
)

set (TE_CORE_SRC_RENDERAPI
    "Core/RenderAPI/TeRenderAPI.cpp"
)

source_group("RenderAPI" FILES ${TE_CORE_INC_RENDERAPI} ${TE_CORE_SRC_RENDERAPI})

set(TE_CORE_SRC
	${TE_CORE_SRC_RENDERAPI}
	${TE_CORE_INC_RENDERAPI}
)

if (WIN32)

endif ()

if (UNIX)

endif ()