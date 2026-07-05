#pragma once

#include "idk_core/metric.hpp"
#include "idk_core/Allocator.hpp"

namespace idk
{
    namespace core
    {
        static inline BumpAllocator<config::memory::STATIC_ALLOCATOR_SIZE> &getStaticAllocator()
        {
            static BumpAllocator<config::memory::STATIC_ALLOCATOR_SIZE> instance;
            return instance;
        }
    }

    template <typename T, typename... Args>
    static inline T *New(Args&&... args)
    {
        return core::getStaticAllocator().New<T>(args...);
    }

    template <typename T>
    static inline T *NewArray(size_t count)
    {
        void *ptr = core::getStaticAllocator().Alloc(count*sizeof(T), alignof(T));
        return reinterpret_cast<T*>(ptr);
    }
}
