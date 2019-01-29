set (TE_OPENAUDIO_INC_NOFILTER
    "TeOpenAudioPrerequisites.h"
    "TeOpenAudio.h"
    "TeOpenAudioImporter.h"
)

set (TE_OPENAUDIO_SRC_NOFILTER
    "TeOpenAudio.cpp"
    "TeOpenAudioPlugin.cpp"
    "TeOpenAudioImporter.cpp"
)

source_group ("" FILES ${TE_OPENAUDIO_SRC_NOFILTER} ${TE_OPENAUDIO_INC_NOFILTER})

set (TE_OPENAUDIO_SRC
    ${TE_OPENAUDIO_INC_NOFILTER}
    ${TE_OPENAUDIO_SRC_NOFILTER}
)