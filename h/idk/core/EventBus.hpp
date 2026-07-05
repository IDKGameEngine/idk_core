#pragma one

#include <vector>


namespace idk
{
    template <typename T>
    struct EventBus
    {
        struct Listener
        {
            using FuncPtr = void (*)(void*, const T&);
            FuncPtr func;
            void *ctx;
        };

        std::vector<Listener> mListeners; // or fixed-size array

        void subscribe(Listener::FuncPtr func, void *ctx)
        {
            mListeners.push_back({func, ctx});
        }

        void publish(const T &data)
        {
            for (auto &L: mListeners)
            {
                L.func(L.ctx, data);
            }
        }
    };
}
