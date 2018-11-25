#include "TeGLRenderAPIFactory.h"
#include "TeGLRenderAPI.h"

namespace te
{
    SPtr<RenderAPI> GLRenderAPIFactory::Create()
    {
        return te_shared_ptr_new<GLRenderAPI>();
    }

    const String& GLRenderAPIFactory::Name() const
    {
        static String StrSystemName = SystemName;
        return StrSystemName;
    }
}