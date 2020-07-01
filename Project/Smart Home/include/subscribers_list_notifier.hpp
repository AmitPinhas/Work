
#ifndef SUBSCRIBERS_LIST_NOTIFIER_H
#define SUBSCRIBERS_LIST_NOTIFIER_H

#include "i_subscribers_list_notifier.hpp" 
#include "thread_pool.hpp" 
#include "i_subscribes_finder.hpp"

using namespace advcpp;

namespace smarthome
{

static size_t LIST_ON_AIR = 1000;

class SubscribersListNotifier : public ISubscribersListNotifier
{
public:
    explicit SubscribersListNotifier(ISubscribersFinder & a_finder, size_t NumOfTasks = LIST_ON_AIR);
    ~SubscribersListNotifier() = default;
    SubscribersListNotifier(const SubscribersListNotifier & a_subscribersListNotifier) = delete;
    SubscribersListNotifier & operator = (const SubscribersListNotifier & a_subscribersListNotifier) = delete;

    virtual void Notifi(SharedPointer<IEvent> a_event);
    virtual void ShutDown();
    
private:
    ISubscribersFinder & m_finder;
    ThreadPool m_threadpool;
};


} // namespace smarthome

#endif // SUBSCRIBERS_LIST_NOTIFIER_H