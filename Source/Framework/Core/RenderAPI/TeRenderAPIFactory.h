#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
    /** Factory class that you may specialize in order to start up a specific render system. */
    class RenderAPIFactory
    {
    public:
        virtual ~RenderAPIFactory() { }

		/**	Creates and starts up the render system managed by this factory.  */
		virtual SPtr<RenderAPI> Create() = 0;

		/**	Returns the name of the render system this factory creates. */
		virtual const String& Name() const = 0;
    };
}