set (TE_BULLET_INC_NOFILTER
    "TeBulletPrerequisites.h"
    "TeBullet.h"
)

set (TE_BULLET_SRC_NOFILTER
    "TeBullet.cpp"
    "TeBulletPlugin.cpp"
)

source_group ("" FILES ${TE_BULLET_SRC_NOFILTER} ${TE_BULLET_INC_NOFILTER})

set (TE_BULLET_SRC
    ${TE_BULLET_INC_NOFILTER}
    ${TE_BULLET_SRC_NOFILTER}
)