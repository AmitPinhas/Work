#include "exceptions_definitions.hpp"
#include <sstream>

namespace advcpp
{
    
inline EnrichedExeption::EnrichedExeption(const char* a_what_arg, XtendedInformation const& a_info) THROW(std::exception)
: logic_error(a_what_arg)
, m_info(a_info)
{
}

inline EnrichedExeption::EnrichedExeption(const std::string& a_what_arg, 
                                   XtendedInformation const& a_info) THROW(std::exception)
: logic_error(a_what_arg)
, m_info(a_info)
{
}

inline XtendedInformation const& EnrichedExeption::Info() const NOEXCEPT
{
    return m_info;
}

inline EnrichedExeption::~EnrichedExeption() NOEXCEPT
{
}

inline XtendedInformation::XtendedInformation(const char* a_fileName, 
                                              int a_line, 
                                              const char* a_funcName) throw(std::ios_base::failure)
: m_fileName(a_fileName)
, m_funcName(a_funcName)
, m_line(CreateStringFromLine(a_line))
{
}

inline const std::string& XtendedInformation::Line() const NOEXCEPT
{
    return m_line;
}

inline const std::string& XtendedInformation::Function() const NOEXCEPT
{
    return m_funcName;
}

inline const std::string& XtendedInformation::FileName() const NOEXCEPT
{
    return m_fileName;
}



}//namespace advcpp

