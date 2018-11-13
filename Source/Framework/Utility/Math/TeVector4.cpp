#include "Math/TeVector4.h"
#include "Math/TeMath.h"

namespace te
{
    const Vector4 Vector4::ZERO{ TE_ZERO() };

    bool Vector4::isNaN() const
    {
        return Math::isNaN(x) || Math::isNaN(y) || Math::isNaN(z) || Math::isNaN(w);
    }
}
