#ifndef I_TASK_H
#define I_TASK_H

#include <tr1/memory> // std::tr1::shared_ptr
#include "common.hpp" // NOEXCEPT

namespace advcpp
{

class ITask
{
public:
    virtual ~ITask() NOEXCEPT = 0;

    virtual void Execute() = 0;

protected:
    ITask();
    ITask(const ITask& a_rhs);
    ITask& operator =(const ITask& a_rhs);

};

class ITasksSubmit
{
public:
    typedef std::tr1::shared_ptr<ITask> ITaskPtr;

    virtual ~ITasksSubmit() NOEXCEPT = 0;

    virtual void Submit(ITaskPtr a_task) = 0;

    virtual size_t Size() const = 0;

protected:
    ITasksSubmit();
    ITasksSubmit(const ITasksSubmit& a_rhs);
    ITasksSubmit& operator =(const ITasksSubmit& a_rhs);

};

class ITasksGet
{
public:
    typedef std::tr1::shared_ptr<ITask> ITaskPtr;

    virtual ~ITasksGet() NOEXCEPT = 0;

    virtual void Get(ITaskPtr& a_task) = 0;

    virtual size_t Size() const = 0;

protected:
    ITasksGet();
    ITasksGet(const ITasksGet& a_rhs);
    ITasksGet& operator =(const ITasksGet& a_rhs);

};

} // namespace advcpp

#endif // I_TASK_H