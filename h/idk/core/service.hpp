#pragma once

#include "idk/core/type.hpp"
#include "libidk/log.hpp"
#include <memory>
#include <vector>


namespace idk
{
    class Service;
    class ServiceManager;

    class ServiceManager: public idk::NonCopyable
    {
    private:
        static idk::idtype typeidx_;
        const idk::idtype mTypeIdxBase;
        bool mEnabled;
        // int _typeIdxToArrayIdx(idk::idtype typeidx);

    protected:
        std::vector<idk::Service*> mServices;

    public:
        ServiceManager();
        void update();
        bool running() { return mEnabled; };
        void enable() { mEnabled = true; }
        void disable() { mEnabled = false; }

        template <typename T, typename... Args>
        T *registerService(Args...);

        template <typename T>
        T *getService();
    };


    class Service: public idk::NonCopyable
    {
    public:
        Service();
        virtual ~Service() = default;
        virtual void onUpdate() = 0;
        virtual void onEnable()   {  };
        virtual void onDisable()  {  };

    protected:
        template <typename T>
        T *getService() { return mSrvManager->getService<T>(); }

    private:
        friend class ServiceManager;
        bool mBrandOfSacrifice;
        idk::idtype mTypeIdx;
        ServiceManager *mSrvManager;

    };

}



template <typename T, typename... Args>
inline T *idk::ServiceManager::registerService(Args... args)
{
    static_assert(
        std::is_base_of_v<Service, T>,
        "T must be derivative of idk::Service"
    );

    if (getService<T>())
    {
        VLOG_ERROR("Attempted to register VaneTypeId=={} more than once\n", idk_typeid<T>());
        return nullptr;
    }

    T *srv = new T(args...);
       srv->mBrandOfSacrifice = false;
       srv->mTypeIdx    = idk_typeid<T>();
       srv->mSrvManager = this;
    mServices.push_back(srv);

    // int idx_maybe = _typeIdxToArrayIdx(srv_typeid<T>()); 
    // VLOG_INFO(
    //     "Registered service (TypeIdx, Idx, idx_maybe) == ({}, {}, {})",
    //     srv->mTypeIdx, mServices.size() - 1, idx_maybe
    // );

    return srv;
}


template <typename T>
inline T *idk::ServiceManager::getService()
{
    static_assert(
        std::is_base_of_v<Service, T>,
        "T must be derivative of idk::Service"
    );

    const idk::idtype desired_id = idk_typeid<T>();
    for (auto *srv: mServices)
        if (srv->mTypeIdx == desired_id)
            return static_cast<T*>(srv);
    return nullptr;
}




