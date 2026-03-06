#pragma once

#include "idk/core/inplace.hpp"
#include "idk/core/type.hpp"
#include <memory>
#include <vector>

namespace idk::core
{
    enum class ServiceCommand
    {
        Invalid = 0,
        Enable,
        Disable,
        Restart,
        Shutdown
    };

    class Service;
    class ServiceManager;

    class ServiceManager: public idk::NonCopyable
    {
    public:
        ServiceManager();
        void update();
        bool running();
        void shutdown();

        template <typename T, typename... Args>
        T *registerService(Args...);

        template <typename T>
        T *getService();

        template <typename T>
        void srvCmdToSrv(ServiceCommand);
        void srvCmdToAll(ServiceCommand);

    protected:
        std::vector<idk::core::Service*> mServices;

    private:
        static idk::idtype typeidx_;
        const idk::idtype typeIdxBase_;
        bool running_;
        bool shutdown_;
        int _typeIdxToArrayIdx(idk::idtype typeidx);
        void _shutdownAll();
        void _shutdownBranded();

    };


    class Service: public idk::NonCopyable
    {
    private:
        friend class ServiceManager;
        bool mBrandOfSacrifice;
        idk::idtype mTypeIdx;
        ServiceManager *mSrvManager;

    protected:
        template <typename T>
        void srvCmdToSrv(ServiceCommand cmd) { mSrvManager->srvCmdToSrv<T>(cmd); }
        void srvCmdToAll(ServiceCommand cmd) { mSrvManager->srvCmdToAll(cmd); }

        template <typename T>
        T *getService() { return mSrvManager->getService<T>(); }

    public:
        Service(): mBrandOfSacrifice(false) {  };
        virtual ~Service() = default;
        virtual void onUpdate() = 0;
        virtual void onEnable() = 0;
        virtual void onDisable() = 0;
        virtual void onRestart() = 0;
        virtual void onShutdown() = 0;

    };

}



template <typename T, typename... Args>
inline T *idk::core::ServiceManager::registerService(Args... args)
{
    static_assert(
        std::is_base_of_v<Service, T>,
        "T must be derivative of idk::core::Service"
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

    int idx_maybe = _typeIdxToArrayIdx(idk_typeid<T>()); 

    VLOG_INFO(
        "Registered service (TypeIdx, Idx, idx_maybe) == ({}, {}, {})",
        srv->mTypeIdx, mServices.size() - 1, idx_maybe
    );

    return srv;
}


template <typename T>
inline T *idk::core::ServiceManager::getService()
{
    static_assert(
        std::is_base_of_v<Service, T>,
        "T must be derivative of idk::core::Service"
    );

    const idk::idtype desired_id = idk_typeid<T>();
    for (auto *srv: mServices)
        if (srv->mTypeIdx == desired_id)
            return static_cast<T*>(srv);
    return nullptr;
}


template <typename T>
inline void idk::core::ServiceManager::srvCmdToSrv(idk::core::ServiceCommand cmd)
{
    auto *srv = static_cast<Service*>(getService<T>());
    if (srv == nullptr)
    {
        VLOG_FATAL("Could not find service");
        return;
    }

    switch (cmd)
    {
        default: VLOG_WARN("Invalid idk::core::ServiceCommand"); break;
        case ServiceCommand::Enable:   srv->onEnable();   break;
        case ServiceCommand::Disable:  srv->onDisable();  break;
        case ServiceCommand::Restart:  srv->onRestart();  break;
        case ServiceCommand::Shutdown: srv->mBrandOfSacrifice = true; break;
    }
}


inline void idk::core::ServiceManager::srvCmdToAll(idk::core::ServiceCommand cmd)
{
    #define LAZYAF(Cmd_) for (auto *srv: mServices) { srv->on##Cmd_(); }

    switch (cmd)
    {
        default: VLOG_WARN("Invalid idk::core::ServiceCommand"); break;
        case ServiceCommand::Enable:   LAZYAF(Enable);   break;
        case ServiceCommand::Disable:  LAZYAF(Disable);  break;
        case ServiceCommand::Restart:  LAZYAF(Restart);  break;
        case ServiceCommand::Shutdown: this->shutdown(); break;
    }

    #undef LAZYAF
}



