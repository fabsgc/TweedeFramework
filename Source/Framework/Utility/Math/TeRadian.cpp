#include "Math/TeRadian.h"
#include "Math/TeMath.h"

namespace te
{
    Radian::Radian(const Degree& d) : _rad(d.valueRadians())
    { }

    Radian Radian::wrap()
    {
        _rad = fmod(_rad, Math::TWO_PI);

        if (_rad < 0)
            _rad += Math::TWO_PI;

        return *this;
    }

    Radian& Radian::operator= (const Degree& d)
    {
        _rad = d.valueRadians();
        return *this;
    }

    Radian Radian::operator+ (const Degree& d) const
    {
        return Radian(_rad + d.valueRadians());
    }

    Radian& Radian::operator+= (const Degree& d)
    {
        _rad += d.valueRadians();
        return *this;
    }

    Radian Radian::operator- (const Degree& d) const
    {
        return Radian(_rad - d.valueRadians());
    }

    Radian& Radian::operator-= (const Degree& d)
    {
        _rad -= d.valueRadians();
        return *this;
    }

    float Radian::valueDegrees() const
    {
        return _rad * Math::RAD2DEG;
    }
}
