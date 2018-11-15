 #include "Audio/TeAudio.h"

 namespace te
 {
    TE_CORE_EXPORT Audio& gAudio()
    {
        return Audio::Instance();
    }

	TE_CORE_EXPORT Audio* gAudioPtr()
    {
        return Audio::InstancePtr();
    }
 }