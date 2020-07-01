#ifndef INFO_H
#define INFO_H
#include "InterfaceInfo.hpp"
#include "utils.hpp"
#include "Common.hpp"

namespace advcpp
{

class Info : public IInfo
{
public:
	Info( const char * a_file, 
		  const char * a_func, 
		  size_t a_line ) NOEXCEPTION;
	
	~Info() NOEXCEPTION;
	
	std::string GetInfo() const NOEXCEPTION;
	
private:
	const char * m_file;
	const char * m_func;
	size_t m_line;
};

inline Info::Info( const char * a_file, 
				   const char * a_func, 
				   size_t a_line ) NOEXCEPTION
: m_file(a_file)
, m_func(a_func)
, m_line(a_line)
{
}

inline Info::~Info() NOEXCEPTION
{
}

inline std::string Info::GetInfo() const NOEXCEPTION
{
	std::string str;
	
	str.append(" func: ");
	str.append(m_func);
	str.append(" line: ");
	str.append(NumberToString ( m_line ));
	str.append(" file: ");
	str.append(m_file);
	
	return str;
}


} // namespace advcpp


#endif // INFO_H
