#include "EnrichedException.hpp"

namespace advcpp
{

const char* EnrichedException::what() const NOEXCEPTION
{
	std::string str;
	
	str.append(logic_error::what());
	str.append(" : ");
	str.append(m_info.GetInfo());
	
	return str.c_str();	
}

} // namespace advcpp
