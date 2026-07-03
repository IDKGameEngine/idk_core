#pragma once

#include "idk/core/types.hpp"

namespace idk
{
    template <typename T, size_t MAX_SIZE>
    class InplaceList : public idk::NonCopyable, public idk::NonMovable
    {
    private:
        size_t mSize;
        T mData[MAX_SIZE];

    public:
        InplaceList()
        :   mSize(0)
        {

        }

        void push(const T &value)
        {
            if (mSize < MAX_SIZE)
            {
                new (&mData[mSize++]) T(value);
            }
        }

        void pop()
        {
            if (mSize > 0)
            {
                mData[--mSize].~T();
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

        Iterator begin() { return Iterator(mData); }
        Iterator end()   { return Iterator(mData + mSize); }
    };
}
