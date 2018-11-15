#include "TeD3D11RenderAPIFactory.h"
#include "TeD3D11RenderAPI.h"

namespace te
{
    SPtr<RenderAPI> D3D11RenderAPIFactory::create()
    {
        return te_shared_ptr_new<D3D11RenderAPI>();
    }

    const String& D3D11RenderAPIFactory::name() const
    {
        static String StrSystemName = SystemName;
        return StrSystemName;
    }
}