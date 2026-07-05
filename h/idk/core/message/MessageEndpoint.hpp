#pragma once

#include <cstddef>
#include <cstdint>

namespace idk::core
{
    class MessageEndpoint
    {
    public:
        MessageEndpoint() {}
        virtual ~MessageEndpoint() = default;
        virtual size_t sendTo(const void *dst, size_t size) = 0;
        virtual size_t recvFrom(void *src, size_t size) = 0;
        
    };
}

