#ifndef I_SCHEDULER_SUBSCRIPTION_H
#define I_SCHEDULER_SUBSCRIPTION_H

#include <memory> // std::shared_ptr
#include "i_scheduler_task.hpp"

namespace smarthome
{

typedef std::shared_ptr<ISchedulerTask> SPISchedulerTask;   
    
class ISchedulerSubscription
{
public:
    virtual ~ISchedulerSubscription() = default;

    virtual void Subscribe(SPISchedulerTask a_iSchedulerTask) = 0;

protected:
    ISchedulerSubscription() = default;
    ISchedulerSubscription(const ISchedulerSubscription& a_rhs) = default;
    ISchedulerSubscription& operator = (const ISchedulerSubscription& a_rhs) = default;

};

} // namespace smarthome

#endif // I_SCHEDULER_SUBSCRIPTION_H
