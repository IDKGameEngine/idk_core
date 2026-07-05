#pragma once

namespace idk
{
    template <typename T, typename... Args>
    static inline T *New(Args&&... args)
    {
        namespace cm = idk::config::memory;
        return cm::getAllocator().New<T>(args...);
    }

    template <typename T>
    static inline T *NewArray(size_t count)
    {
        namespace cm = idk::config::memory;
        void *ptr = cm::getAllocator().Alloc(count*sizeof(T), alignof(T));
        return reinterpret_cast<T*>(ptr);
    }
}
