#ifndef MUTEX_EXCEPTION_HPP
#define MUTEX_EXCEPTION_HPP

#include "enriched_exception.hpp"

namespace advcpp
{

class MutexException : public EnrichedException
{
public: 
	MutexException(int a_errorNum, 
	               const ExtendedExceptionInfo& a_info)        
	               NOEXCEPT;
	               
	virtual ~MutexException() NOEXCEPT;
	
	virtual const char* what() const NOEXCEPT;
};

} // namespace advcpp

#include "inl/mutex_exception.inl"

#endif // MUTEX_EXCEPTION_HPP
