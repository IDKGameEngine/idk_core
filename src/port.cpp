#include "idk/core/port.hpp"

using namespace idk;


// RxMsgEndpoint *TxMsgEndpoint::bind(RxMsgEndpoint *rxer)
// {
//     if (m_rxidx < TxMsgEndpoint::MAX_RXERS)
//     {
//         m_rxers[m_rxidx] = rxer;
//         rxer->addr = m_rxidx++;
//         return rxer;
//     }
//     VLOG_WARN("TxMsgEndpoint was unable to bind RxMsgEndpoint");
//     return nullptr;
// }

// void TxMsgEndpoint::broadcast(const void *msg, size_t msgsz)
// {
//     for (int i=0; i<m_rxidx; i++)
//     {
//         m_rxers[i]->recvmsg(msg, msgsz);
//     }
// }

// void TxMsgEndpoint::multicast(uint32_t mask, const void *msg, size_t msgsz)
// {
//     for (int i=0; i<m_rxidx; i++)
//     {
//         RxMsgEndpoint *rxer = m_rxers[i];

//         if (rxer->addr & mask)
//         {
//             rxer->recvmsg(msg, msgsz);
//         }
//     }
// }

// void TxMsgEndpoint::unicast(uint32_t dest, const void *msg, size_t msgsz)
// {
//     for (int i=0; i<m_rxidx; i++)
//     {
//         RxMsgEndpoint *rxer = m_rxers[i];
//         if (rxer->addr == dest)
//         {
//             rxer->recvmsg(msg, msgsz);
//             break;
//         }
//     }
// }

