#include "mu_test.h"

#include <iostream>
#include <tr1/memory> // std::tr1::shared_ptr
#include "thread_pool.hpp"
#include "i_task.hpp"
#include "atomic_value.hpp"
#include "tasks.hpp"
#include "thread.hpp"
#include "atomic_value.hpp"

using namespace advcpp;

class Task : public ITask
{
public:
    Task(size_t a_numLoop, AtomicValue<int>& a_var);
    void Execute();

private: 
    AtomicValue<int>& m_var;
    size_t m_numLoop;

};

Task::Task(size_t a_numLoop, AtomicValue<int>& a_var)
: m_var(a_var)
, m_numLoop(a_numLoop)
{
}

void Task::Execute()
{
    for(size_t i = 0 ; i < m_numLoop; ++i)
    {
        ++m_var;
    }
}

UNIT(first_test)

    const size_t sizeQ = 10000;

    const size_t numThreads = 2;

    advcpp::ThreadPool threadPool(sizeQ, numThreads);
    AtomicValue<int> var;
    const size_t numTasks = 2;
    size_t i = numTasks;
    const size_t loops = 2;
    const size_t addWorkers = 2;
    const size_t removeWorkers = 2;
    std::tr1::shared_ptr<advcpp::ITask> task(new Task(loops, var));

    while(i-- > 0)
    {   
        threadPool.Submit(task);
    }

    threadPool.AddWorkers(addWorkers);

    i = numTasks;

    while(i-- > 0)
    {   
        threadPool.Submit(task);
    }    

    threadPool.RemoveWorkers(removeWorkers);

    i = numTasks;

    while(i-- > 0)
    {   
        threadPool.Submit(task);
    }     

    threadPool.Shutdown();

    ASSERT_EQUAL(var.Get(), (numTasks * loops * 3));

END_UNIT

TEST_SUITE(test the thread pool on fire)
    TEST(first_test)

END_SUITE