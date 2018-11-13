#include "Math/TeBounds.h"
#include "Math/TeRay.h"
#include "Math/TePlane.h"
#include "Math/TeSphere.h"

namespace te
{
    Bounds::Bounds(const AABox& box, const Sphere& sphere)
        :mBox(box), mSphere(sphere)
    { }

    void Bounds::setBounds(const AABox& box, const Sphere& sphere)
    {
        mBox = box;
        mSphere = sphere;
    }

    void Bounds::merge(const Bounds& rhs)
    {
        mBox.merge(rhs.mBox);
        mSphere.merge(rhs.mSphere);
    }

    void Bounds::merge(const Vector3& point)
    {
        mBox.merge(point);
        mSphere.merge(point);
    }

    void Bounds::transform(const Matrix4& matrix)
    {
        mBox.transform(matrix);
        mSphere.transform(matrix);
    }

    void Bounds::transformAffine(const Matrix4& matrix)
    {
        mBox.transformAffine(matrix);
        mSphere.transform(matrix);
    }
}

