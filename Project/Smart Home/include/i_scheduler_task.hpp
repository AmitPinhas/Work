#ifndef I_SCHEDULER_TASK_H
#define I_SCHEDULER_TASK_H

#include <ctime> // time_t

namespace smarthome
{
    
class ISchedulerTask
{
public:
    ~ISchedulerTask() = default;

    virtual bool Execute() = 0;

    virtual time_t GetRunTime() const = 0;

    virtual void SetRunTime(time_t a_newRunTime) = 0;

    virtual time_t GetFrequncy() const = 0;

protected:
    ISchedulerTask() = default;
    ISchedulerTask(const ISchedulerTask& a_rhs) = default;
    ISchedulerTask& operator = (const ISchedulerTask& a_rhs) = default;

};

} // namespace smarthome



#endif // I_SCHEDULER_TASK_H
