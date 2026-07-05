// #pragma once

// #include "idk/core/InplaceList.hpp"

// namespace idk
// {
//     template <typename T>
//     struct EventListener
//     {
//         void (*func)(void*, const T&);
//         void *ctx;
//     };

//     template <typename T, size_t MAX_LISTENERS=64>
//     class EventChannel
//     {
//     public:
//         idk::InplaceList<EventListener<T>, MAX_LISTENERS> mListeners;
//         // std::vector<EventListener<T>> mListeners; // or fixed-size array

//         void subscribe(void (*func)(void*, const T&), void *ctx)
//         {
//             mListeners.push({func, ctx});
//         }

//         void publish(const T &data)
//         {
//             for (EventListener<T> &obj: mListeners)
//             {
//                 obj.func(obj.ctx, data);
//             }
//         }
//     };
// }
