#ifndef EXTENDED_EXCEPTION_INFO_H
#define EXTENDED_EXCEPTION_INFO_H

#include <string>
#include "commons.hpp"

namespace advcpp
{

class ExtendedExceptionInfo
{
public:
	ExtendedExceptionInfo(const char* a_file, 
	                      const char* a_func,
	                      size_t a_line) NOEXCEPT;
	
	std::string Info() const NOEXCEPT;
	                      
	const std::string& File() const NOEXCEPT;
	const std::string& Func() const NOEXCEPT;
	size_t Line() const NOEXCEPT;
	                           

private:
	std::string m_file;
	std::string m_func;
	size_t m_line;
};

} // namespace advcpp 

#include "inl/extended_exception_info.inl"

#endif // EXTENDED_EXCEPTION_INFO_H
