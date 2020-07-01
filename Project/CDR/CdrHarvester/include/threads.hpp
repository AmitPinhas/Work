#ifndef THREADS_HPP
#define THREADS_HPP

#include <cassert>// assert
#include <pthread.h>
#include <errno.h>

#include "mutex.hpp"
#include "common.hpp" 
#include "exeption.hpp"

namespace advcpp
{

class IRunAble : private  UnCopyAble 
{
public:
    virtual ~IRunAble();
    virtual void Run() = 0;
};

class ThreadExeption : public MyExeption
{
public:
	ThreadExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION;
};

class Thread : private UnCopyAble 
{
public:
    explicit Thread(IRunAble* a_prun) THROW1(ThreadExeption);
    ~Thread();

    void Join() THROW1(ThreadExeption);
    void Detach() NO_EXEPTION;    
    void TryJoin(Nano a_time) THROW1(ThreadExeption);
    void Cancel() NO_EXEPTION;
    void Kill(size_t a_sig) THROW1(ThreadExeption);

    static void Yield() THROW1(ThreadExeption);
    static void Exit(void* a_return) NO_EXEPTION;

private:
    static void* thunk(void* a_runAble);

private:
    pthread_t m_thread;
};

}// advcpp namespace 

#include "inl/threads.inl"
#endif //THREADS_HPP