#include "Input/TeInput.h"

namespace te
{
    Input::Input()
    {
    }

    Input::~Input()
    {
    }

    Input& gInput()
    {
        return Input::Instance();
    }

    Input* gInputPtr()
    {
        return Input::InstancePtr();
    }
}