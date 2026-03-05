#pragma once


namespace idk::core
{
    struct WindowDesc
    {
        const char *title;
        int width;
        int height;
    };

    class IWindow
    {
    public:
        virtual ~IWindow() = default;
        virtual int   getWidth() const = 0;
        virtual int   getHeight() const = 0;
        virtual bool  shouldClose() const = 0;
        virtual void *getNativeHandle() const = 0;
        virtual void *getGpuContext() const = 0;
        virtual void  pollEvents() = 0;
    };

}
