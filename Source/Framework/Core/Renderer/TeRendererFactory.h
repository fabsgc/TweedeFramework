#pragma once

#include "TeCorePrerequisites.h"

namespace te
{
    /**
     * Factory class for creating Renderer objects. Implement this class for any custom renderer classes you may have, and
     * register it with renderer manager.
     *
     * @see		RendererManager
     */
    class RendererFactory
    {
    public:
        virtual ~RendererFactory() { }

        /**	Creates a new instance of the renderer. */
        virtual SPtr<Renderer> create() = 0;

        /**	Returns the name of the renderer this factory creates. */
        virtual const String& name() const = 0;
    };
}