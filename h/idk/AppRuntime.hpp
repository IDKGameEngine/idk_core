#pragma once

#include <cstddef>
#include <cstdint>
#include "idk/core/log.hpp"

namespace idk::AppRuntime
{
    extern bool Init();
    extern uint64_t GetSysTimeMs();
    extern uint64_t GetSysTimeNs();
}
