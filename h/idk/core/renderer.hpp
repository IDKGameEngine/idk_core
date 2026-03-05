#pragma once

#include "idk/core/type.hpp"
#include "idk/core/window.hpp"


namespace idk::core
{
    class IRenderer;
}


class idk::core::IRenderer: public idk::NonCopyable
{
public:
    virtual ~IRenderer() = default;
    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;

private:

};

