#pragma once

#include "idk/core/metric.hpp"
#include "idk/core/Allocator.hpp"

namespace idk
{
    static constexpr size_t ALLOCATOR_SIZE = 1 * idk::MEGA;

    namespace core::detail
    {
        using AllocatorType = idk::core::BumpAllocator<ALLOCATOR_SIZE>;
        static inline AllocatorType &getAllocator()
        {
            static AllocatorType instance;
            return instance;
        }
    }

    template <typename T, typename... Args>
    static inline T *New(Args&&... args)
    {
        namespace cd = core::detail;
        return cd::getAllocator().New<T>(args...);
    }

    template <typename T>
    static inline T *NewArray(size_t count)
    {
        namespace cd = core::detail;
        void *ptr = cd::getAllocator().Alloc(count*sizeof(T), alignof(T));
        return reinterpret_cast<T*>(ptr);
    }
}
