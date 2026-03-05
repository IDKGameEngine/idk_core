#include "idk/core/service.hpp"

idk::idtype idk::ServiceManager::typeidx_ = 0;


idk::ServiceManager::ServiceManager()
:   mTypeIdxBase(ServiceManager::typeidx_),
    mEnabled(true)
{

}


// int idk::ServiceManager::_typeIdxToArrayIdx(idk::idtype typeidx)
// {
//     size_t idx = typeidx - mTypeIdxBase;

//     if (!(idx < mServices.size()))
//     {
//         return -1;
//     }

//     return idx;
// }


void idk::ServiceManager::update()
{
    for (auto *srv: mServices)
    {
        srv->onUpdate();
    }

    for (int i=mServices.size()-1; i>=0; i--)
    {
        if (mServices[i]->mBrandOfSacrifice)
        {
            std::swap(mServices[i], mServices.back());
            delete mServices.back();
            mServices.pop_back();
        }
    }
}




idk::Service::Service()
:   mBrandOfSacrifice(false)
{

}


