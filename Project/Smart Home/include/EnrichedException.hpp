#ifndef ENRICHED_EXCEPTION_H
#define ENRICHED_EXCEPTION_H

#include <exception> // logic error
#include "Info.hpp"
#include "Common.hpp"

namespace advcpp
{

class EnrichedException : public std::logic_error
{
public:
	EnrichedException(const Info & a_info, const char * msg) NOEXCEPTION;
	virtual ~EnrichedException() NOEXCEPTION;
	virtual const char* what() const NOEXCEPTION;
	
private:
	const Info & m_info;
};

inline EnrichedException::EnrichedException(const Info & a_info, const char * msg) NOEXCEPTION
: std::logic_error(msg)
, m_info(a_info)
{
}

inline EnrichedException::~EnrichedException() NOEXCEPTION
{
}

} // namespace advcpp

#endif // ENRICHED_EXCEPTION_H
