#include <cassert>

#include "common.hpp" // uncopyable
#include "mutex.hpp" // Mutex
#include "exeption.hpp"// exeptions


namespace advcpp
{


inline CondVarExeption::CondVarExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION
: MyExeption(a_msg, a_info)
{
}

inline CondVar::~CondVar() NO_EXEPTION
{
    if(pthread_cond_destroy(&m_condition) == EBUSY)
    {
        assert(false);
    }
}

inline void CondVar::Nutify() NO_EXEPTION
{
    pthread_cond_signal( &m_condition); 
}

inline void CondVar::NutifyAll() NO_EXEPTION
{
    pthread_cond_broadcast(&m_condition);
}


template<typename Pred>
inline void CondVar::Wait(Mutex& a_mutex, Pred a_predict) THROW1(CondVarExeption)
{
    while ( a_predict() )
    {
        if (pthread_cond_wait(&m_condition, a_mutex.GetMutexP()))
        {
            XTHROW(CondVarExeption, "weit error");
        }
    }
    
}


}//namespace advcpp