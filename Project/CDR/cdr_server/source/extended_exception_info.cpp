#include "extended_exception_info.hpp"
#include "thread_utils.hpp"

namespace advcpp
{

std::string ExtendedExceptionInfo::Info() const NOEXCEPT
{
	std::string str;
	
	str.append(" func: ");
	str.append(m_func);
	str.append(" line: ");
	str.append(NumToStr( m_line ));
	str.append(" file: ");
	str.append(m_file);
	
	return str;
}

} // namespace advcpp
