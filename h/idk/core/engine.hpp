#pragma once

#include "idk/core/types.hpp"
#include "idk/core/cfgparser.hpp"
#include "idk/core/raii.hpp"
#include <vector>

namespace idk
{
    namespace core
    {
        class Service: public idk::NonCopyable, public idk::NonMovable
        {
        private:
            static constexpr size_t MAX_NAME_LENGTH = 64;
            RaiiFunc<void(const char**)> mRaii;
            const idk::IdType mTypeId;
            char mName[MAX_NAME_LENGTH];

        protected:
            const CfgParser::TreeNode &mCfg;

        public:
            Service(const char *name, idk::IdType typeId);
            virtual ~Service() = default;
            virtual void update(IEngine*) = 0;
            virtual void shutdown(IEngine*) = 0;
            idk::IdType getTypeId() const { return mTypeId; }
            const char *getName() const { return &mName[0]; }
        };
    }

    class EngineConfig
    {
    public:
        idk::CfgParser cfgParser;
        EngineConfig() {  }
    };


    class IEngine: public idk::NonCopyable, public idk::NonMovable
    {
    protected:
        std::vector<core::Service*> srvs_;

    public:
        static EngineConfig &getConfig();
        static CfgParser &getCfgParser();

        virtual ~IEngine() = default;
        virtual bool running() = 0;
        virtual void shutdown() = 0;
        virtual void update() = 0;

        template <typename T>
        T *getService()
        {
            for (auto *srv: srvs_)
            {
                if (srv->getTypeId() == idk_typeid<T>())
                {
                    return reinterpret_cast<T*>(srv);
                }
            }
            return nullptr;
        }

    };
}
