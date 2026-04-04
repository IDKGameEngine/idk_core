#include "idk/AppEntry.hpp"
#include "idk/AppRuntime.hpp"
#include "idk/core/log.hpp"

int main(int argc, char **argv)
{
    VLOG_INFO("[main]");

    if (!idk::AppRuntime::Init())
    {
        return 1;
    }

    return idk::AppEntry(argc, argv);
}
