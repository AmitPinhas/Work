#include "exception_stack.hpp"

namespace advcpp
{

ExceptionOverFlow::ExceptionOverFlow(std::string a_string)
: std::logic_error(a_string)
{
}

ExceptionUnderFlow::ExceptionUnderFlow(std::string a_string)
: std::logic_error(a_string)
{
}

} // namespace advcpp
