#include "thread_utils.hpp"


namespace advcpp
{
inline CondVarException::CondVarException(int a_errorNum, 
	                                      const ExtendedExceptionInfo& a_info)        
	                                      NOEXCEPT
: EnrichedException(a_info, NumToStr(a_errorNum).c_str())	                                   
{
}

inline CondVarException::~CondVarException() NOEXCEPT
{
}

inline const char* CondVarException::what() const NOEXCEPT
{	
	return this->what();
}           

inline ConditionalVariable::~ConditionalVariable() NOEXCEPT
{
    pthread_cond_destroy(&m_cond);
}

inline void ConditionalVariable::Notify() NOEXCEPT
{
    pthread_cond_signal(&m_cond);
}

inline void ConditionalVariable::NotifyAll() NOEXCEPT
{
    pthread_cond_broadcast(&m_cond);
}

template <typename Pred>
void ConditionalVariable::Wait(Mutex& a_mutex, Pred a_pred) THROW1(CondVarException)
{
	while(a_pred())
	{
    	int errnoTmp = pthread_cond_wait(&m_cond, a_mutex.mtx());
    	if(errnoTmp)
    	{
        	throw "something";//CondVarException(errnoTmp, XINFO);
    	}
    }	    
}
} // namespace advcpp
