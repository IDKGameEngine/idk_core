#pragma once

#include "idk/core/type.hpp"


namespace idk::core
{
    class IGame: public idk::NonCopyable, public idk::NonMovable
    {
    public:
        virtual void update() = 0;
    };
}

