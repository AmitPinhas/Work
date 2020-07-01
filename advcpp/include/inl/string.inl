#include <algorithm>    // std::search
#include <cassert>
#include "helper.hpp"

namespace advcpp
{

template <typename T>
String<T>::String(const T* a_string)
: m_string(copy(a_string))
, m_size(size(a_string))
{
}

template <typename T>
size_t String<T>::size(const T* a_string)
{
	if(0 == a_string)
	{
		return 0;
	}
	
	return Helper<T>::Len(a_string);
}


template <typename T>
typename String<T>::iterator String<T>::Begin()
{
	return const_cast<iterator>(static_cast<const String&>(*this).Begin());
}

template <typename T>
typename String<T>::const_iterator String<T>::Begin() const
{
	return m_string;
}

template <typename T>
typename String<T>::iterator String<T>::End()
{
	return const_cast<iterator>(static_cast<const String&>(*this).End());
}

template <typename T>
typename String<T>::const_iterator String<T>::End() const
{
	return (m_string + Size());	
}

template <typename T>
typename String<T>::reverse_iterator String<T>::RBegin()
{	
	reverse_iterator iter((m_string + Size() - 1), *this);
	return iter;		
}

template <typename T>
typename String<T>::const_reverse_iterator String<T>::RBegin() const
{
	return const_reverse_iterator((m_string + Size() - 1), *this);		
}

template <typename T>
typename String<T>::reverse_iterator String<T>::REnd()
{
	return const_reverse_iterator((m_string + Size()),*this);		
}

template <typename T>
typename String<T>::const_reverse_iterator String<T>::REnd() const
{
	return const_reverse_iterator((m_string + Size()),*this);		
}

template <typename T>
typename String<T>::iterator String<T>::Find(const String<T>& a_string) 
{
	return const_cast<iterator>(static_cast<const String&>(*this).Find(a_string));
}

template <typename T>
typename String<T>::const_iterator String<T>::Find(const String<T>& a_string) const
{
	return std::search(Begin(), End(), a_string.Begin(), a_string.End());
}


template <typename T>
String<T>& String<T>::operator *=(size_t a_num)
{
	String<T> tmpString(*this);
	
	size_t newSize = Size() * a_num + 1;
	
	T* tmp = new T[newSize];
	
	std::generate_n(tmp, newSize-1, Multiplication<T>(tmpString));

	tmp[newSize] = Helper<T>::End();
	
	delete[] m_string;
	
	m_string = tmp;
	
	m_size = newSize;
	
	return *this;
}

template <typename T>
String<T>& String<T>::operator +=(const char* a_string)
{
	String tmp(a_string);
	
	*this += tmp;
	
	return *this;
} 

template <typename T>
String<T>& String<T>::operator +=(const T& a_letter)
{
	T* newString = new T[Size() + 2];
	
	std::copy(Begin(), End(), newString);
	
	newString[Size()] = a_letter;
	newString[Size() + 1] = Helper<T>::End();	
		
	delete[] m_string;
	
	m_string = newString;
	
	m_size = Size() + 1;
	
	return *this;
}

template <typename T>
String<T>& String<T>::operator +=(const String<T>& a_string)
{
	T* newString = new T[a_string.Size() + Size() + 1];
	
	std::copy(Begin(), End(), newString);
	std::copy(a_string.Begin(), a_string.End(), newString + Size());
	
    delete[] m_string;
	
	m_string = newString;
	
	m_size = a_string.Size() + Size();
	
	return *this;
}

template <typename T>
void String<T>::Resize(size_t a_newSize)
{
	size_t newSize = a_newSize + 1;
	
	T* newString = new T[newSize];	
	
	std::copy(Begin(), Begin() + a_newSize , newString);
	
	newString[a_newSize] = Helper<T>::End();
	
    delete[] m_string;
	
	m_string = newString;
	
	m_size = a_newSize;	
}

template <typename T>
String<T>& String<T>::operator =(const String& a_string)
{
	String<T> tmp(a_string);
	
	swap(tmp);

	return *this;
}

template <typename T>
void String<T>::swap(String<T>& a_string)
{
	T* tmp = a_string.m_string;
	a_string.m_string = m_string;
	m_string = tmp;
	
	size_t sizeTmp = a_string.Size();
	a_string.m_size = m_size;
	m_size = sizeTmp;
}

template <typename T>
T& String<T>::operator[](size_t a_index)
{
	return const_cast<T&>(static_cast<const String&>(*this)[a_index]);
}

template <typename T>
const T& String<T>::operator[](size_t a_index) const
{
	assert(a_index < Size());
	
	return m_string[a_index];
}

template <typename T>
const T* String<T>::myString() const
{
	return m_string;
}

template <typename T>
String<T>::String(const String& a_string)
{
	m_string = copy(a_string.myString());
	m_size = a_string.Size();
}

template <typename T>
String<T>::~String()
{
	delete[] m_string;
}

template <typename T>
T* String<T>::copy(const T* a_string)
{
	if(0 == a_string)
	{
		T *string = new T;
		string[0] = Helper<T>::End();
		return string;
	}	
	
	T *string = new T[Helper<T>::Len(a_string) + 1];
	
		std::copy(a_string, a_string+Helper<T>::Len(a_string) ,
		string);

	return string;
}

template <typename T>
std::ostream& String<T>::Print(std::ostream& a_os) const
{
	std::for_each(Begin(), End(), Printer<T>(a_os));
	
	return a_os;
}

template <typename T>
size_t String<T>::Size() const
{
	return m_size;
}

template <typename T>
std::ostream& operator<<(std::ostream& a_os, const String<T>& a_string)
{
	return a_string.Print(a_os);
}


template <typename T>
std::istream& operator >>(std::istream& a_is, String<T>& a_string)
{
	return a_string.Scan(a_is);	
}

template <typename T>
std::istream& String<T>::Scan(std::istream& a_is)
{
	T *tmp = new T[SIZE_BUFFER];
	
	a_is >> tmp;
	
	delete[] m_string;
	
	m_string = tmp;
	
	Resize(Helper<T>::Len(tmp));
	
	return a_is;
	
}

template <typename T>
String<T> operator +(const String<T>& a_string, const T& a_letter)
{
	String<T> newString(a_string);
	
	newString += a_letter;
	
	return newString;
}

template <typename T>
String<T> operator +(const T& a_letter, const String<T>& a_string)
{
	String<T> newString;
	
	newString += a_letter;
	
	newString += a_string;
	
	return newString;
}

template <typename T>
String<T> operator +(const String<T>& a_first, const String<T>& a_second)
{
	String<T> newString(a_first);
	
	newString += a_second;
	
	return newString;
}

template <typename T>
String<T> operator +(const String<T>& a_first, const char* a_second)
{
	String<T> newString(a_first);	
	
	newString += a_second;
	
	return newString;
}

template <typename T>
String<T> operator +(const char* a_first, const String<T>& a_second)
{
	String<T> newString(a_first);	
	
	newString += a_second;
	
	return newString;
}

template <typename T>
bool operator ==(const String<T>& a_first, const String<T>& a_second)
{
	return !Helper<T>::Cmp(a_first.myString(), a_second.myString());
}

template <typename T>
bool operator ==(const char* a_first, const String<T>& a_second)
{
	return !Helper<T>::Cmp(a_first, a_second.myString());	
}

template <typename T>
bool operator ==(const String<T>& a_first, const char* a_second)
{
	return a_second == a_first;
}

template <typename T>
bool operator !=(const String<T>& a_first, const  String<T>& a_second)
{
	return !(a_first == a_second);
}

template <typename T>
bool operator !=(const char* a_first, const String<T>& a_second)
{
	return !(a_first == a_second);	
}

template <typename T>
bool operator !=(const String<T>& a_first, const char* a_second)
{
	return !(a_first == a_second);		
}

template <typename T>
bool operator >=(const String<T>& a_first, const String<T>& a_second)
{
	return (Helper<T>::Cmp(a_first.myString(), a_second.myString()) >= 0);
}

template <typename T>
bool operator >=(const char* a_first, const String<T>& a_second)
{
	return (Helper<T>::Cmp(a_first, a_second.myString()) >= 0);
}

template <typename T>
bool operator >=(const String<T>& a_first, const char* a_second)
{
	return (Helper<T>::Cmp(a_first.myString(), a_second) >= 0);
}

template <typename T>
bool operator <=(const String<T>& a_first, const String<T>& a_second)
{
	return (Helper<T>::Cmp(a_first.myString(), a_second.myString()) <= 0); 	
}

template <typename T>
bool operator <=(const char* a_first, const String<T>& a_second)
{
	return (Helper<T>::Cmp(a_first, a_second.myString()) <= 0);
}

template <typename T>
bool operator <=(const String<T>& a_first, const char* a_second)
{
	return (Helper<T>::Cmp(a_first.myString(), a_second) <= 0);
}

template <typename T>
bool operator <(const String<T>& a_first, const String<T>& a_second)
{
	return !(a_first >= a_second);
}

template <typename T>
bool operator <(const char* a_first, const String<T>& a_second)
{
	return !(a_first >= a_second);	
}

template <typename T>
bool operator <(const String<T>& a_first, const char* a_second)
{
	return !(a_first >= a_second);		
}

template <typename T>
bool operator >(const String<T>& a_first, const String<T>& a_second)
{
	return !(a_first <= a_second);
}

template <typename T>
bool operator >(const char* a_first, const String<T>& a_second)
{
	return !(a_first <= a_second);
}

template <typename T>
bool operator >(const String<T>& a_first, const char* a_second)
{
	return !(a_first <= a_second);	
}

template <typename T>
void String<T>::ToUpper()
{
	 std::transform(Begin(), End(), Begin(), Helper<T>::Upper);
}

template <typename T>
void String<T>::ToLower()
{
	 std::transform(Begin(), End(), Begin(), Helper<T>::Lower);
}

template <typename T>
Multiplication<T>::Multiplication(const String<T>& a_string)
: m_string(a_string)
, m_iter(a_string.Begin())
{
}

template <typename T>
T Multiplication<T>::operator()()
{
	T tmp = *m_iter;
	
	++m_iter;
	
	if(m_iter == m_string.End())
	{
		 m_iter = m_string.Begin();
	}
	
	return tmp;
}

template <typename T>
Printer<T>::Printer(std::ostream& a_os)
: m_os(a_os)
{
}	

template <typename T>
void Printer<T>::operator()(const T& a_char)
{
	m_os << a_char ;
}

} // advcpp
