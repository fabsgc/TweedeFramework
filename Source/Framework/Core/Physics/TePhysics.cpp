 #include "Physics/TePhysics.h"

 namespace te
 {
    TE_CORE_EXPORT Physics& gPhysics()
    {
        return Physics::Instance();
    }

	TE_CORE_EXPORT Physics* gPhysicsPtr()
    {
        return Physics::InstancePtr();
    }
 }