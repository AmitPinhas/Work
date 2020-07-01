
namespace advcpp
{

inline ExtendedExceptionInfo::ExtendedExceptionInfo( const char * a_file, 
				                                     const char * a_func,      		                                                 size_t a_line ) NOEXCEPT
: m_file(a_file)
, m_func(a_func)
, m_line(a_line)
{
}

inline const std::string& ExtendedExceptionInfo::File() const NOEXCEPT
{
	return m_file;
}

inline const std::string& ExtendedExceptionInfo::Func() const NOEXCEPT
{
	return m_func;
}

inline size_t ExtendedExceptionInfo::Line() const NOEXCEPT
{
	return m_line;
}

} // namespace advcpp
