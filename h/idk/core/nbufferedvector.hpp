#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#include <array>
#include <vector>


namespace idk::core
{
    template <typename T, uint8_t NumBufs, size_t MaxObjs>
    class NBufferedVector
    {    
    private:
        const int mN;
        int mCount;
        std::vector<std::vector<T>> mBufs;

    public:
        NBufferedVector()
        :   mN(NumBufs),
            mCount(0)
        {
            static_assert(NumBufs > 0);

            mBufs.resize(NumBufs);
            for (auto &buf: mBufs)
            {
                buf.reserve(MaxObjs);
            }
        }

        int swapBuffers()
        {
            // a b c
            // c a b
            // b c a
            // a b c

            //                          a b c d
            //                     need d a b c
            // swap 0, 1:   a b c d --> b a c d
            // swap 0, 2:   b a c d --> c a b d
            // swap 0, 3:   c a b d --> d a b c
    
            for (int i=mN-1; i>0; i--)
            {
                mBufs[i] = mBufs[i-1];
                // mBufs[i+1].resize(mBufs[i].size());
                // std::memcpy(mBufs[i+i].data(), mBufs[i].data(), mBufs[i].size() * sizeof(T));
            }

            int count = mCount;
            mCount = (mCount + 1) % mN;

            return count;
        }

        auto &front() { return mBufs.front(); }
        auto &back() { return mBufs.back(); }
        const auto &front() const { return mBufs.front(); }
        const auto &back() const { return mBufs.back(); }

    };


    template <typename T>
    class NBufferedVectorWriter
    {
    private:
        T &dst_;

    public:
        NBufferedVectorWriter(T &nbuffer)
        :   dst_(nbuffer) {  }

        void push_back(const auto &x) { dst_.front().push_back(x); }
        void flush() { dst_.swapBuffers(); }

        auto begin() { return dst_.front().begin(); }
        auto end() { return dst_.front().end(); }
    };


    template <typename T>
    class NBufferedVectorReader
    {
    private:
        const T &src_;

    public:
        NBufferedVectorReader(const T &nbuffer)
        :   src_(nbuffer) {  }

        const auto begin() const { return src_.back().begin(); }
        const auto end() const { return src_.back().end(); }
    };

}


