#pragma once

#include "idk/core/type.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>

#include <atomic>
#include <array>
#include <queue>


namespace idk::core
{
    template <typename T> class DoubleBuffer;
    template <typename T> class DblBufferWriter;
    template <typename T> class DblBufferReader;
}



template <typename T>
class idk::core::DoubleBuffer: public idk::NonCopyable, public idk::NonMovable
{
private:
    friend class DblBufferWriter<T>;
    friend class DblBufferReader<T>;

    std::queue<T> data_[2];
    int widx_;
    int ridx_;

    auto *wtget() { return &data_[widx_]; }
    auto *rdget() { return &data_[ridx_]; }

public:
    explicit DoubleBuffer(): widx_(0), ridx_(1) {  }
    void swapBuffers() { std::swap(widx_, ridx_); }

};


template <typename T>
class idk::core::DblBufferWriter
{
private:
    DoubleBuffer<T> &buf_;

public:
    explicit DblBufferWriter(DoubleBuffer<T> &buf): buf_(buf) {  }
    auto *operator->() { return buf_.wtget(); }
};


template <typename T>
class idk::core::DblBufferReader
{
private:
    DoubleBuffer<T> &buf_;

public:
    explicit DblBufferReader(DoubleBuffer<T> &buf): buf_(buf) {  }
    auto *operator->() { return buf_.rdget(); }
};
