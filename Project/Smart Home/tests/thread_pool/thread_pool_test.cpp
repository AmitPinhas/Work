#include "mu_test.h"

#include <iostream>
#include "thread_pool.hpp"
#include "pool_routine.hpp"
#include "task.hpp"
#include "utils.hpp"
#include "fire_controller.hpp"

#include "thread_group.hpp"

using namespace advcpp;
using namespace smart_home;
using namespace std;

AtomicValue<int> atomic(25);

class PlusTask : public ITask
{
public:
    virtual void Run();
};

inline void PlusTask::Run()
{

    ++atomic;
}

class MinusTask : public ITask
{
public:
    virtual void Run();
};

inline void MinusTask::Run()
{

    --atomic;
}



const size_t TASKS = 100000;

UNIT(base_test) 
    SharedPointer<ITask> s(new TestTask("first"));
    SharedPointer<ITask> v(new TestTask("second"));

    ThreadPool tp(100, 10);
    size_t i = TASKS;
    while(i -- > 0)
    {
        tp.DispatchTask(v);
    }

    Second sec(2);
    Sleep(sec);
    tp.ShutDown();
	ASSERT_PASS();
END_UNIT

UNIT(base_add_remove) 
    SharedPointer<ITask> s(new TestTask("first"));
    SharedPointer<ITask> v(new TestTask("second"));

    ThreadPool tp(100, 2);
    size_t i = TASKS;
    while(i -- > 0)
    {
        tp.DispatchTask(v);
    }

    // Second sec(2);
    // Sleep(sec);
    cout << "sleep!------------------------->sleep!";
    i = TASKS;
    tp.AddThreads(10);
    tp.RemoveThreads(2);
    
    tp.ShutDown();
	ASSERT_PASS();
END_UNIT

UNIT(base_test_with_no_delays) 
    SharedPointer<ITask> s(new TestTask("first"));
    SharedPointer<ITask> v(new TestTask("second"));

    ThreadPool tp(10, 2);
    size_t i = TASKS;
    while(i -- > 0)
    {
        tp.DispatchTask(v);
        tp.DispatchTask(s);
    }

    tp.AddThreads(2);
    tp.RemoveThreads(2);
    
    tp.ShutDown();
	ASSERT_PASS();
END_UNIT


UNIT(full_test) 
    SharedPointer<ITask> s(new PlusTask);
    SharedPointer<ITask> v(new MinusTask);

    ThreadPool tp(100, 100);
    size_t i = TASKS;
    
    
    while(i -- > 0)
    {
        tp.DispatchTask(s);
        tp.DispatchTask(v);
    }
    tp.DispatchTask(s);
    
    tp.AddThreads(2);
    i = TASKS;
    while(i -- > 0)
    {
        tp.DispatchTask(s);
        tp.DispatchTask(v);
    }
    tp.RemoveThreads(2);
    i = TASKS;
    while(i -- > 0)
    {
        tp.DispatchTask(s);
        tp.DispatchTask(v);
    }
    tp.ShutDown();

    ASSERT_EQUAL(26, atomic.Value());
END_UNIT

UNIT(sprinklers_test) 

    ThreadPool tp(100, 100);
    size_t i = TASKS;
    
    
    while(i -- > 0)
    {
        Sprinkler sprink;
        sprink.m_id = i;
        sprink.m_state = Sprinkler::OFF;
        SharedPointer<ITask> s(new SprinklerController(sprink));
        tp.DispatchTask(s);
    }
    
    tp.AddThreads(2);
    i = TASKS;
    while(i -- > 0)
    {
        Sprinkler sprink;
        sprink.m_id = i + TASKS;
        sprink.m_state = Sprinkler::OFF;
        SharedPointer<ITask> s(new SprinklerController(sprink));
        tp.DispatchTask(s);
    }
    tp.RemoveThreads(2);
    i = TASKS;
    while(i -- > 0)
    {
        Sprinkler sprink;
        sprink.m_id = i + TASKS + TASKS;
        sprink.m_state = Sprinkler::OFF;
        SharedPointer<ITask> s(new SprinklerController(sprink));
        tp.DispatchTask(s);
    }
    tp.ShutDown();

    ASSERT_PASS();
END_UNIT

TEST_SUITE(thread pool tests)
	// TEST(base_test)
    // TEST(base_add_remove) 
    // TEST(base_test_with_no_delays) 
    // TEST(full_test) 
    TEST(sprinklers_test)
END_SUITE

