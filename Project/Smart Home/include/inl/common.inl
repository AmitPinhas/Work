#ifndef COMMON_INL
#define COMMON_INL
namespace advcpp{

inline ExtendInfo::ExtendInfo(const char* a_file, const char* a_func, int a_line)
: m_file(a_file)
, m_func(a_func)
, m_line (a_line)
{
}

inline std::string const& ExtendInfo::File() const
{
    return m_file;
}

inline std::string const& ExtendInfo::Func() const
{
    return m_func;
}

inline int ExtendInfo::Line() const
{
    return m_line;
}

///////////////////////////////////////////////////

inline ExtendedException::ExtendedException(const char* a_msg, ExtendInfo const& a_xInfo)
: runtime_error(a_msg)
, m_xInfo(a_xInfo)
{
}

inline ExtendedException::~ExtendedException() NOEXCEPT
{    
}

inline ExtendInfo const& ExtendedException::XInfo()
{
    return m_xInfo;
}

///////////////////////////////////////////////////


}//namespace advcpp
#endif //COMMON_INL
