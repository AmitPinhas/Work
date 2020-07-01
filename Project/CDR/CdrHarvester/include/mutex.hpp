#ifndef MUTEX_HPP
#define MUTEX_HPP
#include <pthread.h>
#include <cstdio>

#include "exeption.hpp"
#include "common.hpp"

namespace advcpp
{

class CondVar;

class MutexExeption : public MyExeption
{
public:
	MutexExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION;
};

class Mutex : private UnCopyAble
{
public:
    friend class CondVar;

public:
    Mutex() THROW1(MutexExeption);
    ~Mutex() NO_EXEPTION;

    void Lock() THROW1(MutexExeption);
    void UnLock() THROW1(MutexExeption);
    void TryLock(Nano a_time) NO_EXEPTION;
private:
    pthread_mutex_t* GetMutexP() NO_EXEPTION;

private:
    pthread_mutex_t m_mutex;
};

class Guard : private UnCopyAble
{
public:
    Guard(Mutex& a_lock);
    ~Guard();

private:
    Mutex& m_lock;
};



}// cpp namespace
#include "inl/mutex.inl"
#include "conditional_variable.hpp"
#endif //MUTEX_HPP