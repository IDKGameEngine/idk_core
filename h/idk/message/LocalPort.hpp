#pragma once

#include "idk_core/stdmem.hpp"

#include <cstddef>
#include <cstdint>
#include <atomic>


namespace idk::message
{
    template <typename DataType>
    struct LocalPortRegion
    {
        std::atomic<int64_t> lock;
        std::atomic<uint64_t> tick;
        DataType data;

        LocalPortRegion(): lock{0}, tick{0} {}

        uint64_t getLastestTick() const { return tick.load(); }

        bool try_acquire()
        {
            if (0 != lock.fetch_add(1))
            {
                lock.fetch_sub(1);
                return false;
            }
            return true;
        }
    
        void acquire()
        {
            while (!try_acquire()) {  }
        }
    
        void release()
        {
            lock.fetch_sub(1);
        }
    };

    template <typename DATA_TYPE, auto REGION_BASE>
    struct LocalPortAddress
    {
        using DataType = DATA_TYPE;
        static constexpr LocalPortRegion<DATA_TYPE> *RegionBase = REGION_BASE;
    };


    // void exampleWriterThread(LocalPortRegion<1024> *region)
    // {
    //     static char msg[] = "Hello from writer thread!";

    //     while (true)
    //     {
    //         region->acquire();
    //         memcpy(region->data, msg, sizeof(msg));
    //         region->release();
    //     }
    // }

    // void exampleReaderThread(LocalPortRegion<1024> *region)
    // {
    //     static char msg[1024];

    //     while (true)
    //     {
    //         region->acquire();
    //         memcpy(msg, region->data, region->size);
    //         region->release();
    //         printf("msg: %s\n", msg);
    //     }
    // }


    template <typename AddressType>
    class LocalPortWriter
    {
    public:
        bool writeData(const AddressType::DataType *data)
        {
            using DataType = AddressType::DataType;
            using RegionType = LocalPortRegion<DataType>;
            static RegionType *region = reinterpret_cast<RegionType*>(AddressType::RegionBase);
            static auto &tick = region->tick;

            region->acquire();
            idk_memcpy(&(region->data), data, sizeof(DataType));
            tick.store((tick.load() + 1) % (~uint64_t(0) - 1U));
            region->release();
 
            return true;
        }

    };


    template <typename AddressType>
    class LocalPortReader
    {
    private:
        uint64_t mLatestTick;

    public:
        LocalPortReader(): mLatestTick(0) {}

        bool readData(AddressType::DataType *data)
        {
            using DataType = AddressType::DataType;
            using RegionType = LocalPortRegion<DataType>;
            static RegionType *region = reinterpret_cast<RegionType*>(AddressType::RegionBase);

            uint64_t latestTick = region->getLastestTick();
            if (mLatestTick == latestTick) { return false; }
            mLatestTick = latestTick;

            region->acquire();
            idk_memcpy(data, &(region->data), sizeof(DataType));
            region->release();

            return true;
        }

    };


}

