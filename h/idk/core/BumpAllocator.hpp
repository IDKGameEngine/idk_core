#pragma once

#include <cstddef>
#include <cstdint>
#include <stdalign.h>

namespace idk::core
{
    template <size_t MAX_SIZE>
    class BumpAllocator
    {
    private:
        uint8_t *mTail;
        uint8_t mData[MAX_SIZE];

    public:
        BumpAllocator()
        :   mTail(&mData[0])
        {

        }

        template <typename T>
        T *alloc()
        {
            uint8_t *addr = (mTail + (alignof(T) - 1)) & ~(alignof(T) - 1);
            mTail = addr + sizeof(T);
            return reinterpret_cast<T*>(addr);
        }
    };
}


