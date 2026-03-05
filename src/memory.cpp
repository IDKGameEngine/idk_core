#include "idk/core/memory.hpp"
#include "libidk/align.hpp"
#include <cstdlib>

struct idk::ThreadMemoryRegion
{
    void  *base;
    size_t size;
};

static idk::ThreadMemoryRegion tmr_base_[32];
static idk::ThreadMemoryRegion *tmr_top_ = tmr_base_;

idk::ThreadMemoryRegion const *idk::createThreadMemory(size_t size)
{
    auto *desc = tmr_top_++;
    desc->base = util::align_up(std::malloc(size+16), 16);
    desc->size = size;
    return desc;
}




template <typename T>
class ThreadMemoryWriter
{
private:
    idk::ThreadMemoryRegion &tmr_;

public:
    ThreadMemoryWriter(idk::ThreadMemoryRegion const *tmr)
    :   tmr_(*tmr)
    {

    }

};


template <typename T>
class ThreadMemoryReader
{
private:
    idk::ThreadMemoryRegion &tmr_;

public:
    ThreadMemoryReader(idk::ThreadMemoryRegion const *tmr)
    :   tmr_(*tmr)
    {

    }

};

