#pragma once

#include "idk/core/type.hpp"


namespace idk
{
    enum class EngineStat: uint8_t
    {
        Invalid = 0,
        Alive,
        Dead,
        Starting,
        Stopping,
    };

    enum class EngineCtrl: uint8_t
    {
        None = 0,
        Start,
        Stop
    };

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

    namespace core
    {
        class IEngine;
    }
}


class idk::core::IEngine: public idk::NonCopyable, public idk::NonMovable
{
private:

public:
    virtual ~IEngine() = default;
    virtual void update() = 0;
    virtual void shutdown() = 0;

    /**
     * @return true if successful/acknowledged.
     */
    virtual bool set_ctrl(EngineCtrl) = 0;
    virtual EngineStat get_stat() = 0;

};

