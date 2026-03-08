#pragma once

#include "idk/core/window.hpp"
#include "idk/core/service.hpp"


namespace idk::core
{
    class IRenderer: public idk::core::Service
    {
    public:
        virtual ~IRenderer() = default;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;

        // virtual void onUpdate() = 0;
        // virtual void onEnable() = 0;
        // virtual void onDisable() = 0;
        // virtual void onRestart() = 0;
        // virtual void onShutdown() = 0;
    private:

    };

    using IRendererPtr = std::shared_ptr<idk::core::IRenderer>;

}

