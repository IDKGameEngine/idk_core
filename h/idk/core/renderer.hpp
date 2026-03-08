#pragma once

#include "idk/core/window.hpp"
#include "idk/core/service.hpp"


namespace idk::core
{
    class IRenderer: public idk::NonCopyable, public idk::NonMovable
    {
    public:
        virtual ~IRenderer() = default;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;

    private:

    };

}

