#ifndef I_PRIORITY_TASK_CONTAINER_H
#define I_PRIORITY_TASK_CONTAINER_H

#include <memory> // std::shared_ptr
#include "i_scheduler_task.hpp"

namespace smarthome
{

typedef std::shared_ptr<ISchedulerTask> SPISchedulerTask;  

class IPriorityTaskContainer
{
public:
    virtual ~IPriorityTaskContainer() = default;

    virtual SPISchedulerTask Pop() = 0;

    virtual void Push(SPISchedulerTask a_iSchedulerTask) = 0;

protected:
    IPriorityTaskContainer() = default;
    IPriorityTaskContainer(const IPriorityTaskContainer& a_rhs) = default;
    IPriorityTaskContainer& operator = (const IPriorityTaskContainer& a_rhs) = default;
};

} // namespace smarthome


#endif // I_PRIORITY_TASK_CONTAINER_H