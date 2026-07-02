#pragma once

#include <atomic>
#include <mutex>
#include <thread>

#include "idk/core/types.hpp"

namespace idk::core
{
    template <uint8_t NUM_THREADS>
    class ThreadPool
    {
    public:
        ThreadPool();

    private:
        struct ThreadArgs
        {
            IdType id;
            // uint8_t data[32];

            ThreadArgs() : id(-1){};
            ThreadArgs(IdType tid) : id(tid){};
        };

        std::thread threads_[NUM_THREADS];
        ThreadArgs threadArgs_[NUM_THREADS];

        static void threadMain(const ThreadArgs &);
    };
}  // namespace idk::core

template <uint8_t N>
idk::core::ThreadPool<N>::ThreadPool()
{
    for (uint8_t i = 0; i < N; i++)
    {
        threadArgs_[i] = ThreadArgs(i);
        threads_[i] =
            std::thread(ThreadPool<N>::threadMain, std::ref(threadArgs_[i]));
        threads_[i].detach();
    }
}

template <uint8_t N>
void idk::core::ThreadPool<N>::threadMain(const ThreadArgs &args)
{
    (void)args;
}
