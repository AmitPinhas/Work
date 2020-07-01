#include "exceptions_definitions.hpp"

namespace advcpp
{

std::string XtendedInformation::CreateStringFromLine(int a_line) throw(std::ios_base::failure)
{
    std::ostringstream sstr;
	sstr<<a_line;
	return sstr.str();
}

std::string XtendedInformation::Location() const throw(std::ios_base::failure)
{
    std::ostringstream sstr;
	sstr<<FileName()<<'|'<<Line()<<'|'<<Function()<<'\n';
	return sstr.str();
}


}//namespace advcpp