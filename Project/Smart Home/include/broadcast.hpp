#ifndef BROADCAST_H
#define BROADCAST_H

#include <map> 
#include <vector>
#include "i_broadcast.hpp" 
#include "shared_pointer.hpp" 
#include "thread_pool.hpp" 
#include "i_controller.hpp"
#include "i_subscribes_finder.hpp"
#include "subscribers_storage.hpp"

using namespace advcpp;

namespace smarthome
{

class Broadcast : public IBroadcast
{
public:
    Broadcast(SubscribersStorage & a_subscribers);

    //TODO: rename to broadcast
    virtual void Dispatch(SharedPointer<IEvent> a_event);
    virtual void ShutDown();
    
private:
    SubscribersStorage & m_subscribers;
    ThreadPool m_threadpool;
};

} // namespace smart_home

#endif // BROADCAST_H