#pragma once

#include <cstdint>

namespace idk::AppRuntime
{
    extern bool Init();
    extern int Entry(int, char**);

    extern uint64_t GetSysTimeMs();
    extern uint64_t GetSysTimeNs();
}
