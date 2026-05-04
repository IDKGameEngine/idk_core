#include "idk/OsAdapter.hpp"
#include "idk/core/log.hpp"

int main(int argc, char **argv)
{
    VLOG_INFO("[main]");
    srand(clock());

    if (!idk::OsAdapter::PreInit())
    {
        return 1;
    }

    return idk::OsAdapter::AppMain(argc, argv);
}
