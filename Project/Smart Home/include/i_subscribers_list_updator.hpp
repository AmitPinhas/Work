#ifndef I_SUBSCRIBES_LIST_UPDATOR_H
#define I_SUBSCRIBES_LIST_UPDATOR_H

#include "shared_pointer.hpp"
#include "i_subscriber.hpp"

using namespace advcpp;

namespace smarthome
{

class ISubscribersListUpdator
{
public:
    virtual ~ISubscribersListUpdator() = default;
    virtual void Add(SharedPointer<ISubscriber> a_iSubscriber) = 0;
    virtual void Remove(SharedPointer<ISubscriber> a_iSubscriber) = 0;

protected:
    ISubscribersListUpdator() = default;
    ISubscribersListUpdator(const ISubscribersListUpdator & a_iSubscribersListUpdator) = default;
    ISubscribersListUpdator & operator = (const ISubscribersListUpdator & a_iSubscribersListUpdator) = default;

};


} // namespace smarthome


#endif // I_SUBSCRIBES_LIST_UPDATOR_H