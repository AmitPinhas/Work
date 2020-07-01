#ifndef ENRICHED_EXCEPTION_H
#define ENRICHED_EXCEPTION_H

#include <exception> // logic error
#include  <stdexcept>
	
#include "extended_exception_info.hpp"
#include "commons.hpp"


namespace advcpp
{

class EnrichedException : public std::logic_error
{
public:
	EnrichedException(const ExtendedExceptionInfo & a_info, const char * a_msg) NOEXCEPT;
	
	virtual ~EnrichedException() NOEXCEPT;
	
	const ExtendedExceptionInfo& Info() const NOEXCEPT;
	
	virtual const char* what() const NOEXCEPT;
	
private:
	const ExtendedExceptionInfo& m_info;
	
};

} // namespace advcpp

#include "inl/enriched_exception.inl"

#endif // ENRICHED_EXCEPTION_H
