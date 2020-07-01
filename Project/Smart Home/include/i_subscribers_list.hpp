#ifndef I_SUBSCRIBERS_LIST_H
#define I_SUBSCRIBERS_LIST_H

#include "i_subscribers_list_dispatcher.hpp"
#include "i_subscribers_list_updator.hpp"

namespace smarthome
{

class ISubscribersList : public ISubscribersListDispatcher, public ISubscribersListUpdator
{
public:
    virtual ~ISubscribersList() = default;

    virtual void Add(SharedPointer<ISubscriber> a_iSubscriber) = 0;
    virtual void Remove(SharedPointer<ISubscriber> a_iSubscriber) = 0;

    virtual void Dispatch(SharedPointer<IEvent> a_ievent) = 0;

    virtual size_t Size() const = 0;
protected:
    ISubscribersList() = default;
    ISubscribersList(const ISubscribersList & a_iSubscribersList) = default;
    ISubscribersList & operator = (const ISubscribersList & a_iSubscribersList) = default;

};


} // namespace smarthome

#endif // I_SUBSCRIBERS_LIST_H