#include "TeGLRenderAPIFactory.h"
#include "TeGLRenderAPI.h"

namespace te
{
    SPtr<RenderAPI> GLRenderAPIFactory::create()
    {
        return te_shared_ptr_new<GLRenderAPI>();
    }

    const String& GLRenderAPIFactory::name() const
    {
        static String StrSystemName = SystemName;
        return StrSystemName;
    }
}