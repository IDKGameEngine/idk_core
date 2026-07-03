#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>
#include <memory>
#include "idk/core/log.hpp"


namespace idk
{
    template <typename T>
    class PortReader
    {
    private:
        uint32_t addr;

    public:
        PortReader()
        {
            (void)addr;
        }

        bool read(T &data)
        {

        }
    };

    template <typename T>
    class PortWriter
    {
    protected:

    public:
        bool write(const T &data)
        {

        }

    };
}
