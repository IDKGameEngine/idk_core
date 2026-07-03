#pragma once

#include "idk/core/types.hpp"

namespace idk
{
    template <typename T, size_t MAX_SIZE>
    class InplaceList : public idk::NonCopyable, public idk::NonMovable
    {
    private:
        T *mBase;
        T *mTail;
        T *mEnd;
        alignas(T) uint8_t mData[sizeof(T) * MAX_SIZE];

    public:
        InplaceList()
        :   mBase(reinterpret_cast<T*>(&mData[0])),
            mTail(mBase),
            mEnd(mBase + MAX_SIZE)
        {

        }

        void push(const T &value)
        {
            if (mTail < mEnd)
            {
                new (mTail++) T(value);
            }
        }

        void pop()
        {
            if (mTail > mBase)
            {
                (--mTail)->~T();
            }
        }

        struct Iterator
        {
            T *mPtr;
            Iterator(T *ptr): mPtr(ptr) {  }
            Iterator(const Iterator &I): mPtr(I.mPtr) {  }
            Iterator &operator++() { mPtr += 1; return *this; }
            Iterator operator++(int) { return Iterator(mPtr + 1); }
            bool operator==(const Iterator &rhs) { return mPtr == rhs.mPtr; }
            bool operator!=(const Iterator &rhs) { return mPtr != rhs.mPtr; }
            T &operator*() { return *mPtr; };
        };

        Iterator begin() { return Iterator(mBase); }
        Iterator end()   { return Iterator(mEnd); }
    };
}
