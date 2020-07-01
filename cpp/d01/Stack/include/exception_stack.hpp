#ifndef EXCEPTION_STACK_H
#define EXCEPTION_STACK_H

#include <stdexcept>
#include <string>

namespace advcpp
{

class ExceptionOverFlow : public std::logic_error
{
public: 
	explicit ExceptionOverFlow(std::string a_string = "overflow");
};

class ExceptionUnderFlow : public std::logic_error
{
public: 
	explicit ExceptionUnderFlow(std::string a_srting = "underflow");
};

} // namespace advcpp


#endif // EXCEPTION_STACK_H
