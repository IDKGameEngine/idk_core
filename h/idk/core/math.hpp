#pragma once

#include <cstdint>
#include <cstddef>

namespace idk
{
    template <typename T>
    T min(T x, T y)
    {
        return (x < y) ? x : y;
    }

    template <typename T>
    T max(T x, T y)
    {
        return (x > y) ? x : y;
    }

    template <typename T>
    T clamp(T x, T lo, T hi)
    {
        return idk::max(lo, idk::min(x, hi));
    }

    template <typename T>
    T lerp(T x, T y, T a)
    {
        return x + a*(y - x);
    }
}

