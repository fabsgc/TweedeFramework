#include "Math/TeLine2.h"
#include "Math/TeMath.h"

namespace te
{
    std::pair<bool, float> Line2::intersects(const Line2& rhs) const
    {
        Vector2 diff = rhs.getOrigin() - getOrigin();
        Vector2 perpDir = rhs.getDirection();
        perpDir = Vector2(perpDir.y, -perpDir.x);

        float dot = getDirection().dot(perpDir);
        if (std::abs(dot) > 1.0e-4f) // Not parallel
        {
            float distance = diff.dot(perpDir) / dot;

            return std::make_pair(true, distance);
        }
        else // Parallel
        {
            return std::make_pair(true, 0.0f);
        }
    }
}