#pragma once

#include "idk/core/type.hpp"
#include "idk/core/engine.hpp"


namespace idk::core
{
    class Service: public idk::NonCopyable
    {
    public:
        Service() = default;
        virtual ~Service() = default;
        virtual void onUpdate(IEngine*) = 0;
        virtual void onShutdown(IEngine*) = 0;

    };
}

