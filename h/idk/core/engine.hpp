#pragma once

#include "idk/core/types.hpp"
#include <vector>

namespace idk
{
    namespace core
    {
        class Service: public idk::NonCopyable, public idk::NonMovable
        {
        private:
            const idk::IdType mTypeId;

        public:
            Service(idk::IdType typeId): mTypeId(typeId) {  };
            virtual ~Service() = default;
            virtual void startup(IEngine*) = 0;
            virtual void update(IEngine*) = 0;
            virtual void shutdown(IEngine*) = 0;

            idk::IdType getTypeId() const { return mTypeId; }
        };
    }

    class IEngine: public idk::NonCopyable, public idk::NonMovable
    {
    protected:
        std::vector<core::Service*> srvs_;

    public:
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
