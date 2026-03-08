#pragma once

#include "idk/core/renderer.hpp"


namespace idk::core
{
    class IPlatform: public idk::core::Service
    {
    public:
        virtual ~IPlatform() = default;
        virtual const core::IWindowPtr &getWindow() = 0;
        // virtual void update() = 0;
        // virtual void shutdown() = 0;
        // virtual bool running() = 0;
        // virtual core::IRenderer *createRenderer(core::IWindow*) = 0;
    };

    using IPlatformPtr = std::shared_ptr<idk::core::IPlatform>;
}

