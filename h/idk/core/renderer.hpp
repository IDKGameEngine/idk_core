#pragma once

#include "idk/core/window.hpp"


namespace idk::core
{
    class IRenderer: public idk::NonCopyable
    {
    public:
        virtual ~IRenderer() = default;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual void onShutdown() = 0;

    private:

    };
}

