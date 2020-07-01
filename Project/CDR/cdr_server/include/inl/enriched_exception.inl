
namespace advcpp
{

inline EnrichedException::EnrichedException(const ExtendedExceptionInfo & a_info, const char * msg) NOEXCEPT
: std::logic_error(msg)
, m_info(a_info)
{
}

inline EnrichedException::~EnrichedException() NOEXCEPT
{
}

inline const ExtendedExceptionInfo& EnrichedException::Info() const NOEXCEPT
{
	return m_info;
}

inline const char* EnrichedException::what() const NOEXCEPT
{
	std::string stringWhat(this->what());
	
	stringWhat.append(" ");
	
	stringWhat.append(m_info.Info());
	
	return stringWhat.c_str();
}

} // namespace advcpp
