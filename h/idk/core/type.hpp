#pragma once

#include <cstddef>
#include <cstdint>


namespace idk
{
    using idtype = int32_t;

    class NonCopyable;
    class NonMovable;

    namespace detail
    {
        struct typeid_impl
        {
            inline static idtype value_ = 0;
        };
    }
}



class idk::NonCopyable
{
public:
    NonCopyable() = default;
    ~NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable &operator=(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = default;
    NonCopyable &operator=(NonCopyable&&) = default;
};


class idk::NonMovable
{
public:
    NonMovable() = default;
    ~NonMovable() = default;
    NonMovable(const NonMovable&) = default;
    NonMovable &operator=(const NonMovable&) = default;
    NonMovable(NonMovable&&) = delete;
    NonMovable &operator=(NonMovable&&) = delete;
};


template <typename T>
inline idk::idtype idk_typeid()
{
    static const idk::idtype id = idk::detail::typeid_impl::value_++;
    return id;
}

