#pragma once

#include "idk/core/platform.hpp"
#include "idk/core/metric.hpp"
#include "idk/core/log.hpp"

namespace idk
{
    class IEngine;


    class PeriodicTimer
    {
    private:
        uint64_t periodNs_;
        uint64_t startTimeNs_;

    public:
        PeriodicTimer(uint64_t rateHz = 1000000000)
        :   periodNs_(0),
            startTimeNs_(idk::platform::GetSysTimeNs())
        {
            setRateHz(rateHz);
        }

        bool expired()
        {
            uint64_t currTimeNs = idk::platform::GetSysTimeNs();
            if (currTimeNs >= startTimeNs_ + periodNs_)
            {
                return true;
            }
            return false;
        }

        void reset()
        {
            startTimeNs_ = idk::platform::GetSysTimeNs();
        }
    
        void setRateHz(uint64_t rateHz)
        {
            periodNs_ = 1000000000 / rateHz;
        }

        template <typename T> T getPeriodNs() { return static_cast<T>(periodNs_); }
        template <typename T> T getPeriodUs() { return static_cast<T>(periodNs_) / T(1000); }
        template <typename T> T getPeriodMs() { return getPeriodUs<T>() / T(1000); }
    };
}

// bool idk::MSecTimer::expired()
// {
//     uint64_t curr, delta;

//     curr = SDL_GetTicks();
//     delta = (curr - prev_);

//     if (delta >= step_msec_)
//     {
//         prev_ = curr;
//         return true;
//     }

//     return false;
// }
