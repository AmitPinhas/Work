#ifndef TASK_H
#define TASK_H

#include "i_task.hpp"
#include <iostream>
#include <unistd.h>

namespace advcpp
{

class TestTask : public ITask
{
public:
    TestTask(const char * a_line );
    virtual void Run();

private:
    const char * m_line;
};

class EndTask : public ITask
{
public:
    virtual void Run();

private:
    const char * m_line;
};

inline void EndTask::Run()
{

    std::cout << "bye bye \n";
}


inline TestTask::TestTask(const char * a_line )
: m_line(a_line)
{
}

inline void TestTask ::Run()
{
    size_t i = 3;
    while(i -- > 0)
    {
        std::cout << m_line << '\n';
    }
}

} // namespace advcpp

#endif // TASK_H