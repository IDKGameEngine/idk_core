#pragma once

#include "idk/core/types.hpp"
#include "idk/core/engine.hpp"
#include "idk/core/periodic_timer.hpp"


namespace idk::core
{
    class Service: public idk::NonCopyable
    {
    protected:
        idk::PeriodicTimer timer_;

    public:
        Service(const idk::PeriodicTimer &t): timer_(t) {  };
        virtual ~Service() = default;
        virtual void _startup(IEngine*) = 0;
        virtual void _update(IEngine*) = 0;
        virtual void _shutdown(IEngine*) = 0;

        void startup(IEngine *E)
        {
            _startup(E);
        }

        void update(IEngine *E)
        {
            timer_.update();
            while (timer_.ready())
            {
                _update(E);
            }
        }

        void shutdown(IEngine *E)
        {
            _shutdown(E);
        }
    };
}

