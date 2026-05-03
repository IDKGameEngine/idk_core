#pragma once

#include "idk/core/metric.hpp"
#include "idk/AppRuntime.hpp"

namespace idk
{
    class IEngine;


    class PeriodicTimer
    {
    private:
        const uint64_t period_;
        uint64_t accum_;
        uint64_t prev_;

    public:
        PeriodicTimer(double period_msec)
        :   period_ (idk::time::msec_to_nsec(period_msec)),
            accum_  (0),
            prev_   (AppRuntime::GetSysTimeNs())
        {

        }

        void update()
        {
            uint64_t curr = AppRuntime::GetSysTimeNs();
            accum_ += (curr - prev_);
            prev_   = curr;
        }

        bool ready()
        {
            if (accum_ > period_)
            {
                accum_ -= period_;
                return true;
            }
            return false;
        }

        template <typename T> T getPeriodNs() { return static_cast<T>(period_); }
        template <typename T> T getPeriodUs() { return static_cast<T>(period_) / T(1000); }
        template <typename T> T getPeriodMs() { return getPeriodUs<T>() / T(1000); }

        // bool expired()
        // {
        //     mCurrMs = AppRuntime::GetSysTimeMs();
        //     if (mCurrMs > mPrevMs + stepMs)
        //     {
        //         mPrevMs = mCurrMs;
        //         return true;
        //     }
        //     return false;
        // }
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
