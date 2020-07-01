#ifndef I_SUBSCRIBES_LIST_DISPATCHER_H
#define I_SUBSCRIBES_LIST_DISPATCHER_H

#include "shared_pointer.hpp"
#include "i_event.hpp"

using namespace advcpp;


namespace smarthome
{

class ISubscribersListDispatcher
{
public:
    virtual ~ISubscribersListDispatcher() = default;
    virtual void Dispatch(SharedPointer<IEvent> a_ievent) = 0;

protected:
    ISubscribersListDispatcher() = default;
    ISubscribersListDispatcher(const ISubscribersListDispatcher & a_iSubscribersListDispatcher) = default;
    ISubscribersListDispatcher & operator = (const ISubscribersListDispatcher & a_iSubscribersListDispatcher) = default;

};


} // namespace smarthome


#endif // I_SUBSCRIBES_LIST_Dispatcher_H