#pragma once

#include "idk/core/types.hpp"
#include "idk/core/cfgparser.hpp"
#include "idk/core/raii.hpp"
#include <vector>

namespace idk
{
    namespace core
    {
        class Service;
    }

    class EngineConfig
    {
    public:
        idk::CfgParser cfgParser;
        EngineConfig() {  }
    };


    class IEngine: public idk::NonMobile
    {
    protected:
        virtual core::Service *_getService(idk::IdType id) = 0;

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
            return reinterpret_cast<T*>(_getService(idk_typeid<T>()));
        }

    };
}
