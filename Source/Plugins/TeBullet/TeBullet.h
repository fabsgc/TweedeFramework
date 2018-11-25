#pragma once

#include "TeBulletPrerequisites.h"
#include "Physics/TePhysics.h"

namespace te
{
    class Bullet: public Physics
    {
    public:
        Bullet();
        ~Bullet();

        void Update() override;
    };
}