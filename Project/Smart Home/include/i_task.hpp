#ifndef I_TASK_H
#define I_TASK_H

namespace advcpp
{

class ITask
{
public:
    virtual ~ITask() = 0;
    virtual void Run() = 0;

protected:
    ITask();
    ITask(const ITask & task);
    ITask & operator = (const ITask & task);
};

inline ITask::~ITask()
{
}

inline ITask::ITask()
{
}

inline ITask::ITask(const ITask & task)
{
    (void)task;
}

inline ITask & ITask::operator = (const ITask & task)
{
    (void)task;
    return *this;
}

} // namespace advcpp
 

#endif // I_TASK_H