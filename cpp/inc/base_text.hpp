#ifndef BASE_TEXT_HPP
#define BASE_TEXT_HPP

#include <iostream>     // std::istream, std::cout
#include <string>

#include "base_manipulator.hpp"

namespace cpp
{
template <typename Out = int> 
class BaseText 
{
public:
	explicit BaseText(std::istream& a_text);
	
	// BaseText(const BaseText & a_other) = default
	// BaseText& operator=(const BaseText & a_other) = default
	// ~BaseText() = default
	
	Out UpperCase();
	Out LowerCase();
	
	const std::string& String() const;
	
	void Text(std::istream& a_text);
		
private:
	std::string& String();
	std::string ConvertToStr(std::istream& a_text);

private:
	std::string m_string;
	BaseManipulator	m_basicManipulator;
};

template <typename Out>
BaseText<Out>::BaseText(std::istream& a_text)
: m_string(ConvertToStr(a_text))
, m_basicManipulator()
{
}

template <typename Out>
const std::string& BaseText<Out>::String() const
{
	return m_string;
}

template <typename Out>
std::string& BaseText<Out>::String()
{
	return m_string;
}

template <typename Out>
void BaseText<Out>::Text(std::istream& a_text)
{
	String() = ConvertToStr(a_text);
}

template <typename Out>
std::string BaseText<Out>::ConvertToStr(std::istream& a_text)
{
//	std::string str{ std::istreambuf_iterator<char>(a_text),
//				     std::istreambuf_iterator<char>() };

	std::string str;
//	std::istream tmp = a_text;

//	while(std::getline(a_text,str))  

	while(a_text >> str);

	return str;
}

template <typename Out>
Out BaseText<Out>::UpperCase()
{		
	m_basicManipulator.UpperCase(String());

	//std::ostringstream outputText;
	
	std::cout << String();
	
	//return outputText;
	
	return 0;
}


template <typename Out>
Out BaseText<Out>::LowerCase()
{
	m_basicManipulator.LowerCase(String());
	
	//std::ostringstream outputText;
	
	std::cout << String() ;
	
	//return outputText;
	return 0;
}

}

#endif // BASE_TEXT_HPP
