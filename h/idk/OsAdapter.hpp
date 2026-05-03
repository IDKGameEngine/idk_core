#pragma once

#include <cstdint>

namespace idk::OsAdapter
{
    extern bool PreInit();
    extern int  AppMain(int, char**);

    extern uint64_t GetSysTimeMs();
    extern uint64_t GetSysTimeNs();
}
