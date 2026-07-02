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
    class PortReader;
    
    template <typename T>
    class PortWriter;
}


template <typename T>
class idk::PortReader
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
class idk::PortWriter
{
protected:

public:
    bool write(const T &data)
    {

    }

};

