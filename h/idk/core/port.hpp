#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>
#include <memory>
#include "idk/core/log.hpp"


namespace idk
{
    class RxMsgEndpoint;
    class TxMsgEndpoint;

    template <typename T>
    class RxSamplePort;
    
    template <typename T>
    class TxSamplePort;
}


class idk::RxMsgEndpoint
{
private:
    friend class idk::TxMsgEndpoint;
    uint32_t addr;

public:
    virtual void recvmsg(const void*, size_t) = 0;
};


class idk::TxMsgEndpoint
{
protected:
    uint32_t m_rxaddr;
    std::vector<std::shared_ptr<RxMsgEndpoint>> m_rxers;

public:
    TxMsgEndpoint(): m_rxaddr(0) {  }

    template <typename RxType>
    std::shared_ptr<RxType> makeRxEndpoint()
    {
        static_assert(
            std::is_base_of_v<RxMsgEndpoint, RxType>,
            "RxType must be derivative of idk::RxMsgEndpoint"
        );

        auto rxer = std::shared_ptr<RxType>(new RxType());
             rxer->addr = m_rxaddr++;
        m_rxers.push_back(rxer);

        return rxer;
    }

    // void broadcast(const void *msg, size_t msgsz);
    // void multicast(uint32_t mask, const void *msg, size_t msgsz);
    // void unicast(uint32_t dest, const void *msg, size_t msgsz);

    // template <typename T>
    // void sendmsg_bcast(const T &p) { sendmsg_bcast(&p, sizeof(T)); }

};





template <typename T>
class idk::RxSamplePort: public idk::RxMsgEndpoint
{
private:
    bool ready_;
    T data_[1];

public:
    RxSamplePort(): ready_(false) {  };

    virtual void recvmsg(const void *msg, size_t msgsz) final
    {
        if (msgsz != sizeof(T))
        {
            VLOG_ERROR("RxSamplePortT msgsz != sizeof(T)");
            return;
        }

        std::memcpy(data_, msg, sizeof(T));
        ready_ = true;
    }

    bool read(T *data)
    {
        if (!ready_)
            return false;

        ready_ = false;
        memcpy(data, data_, sizeof(T));
        return true;
    }

    bool ready() const
    {
        return ready_;
    }

    T *data()
    {
        ready_ = false;
        return &data_[0];
    }

};



template <typename T>
class idk::TxSamplePort: public idk::TxMsgEndpoint
{
public:
    void write(const T *data)
    {
        for (auto &rxer: m_rxers)
        {
            rxer->recvmsg(data, sizeof(T));
        }
    }
};

