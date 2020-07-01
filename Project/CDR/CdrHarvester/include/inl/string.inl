#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cwchar>

namespace advcpp
{


template <typename C>
bool operator<(String<C> const& a_lhs, String<C> const& a_rhs)
{
	return ( Helper<C>::Compare (&a_lhs[0], &a_rhs[0]) > 0 );
}

template <typename C>
bool operator>(String<C> const& a_lhs, String<C> const& a_rhs)
{
	return ( Helper<C>::Compare (a_lhs.Begin(), a_rhs.Begin()) < 0 );
}

template <typename C>
bool operator<=(String<C> const& a_lhs, String<C> const& a_rhs)
{
	return ! (a_lhs > a_rhs);
}

template <typename C>
bool operator>=(String<C> const& a_lhs, String<C> const& a_rhs)
{
	return ! (a_lhs > a_rhs);
}


template <typename C>
bool operator<(String<C> const& a_lhs, const C* a_char)
{
	return ( Helper<C>::Compare (&a_lhs[0], a_char) > 0 );
}

template <typename C>
bool operator>(String<C> const& a_lhs, const C* a_char)
{
	return ( Helper<C>::Compare (&a_lhs[0], a_char) < 0 );
}

template <typename C>
bool operator<=(String<C> const& a_lhs, const C* a_char)
{
	return ! (a_lhs > a_char);
}

template <typename C>
bool operator>=(String<C> const& a_lhs, const C* a_char)
{
	return ! (a_lhs < a_char);
}


template <typename C>
bool operator<(const C* a_char, String<C> const& a_rhs)
{
	return ( Helper<C>::Compare (a_char, a_rhs[0]) > 0 );
}

template <typename C>
bool operator>(const C* a_char, String<C> const& a_rhs)
{
	return ( Helper<C>::Compare (a_char, a_rhs[0]) < 0 );
}

template <typename C>
bool operator<=(const C* a_char, String<C> const& a_rhs)
{
	return ! (a_char > a_rhs);
}

template <typename C>
bool operator>=(const C* a_char, String<C> const& a_rhs)
{
	return ! (a_char < a_rhs);
}


template <typename C>
bool operator==(String<C> const& a_lhs, String<C> const& a_rhs)
{
	return a_rhs.IsEqual(a_lhs);
}


template <typename C>
bool operator!=(String<C> const& a_lhs, String<C> const& a_rhs)
{
	return !(a_rhs == a_lhs);
}


template <typename C>
bool String<C>::IsEqual(String<C> const& a_lhs) const
{
	return (Helper<C>::Compare(&a_lhs[0], &m_buffer[0]) == 0);
}


template <typename C>
bool String<C>::IsEqual(const C* a_char) const
{
	return (Helper<C>::Compare(a_char, &m_buffer[0]) == 0);
}

template <typename C>
bool operator==(String<C> const& a_lhs, const C* a_char)
{
	return a_lhs.IsEqual(a_char);
}


template <typename C>
bool operator!=(String<C> const& a_lhs, const C* a_char)
{
	return !(a_lhs == a_char);
}

template <typename C>
bool operator==( const C* a_char, String<C> const& a_rhs)
{
	return a_rhs.IsEqual(a_char);
}


template <typename C>
bool operator!=( const C* a_char, String<C> const& a_rhs)
{
	return !(a_rhs == a_char);
}

template <typename C>
String<C> operator+(String<C> const& a_lhs, String<C> const& a_rhs)
{
	String<C> temp(a_rhs);
	temp += a_lhs;
	return temp;
}

template <typename C>
String<C> operator+(String<C> const& a_rhs, const C* a_char)
{
	String<C> temp(a_rhs);
	temp += a_char;
	return temp;
}

template <typename C>
String<C> operator+(const C* a_char, String<C> const& a_rhs)
{
	return a_rhs + a_char;
}


template <typename C>
bool String<C>::IsInRange(size_t a_index) const
{
	return (a_index < m_size);
}


template <typename C>
String<C>::String(C const* a_charP)
: m_buffer()
{

	if(a_charP != 0)
	{
		size_t strLen = Helper<C>::Len(a_charP);
	
		m_buffer.insert(m_buffer.begin(), a_charP, a_charP + strLen  + 1);
	}
	else
	{
		m_buffer.push_back(C(0));
	}
}


template <typename C>
C const& String<C>::operator[](size_t a_index) const
{
	return m_buffer.at(a_index);
}


template <typename C>
C& String<C>::operator[](size_t a_index)
{
	return const_cast<C&>(static_cast<const String&>(*this)[a_index]);
}


template <typename C>
String<C> const& String<C>::operator+=(String const& a_lhs)
{
	m_buffer.insert(m_buffer.end() - 1, a_lhs.m_buffer.begin(), a_lhs.m_buffer.end() - 1);

	return *this;
}


template <typename C>
String<C> const& String<C>::operator+=(C const* a_char)
{
	assert(a_char != 0);

	m_buffer.pop_back();
	size_t strLen = Helper<C>::Len(a_char);

	m_buffer.insert(m_buffer.end(), a_char, a_char + strLen + 1);
	m_size = strLen;
	return *this;
}

template <typename C>
size_t String<C>::Size() const
{
	return m_buffer.size() - 1;
}

template <typename C>
typename String<C>::iterator String<C>::Begin()
{
	return m_buffer.begin();
}


template <typename C>
typename String<C>::iterator String<C>::End()
{
	return m_buffer.end();
}


template <typename C>
typename String<C>::const_iterator String<C>::Begin() const
{
	return m_buffer.begin();
}


template <typename C>
typename String<C>::const_iterator String<C>::End() const
{
	return m_buffer.end();
}


template <typename C>
typename String<C>::reverse_iterator String<C>::RBegin()
{
	return m_buffer.rbegin();
}

template <typename C>
typename String<C>::reverse_iterator String<C>::REnd()
{
	return m_buffer.rend();
}

template <typename C>
typename String<C>::const_reverse_iterator String<C>::RBegin() const
{
	return m_buffer.rbegin();
}

template <typename C>
typename String<C>::const_reverse_iterator String<C>::REnd() const
{
	return m_buffer.rend();
}

template <typename C>
String<C> const& String<C>::operator*=(size_t a_multyplyer)
{

	String<C> temp = *this;
	MultiPlyer(a_multyplyer, temp);
	return *this;
}

template <typename C>
void String<C>::MultiPlyer(size_t a_multyply, String<C> const& a_string)
{
	if (a_multyply < 2)
	{
		return;
	}
	*this += a_string;
	MultiPlyer(a_multyply - 1, a_string);
}



template <typename C>
std::ostream& operator<<(std::ostream& a_stream, String<C>& a_str)
{
	return a_stream.write(&a_str[0], a_str.Size());
}



template <typename C>
void operator>>(std::istream const& a_stream, String<C>& a_str)
{
	char temp[String<C>::MaxLineLen];
	a_stream.getline(temp, String<C>::MaxLineLen);
	a_str = temp;
}


template <typename C>
typename String<C>::const_iterator 
String<C>::Find(String<C> const& a_str) const
{
	 return std::search(Begin(), End(), a_str.Begin(), a_str.End());
}


template <typename C>
C const* String<C>::Data() const
{
	return &m_buffer[0];
}


template <typename C>
void String<C>::Swap(String& a_lhs)
{
	m_buffer.swap(a_lhs.m_buffer);
}


template <typename C>
void String<C>::ToUpper()
{
	for_each(Begin(), End(), Helper<C>::ToUpper);
}


template <typename C>
void String<C>::ToLower()
{
	for_each(Begin(), End(), Helper<C>::ToLower);
}


/////////////////////////////////////////////////////////
size_t Helper<char>::Compare(const char* a_lhs, const char* a_rhs)
{
	return strcmp(a_lhs, a_rhs);
}
size_t Helper<char>::Len(const char* a_str)
{
	return strlen(a_str);

}

void Helper<char>::ToUpper(char& a_char)
{
	if ( islower(a_char) )
	{
		a_char = toupper(a_char); 
	}
}

void Helper<char>::ToLower(char& a_char)
{
	if ( isupper(a_char) )
	{
		a_char = tolower(a_char); 
	}
}


size_t Helper<wchar_t>::Compare(const wchar_t* a_lhs, const wchar_t* a_rhs)
{
	return wcscmp(a_lhs, a_rhs);
}

size_t Helper<wchar_t>::Len(const wchar_t* a_str)
{
	return wcslen(a_str);
}

void Helper<wchar_t>::ToUpper(wchar_t& a_char)
{
	if ( iswlower(a_char) )
	{
		a_char = towupper(a_char); 
	}
}

void Helper<wchar_t>::ToLower(wchar_t& a_char)
{
	if ( iswupper(a_char) )
	{
		a_char = towlower(a_char); 
	}
}

}// cpp namespace
