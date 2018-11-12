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

set(TE_UTILITY_INC_PREPREQUISITES
    "Utility/Prerequisites/TePrerequisitesUtility.h"
    "Utility/Prerequisites/TePlatformDefines.h"
    "Utility/Prerequisites/TeForwardDecl.h"
    "Utility/Prerequisites/TeStdHeaders.h"
    "Utility/Prerequisites/TeTypes.h"
)
set(TE_UTILITY_SRC_PREPREQUISITES
)

set(TE_UTILITY_INC_ALLOCATOR
    "Utility/Allocator/TeMemoryAllocator.h"
    "Utility/Allocator/TeBasicAllocator.h"
)
set(TE_UTILITY_SRC_ALLOCATOR
    "Utility/Allocator/TeBasicAllocator.cpp"
)

set(TE_UTILITY_INC_ERROR
    "Utility/Error/TeConsole.h"
    "Utility/Error/TeError.h"
    "Utility/Error/TeDebug.h"
)
set(TE_UTILITY_SRC_ERROR
    "Utility/Error/TeConsole.cpp"
)

set(TE_UTILITY_INC_STRING
    "Utility/String/TeString.h"
)
set(TE_UTILITY_SRC_STRING
    "Utility/String/TeString.cpp"
)

set(TE_UTILITY_INC_UTILITY
    "Utility/Utility/TeDynLib.h"
    "Utility/Utility/TeDynLibManager.h"
    "Utility/Utility/TeModule.h"
    "Utility/Utility/TeNonCopyable.h"
    "Utility/Utility/TeTime.h"
    "Utility/Utility/TeTimer.h"
    "Utility/Utility/TeUtil.h"
    "Utility/Utility/TeUUID.h"
)
set(TE_UTILITY_SRC_UTILITY
    "Utility/Utility/TeDynLib.cpp"
    "Utility/Utility/TeDynLibManager.cpp"
    "Utility/Utility/TeTime.cpp"
    "Utility/Utility/TeTimer.cpp"
    "Utility/Utility/TeUtil.cpp"
    "Utility/Utility/TeUUID.cpp"
)

source_group("ThirdParty" FILES ${TE_UTILITY_INC_THIRDPARTY} ${TE_UTILITY_SRC_THIRDPARTY})
source_group("Math" FILES ${TE_UTILITY_INC_MATH} ${TE_UTILITY_SRC_MATH})
source_group("Prerequisites" FILES ${TE_UTILITY_INC_PREPREQUISITES} ${TE_UTILITY_SRC_PREPREQUISITES})
source_group("Allocator" FILES ${TE_UTILITY_INC_ALLOCATOR} ${TE_UTILITY_SRC_ALLOCATOR})
source_group("Error" FILES ${TE_UTILITY_INC_ERROR} ${TE_UTILITY_SRC_ERROR})
source_group("String" FILES ${TE_UTILITY_INC_STRING} ${TE_UTILITY_SRC_STRING})
source_group("Utility" FILES ${TE_UTILITY_INC_UTILITY} ${TE_UTILITY_SRC_UTILITY})

set(TE_UTILITY_SRC
    ${TE_UTILITY_SRC_MATH}
    ${TE_UTILITY_INC_MATH}
    ${TE_UTILITY_SRC_THIRDPARTY}
    ${TE_UTILITY_INC_THIRDPARTY}
    ${TE_UTILITY_SRC_PREPREQUISITES}
    ${TE_UTILITY_INC_PREPREQUISITES}
    ${TE_UTILITY_SRC_ALLOCATOR}
    ${TE_UTILITY_INC_ALLOCATOR}
    ${TE_UTILITY_SRC_ERROR}
    ${TE_UTILITY_INC_ERROR}
    ${TE_UTILITY_SRC_STRING}
    ${TE_UTILITY_INC_STRING}
    ${TE_UTILITY_SRC_UTILITY}
    ${TE_UTILITY_INC_UTILITY}
)

if (WIN32)

endif ()

if (UNIX)

endif ()