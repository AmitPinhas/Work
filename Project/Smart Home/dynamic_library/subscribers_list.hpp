#ifndef SUBSCRIBERS_LIST_H
#define SUBSCRIBERS_LIST_H

#include <vector>
#include "i_subscribers_list.hpp"

using namespace advcpp;
using namespace std;

namespace smarthome
{

class SubscribersList : public ISubscribersList
{
public:
    SubscribersList() = default;
    ~SubscribersList() = default;
    SubscribersList(const SubscribersList & a_container) = default;
    SubscribersList & operator = (const SubscribersList & a_container) = default;

    virtual void Dispatch(SharedPointer<IEvent> a_ievent);

    virtual void Add(SharedPointer<ISubscriber> a_iSubscriber);
    virtual void Remove(SharedPointer<ISubscriber> a_iSubscriber);
    
    virtual size_t Size() const;

private:
    vector<SharedPointer<ISubscriber> > m_subscribers;
};

} // namespace smarthome

#endif // SUBSCRIBERS_LIST_H