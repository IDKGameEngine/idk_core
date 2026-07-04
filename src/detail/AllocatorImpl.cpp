#include "idk/core/detail/AllocatorImpl.hpp"
#include "idk/core/assert.hpp"
#include "idk/core/log.hpp"
#include "idk/core/stdmem.hpp"

namespace icd = idk::core::detail;


icd::BumpAllocatorImpl::BumpAllocatorImpl(void *base, size_t size)
:   mBase(reinterpret_cast<uintptr_t>(base)),
    mEnd(mBase + size),
    mTail(mBase)
{

}

void *icd::BumpAllocatorImpl::Alloc(size_t size, size_t a=8)
{
    uintptr_t addr = (mTail + (a - 1)) & ~(a - 1);
    mTail = addr + size;
    IDK_ASSERT(mTail <= mEnd, "Out of memory: {} / {} KB", (mTail), mEnd);
    return reinterpret_cast<void*>(addr);
}


void *icd::BumpAllocatorImpl::Calloc(size_t size, size_t a=8)
{
    void *ptr = Alloc(size, a);
    idk_memset(ptr, 0, size);
    return ptr;
}

