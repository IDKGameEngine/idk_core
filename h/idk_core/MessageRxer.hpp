#pragma once

#include <cstddef>
#include <cstdint>

namespace idk
{
    class MessageRxer
    {
    public:
        MessageRxer() {}
        virtual ~MessageRxer() = default;
        virtual bool recvMsg(void *dst, size_t size) = 0;
    };
}

