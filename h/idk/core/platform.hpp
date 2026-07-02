#pragma once

#include <cstdint>

namespace idk::platform
{
    extern bool AppInit();
    extern int  AppEntry(int, char**);

    extern uint64_t GetSysTimeMs();
    extern uint64_t GetSysTimeNs();
}
