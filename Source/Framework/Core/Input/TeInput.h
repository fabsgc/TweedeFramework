#pragma once

#include "TeCorePrerequisites.h"
#include "Utility/TeModule.h"
#include "Utility/TeEvent.h"

namespace te
{
    class Mouse;
    class Keyboard;
    class Gamepad;

    class TE_CORE_EXPORT Input : public Module<Input>
    {
    public:
        Input();
        ~Input();

        void Update();
    };

    /**	Provides easy access to Input. */
    TE_CORE_EXPORT Input& gInput();
    TE_CORE_EXPORT Input* gInputPtr();
}