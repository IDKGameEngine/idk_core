#pragma once

#include "idk/core/renderer.hpp"


namespace idk::core
{
    class IPlatform: public idk::NonCopyable
    {
    public:
        virtual ~IPlatform() = default;
        virtual void update() = 0;
        virtual void shutdown() = 0;
        virtual bool running() = 0;
        virtual core::IWindow *getWindow() = 0;
        // virtual core::IRenderer *createRenderer(core::IWindow*) = 0;
    };
}

