#ifndef I_BROADCAST_H
#define I_BROADCAST_H

#include "i_event.hpp" // event
#include "Common.hpp" // uncpoyable
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

class IBroadcast : public advcpp::UnCopyable
{
public:
    virtual ~IBroadcast() noexcept = 0;
    virtual void Dispatch(SharedPointer<IEvent> a_event) = 0;
    virtual void ShutDown() = 0;

protected:
    IBroadcast() = default;
    IBroadcast(const IBroadcast & a_ibroadcast) = default;
    IBroadcast & operator = (const IBroadcast & a_ibroadcast) = default;

};



} // namespace smart_home

#include "inl/i_broadcast.inl"
#endif //  I_BROADCAST_H