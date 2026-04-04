#pragma once

#include "idk/AppRuntime.hpp"

namespace idk
{
    template <uint64_t RateHz>
    class PeriodicTimer
    {
    private:
        uint64_t mPrevMs, mCurrMs;

    public:
        static constexpr uint64_t rateHz = RateHz;
        static constexpr uint64_t stepMs = 1000U / RateHz;

        PeriodicTimer()
        :   mPrevMs(AppRuntime::GetSysTimeMs()),
            mCurrMs(mPrevMs)
        {

        }

        bool expired()
        {
            mCurrMs = AppRuntime::GetSysTimeMs();
            if (mCurrMs > mPrevMs + stepMs)
            {
                mPrevMs = mCurrMs;
                return true;
            }
            return false;
        }
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
