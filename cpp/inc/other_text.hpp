#ifndef OTHER_TEXT_HPP
#define OTHER_TEXT_HPP

#include <string>

#include "base_manipulator.hpp"

namespace cpp
{
template <typename T, typename InConvert = void, typename OutConvert = void, typename Out = void> // default if InConvert || OutConvert || Out is null 
class OtherText 
{
public:
	explicit OtherText(T const& a_text, InConvert const& a_inConvert = 0, OutConvert const& a_outConvert = 0);
	
	OtherText(T const& a_text, OutConvert const& a_outConvert); // not explicit, num arguments > 1
	
	// OtherText(const OtherText & a_other) = default
	// OtherText& operator=(const OtherText & a_other) = default
	// ~OtherText() = default
	
	Out UpperCase();
	Out LowerCase();
	
	InConvert ConvertIn() const; // not reference, can be 0
	OutConvert ConvertOut() const; // not reference, can be 0
	const std::string& String() const;
	
	void ConvertIn(InConvert const& a_inConvert);
	void ConvertOut(OutConvert const& a_outConvert);
	void Text(T const& a_text);

private:
	std::string InitString(T const& a_text, InConvert const& a_inConvert);
	InConvert& ConvertIn();
	OutConvert& ConvertOut();
	std::string& String();
	
private:
	InConvert m_inConvert;
	OutConvert m_outConvert;
	std::string& m_string;
	BaseManipulator m_basicManipulator;
};


template <typename T, typename InConvert, typename OutConvert, typename Out>
OtherText<T, InConvert, OutConvert, Out>::OtherText(T const& a_text, InConvert const& a_inConvert, OutConvert const& a_outConvert)
: m_inConvert(a_inConvert)
, m_outConvert(a_outConvert)
, m_string(InitString(a_text, a_inConvert))
, m_basicManipulator()
{
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
OtherText<T, InConvert, OutConvert, Out>::OtherText(T const& a_text, OutConvert const& a_outConvert)
: m_inConvert(0)
, m_outConvert(a_outConvert)
, m_string(a_text)
{
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
typename OtherText<T, InConvert, OutConvert, Out>::std::string InitString(T const& a_text, InConvert const& a_inConvert)
{
	if (a_inConvert != 0)
	{
		return m_inConvert(a_text);
	}
	
	return a_text;
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
Out OtherText<T, InConvert, OutConvert, Out>::UpperCase()
{
	m_basicManipulator.UpperCase(String());
	if (m_outConvert)
	{
		return ConvertOut()(String());
	}
	return 0;
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
Out OtherText<T, InConvert, OutConvert, Out>::LowerCase()
{
	m_basicManipulator.LowerCase(String());
	{
		return ConvertOut()(String());		
	}
	return 0;
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
InConvert OtherText<T, InConvert, OutConvert, Out>::ConvertIn() const
{
	return m_inConvert;
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
OutConvert OtherText<T, InConvert, OutConvert, Out>::ConvertOut() const
{
	return m_outConvert;
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
const std::string& OtherText<T, InConvert, OutConvert, Out>::String() const
{
	return m_string;
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
void OtherText<T, InConvert, OutConvert, Out>::ConvertIn(InConvert const& a_inConvert)
{
	ConvertIn() = a_inConvert;
}


template <typename T, typename InConvert, typename OutConvert, typename Out>
void OtherText<T, InConvert, OutConvert, Out>::ConvertOut(OutConvert const& a_outConvert)
{
	ConvertOut() = a_outConvert;
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
void OtherText<T, InConvert, OutConvert, Out>::Text(T const& a_text)
{
	InitString(a_text, ConvertIn());
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
InConvert& OtherText<T, InConvert, OutConvert, Out>::ConvertIn()
{
	return m_inConvert;	
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
OutConvert& OtherText<T, InConvert, OutConvert, Out>::ConvertOut()
{
	return m_outConvert;	
}

template <typename T, typename InConvert, typename OutConvert, typename Out>
std::string& OtherText<T, InConvert, OutConvert, Out>::String()
{
	return m_string;	
}


}

#endif // OTHER_TEXT_HPP
