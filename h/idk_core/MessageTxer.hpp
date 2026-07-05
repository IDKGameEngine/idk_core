#pragma once

#include <cstddef>
#include <cstdint>

namespace idk
{
    class MessageTxer
    {
    public:
        MessageTxer() {}
        virtual ~MessageTxer() = default;
        virtual bool sendMsg(const void *src, size_t size) = 0;
    };
}

