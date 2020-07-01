#ifndef CONDITIONAL_VARIABLE_H
#define CONDITIONAL_VARIABLE_H

#include <pthread.h> // pthread_cond
#include "enriched_exception.hpp"
#include "commons.hpp"
#include "mutex.hpp"

namespace advcpp
{
class CondVarException : public EnrichedException
{
public: 
	CondVarException(int a_errorNum, 
	               const ExtendedExceptionInfo& a_info)        
	               NOEXCEPT;
	               
	virtual ~CondVarException() NOEXCEPT;
	
	virtual const char* what() const NOEXCEPT;
};

class ConditionalVariable : private UnCopyable
{
public:
        ConditionalVariable() THROW1(CondVarException);

        ~ConditionalVariable() NOEXCEPT;
		
		template <typename Pred>
        void Wait(Mutex& a_mutex, Pred a_pred) THROW1(CondVarException);

        void Notify() NOEXCEPT;

        void NotifyAll() NOEXCEPT;

private:
    pthread_cond_t m_cond;

};
} // namespace advcpp

#include "conditional_variable.inl"

#endif // CONDITIONAL_VARIABLE_H
