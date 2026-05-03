#pragma once

#include "idk/core/types.hpp"

namespace idk
{
    inline bool statIsCtrlEnabled(const idk::EngineStat stat)
    {
        // engine control only enabled during non-transition states.
        switch (stat)
        {
            case EngineStat::Alive:
            case EngineStat::Dead:
                return true;
            default:
                return false;
        }
    }

    class IEngine: public idk::NonCopyable, public idk::NonMovable
    {
    public:
        virtual ~IEngine() = default;
        virtual bool running() = 0;
        virtual void shutdown() = 0;
        virtual void await_startup() = 0;
        virtual void await_shutdown() = 0;
    };
}
