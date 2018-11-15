#include "TeRenderManFactory.h"
#include "TeRenderMan.h"

namespace te
{
    SPtr<Renderer> RenderManFactory::create()
    {
        return te_shared_ptr_new<RenderMan>();
    }

    const String& RenderManFactory::name() const
    {
        static String StrSystemName = SystemName;
        return StrSystemName;
    }
}