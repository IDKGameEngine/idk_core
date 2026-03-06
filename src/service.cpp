#include "idk/core/service.hpp"

idk::idtype idk::core::ServiceManager::typeidx_ = 0;


idk::core::ServiceManager::ServiceManager()
:   typeIdxBase_(ServiceManager::typeidx_),
    running_(true),
    shutdown_(false)
{

}

int idk::core::ServiceManager::_typeIdxToArrayIdx(idk::idtype typeidx)
{
    idk::idtype idx = typeidx - typeIdxBase_;

    if (!((size_t)idx < mServices.size()))
    {
        return -1;
    }

    return idx;
}

void idk::core::ServiceManager::_shutdownAll()
{
    for (auto *srv: mServices)
        srv->mBrandOfSacrifice = true;
    _shutdownBranded();
}

void idk::core::ServiceManager::_shutdownBranded()
{
    int sz = int(mServices.size());
    for (int i=sz-1; i>=0; i--)
    {
        if (mServices[i]->mBrandOfSacrifice)
        {
            std::swap(mServices[i], mServices.back());
            delete mServices.back();
            mServices.pop_back();
        }
    }
}

void idk::core::ServiceManager::update()
{
    for (auto *srv: mServices)
    {
        srv->onUpdate();
    }

    _shutdownBranded();

    if (shutdown_)
    {
        running_ = false;
        _shutdownAll();
    }
}

bool idk::core::ServiceManager::running()
{
    return running_;
}

void idk::core::ServiceManager::shutdown()
{
    shutdown_ = true;
}

