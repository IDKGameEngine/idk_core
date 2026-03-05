#pragma once

#include <cstddef>
#include <cstdint>

namespace idk
{
    struct ThreadMemoryRegion;
    ThreadMemoryRegion const *createThreadMemory(size_t size);
}


