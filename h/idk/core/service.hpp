#pragma once

#include "idk/core/type.hpp"
#include "idk/core/engine.hpp"
#include "idk/core/periodic_timer.hpp"


namespace idk::core
{
    class Service: public idk::NonCopyable
    {
    protected:
        idk::PeriodicTimer timer_;

    public:
        Service(const idk::PeriodicTimer &timer)
        :   timer_(timer) {  };
        virtual ~Service() = default;
        virtual void onUpdate(IEngine*) = 0;
        virtual void onShutdown(IEngine*) = 0;

        void update(IEngine *engine)
        {
            timer_.update();
            while (timer_.ready())
            {
                this->onUpdate(engine);
            }
        }

        void shutdown(IEngine *engine)
        {
            this->onShutdown(engine);
        }
    };
}

