#ifndef RECEIVER_INL
#define RECEIVER_INL

#include <iostream>

namespace smarthome
{

inline void Receiver::Receive(Topic const& a_topic) const
{
    m_broadcast.Dispatch(a_topic);
}

} // namespace smarthome

#endif // RECEIVER_INL