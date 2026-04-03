#pragma once

#include <cstdint>

// #define GetSysTimeMs() SDL_GetTicks()



namespace idk
{
    using GetSysTimeMsFuncPtr = uint64_t (*)(void);

    template <GetSysTimeMsFuncPtr FuncPtr>
    struct GetSysTimeMsFunctorBase
    {

    };
    namespace detail { inline static uint64_t getSysTimeMsDefault() { return 0; } }
    uint64_t (*getSysTimeMs)() = detail::getSysTimeMsDefault;

    class PeriodicTimer
    {
    private:
        uint64_t mPeriodMs;
        uint64_t mPrevMs, mCurrMs;

    public:
    
        PeriodicTimer(uint64_t period_msec)
        :   mPeriodMs(period_msec),
            mPrevMs(getSysTimeMs()),
            mCurrMs(mPrevMs)
        {

        }

        bool expired()
        {
            mCurrMs = getSysTimeMs();
            if (mCurrMs > mPrevMs + mPeriodMs)
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
