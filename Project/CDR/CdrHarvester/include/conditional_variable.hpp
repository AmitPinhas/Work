#ifndef CONDITIONAL_VARIABLE_HPP
#define CONDITIONAL_VARIABLE_HPP
#include <cerrno>

#include "common.hpp" // uncopyable
#include "mutex.hpp" // Mutex
#include "exeption.hpp"// exeptions


namespace advcpp
{

class CondVarExeption : public MyExeption
{
public:
	CondVarExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION;
};


class CondVar : private UnCopyAble
{
public:
    CondVar() THROW1(CondVarExeption);
    ~CondVar() NO_EXEPTION;

    void Nutify() NO_EXEPTION;
    void NutifyAll() NO_EXEPTION;
    
    template<typename Pred>
    void Wait(Mutex& a_mutex, Pred a_predict) THROW1(CondVarExeption);

private:
    pthread_cond_t m_condition;
};




///to inl


}//advcpp namespace
#include "inl/conditional_variable.inl"
#endif// CONDITIONAL_VARIABLE_HPP


