set(TE_UTILITY_INC_THIRDPARTY
    "Utility/ThirdParty/Md5/md5.h"
    "Utility/ThirdParty/Json/json.h"
    "Utility/ThirdParty/TinyXml/tinyxml2.h"
)

set(TE_UTILITY_SRC_THIRDPARTY
    "Utility/ThirdParty/Md5/md5.cpp"
    "Utility/ThirdParty/TinyXml/tinyxml2.cpp"
)

set(TE_UTILITY_INC_MATH
    "Utility/Math/TeVector2I.h"
)

set(TE_UTILITY_SRC_MATH
    "Utility/Math/TeVector2I.cpp"
)

source_group("ThirdParty" FILES ${TE_UTILITY_INC_THIRDPARTY} ${TE_UTILITY_SRC_THIRDPARTY})
source_group("Math" FILES ${TE_UTILITY_INC_MATH} ${TE_UTILITY_SRC_MATH})

set(TE_UTILITY_SRC
    ${TE_UTILITY_SRC_MATH}
    ${TE_UTILITY_INC_MATH}
    ${TE_UTILITY_SRC_THIRDPARTY}
    ${TE_UTILITY_INC_THIRDPARTY}
)

if (WIN32)

endif ()

if (UNIX)

endif ()