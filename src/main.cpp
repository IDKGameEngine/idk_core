#include "idk/AppEntry.hpp"
#include "idk/AppRuntime.hpp"

int main(int argc, char **argv)
{
    VLOG_INFO("[main]");

    if (!idk::AppRuntime::Init())
    {
        return 1;
    }

    return idk::AppEntry::AppEntry(argc, argv);
}
