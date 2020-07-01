#ifndef STRING_H
#define SRTING_H

#include "r_iterator.hpp"

namespace advcpp
{

template <typename T = char>
class String
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef RIterator<String<T> > reverse_iterator;
	typedef const RIterator<String<T> > const_reverse_iterator;
	typedef T value_type;

	explicit String(const T* a_string = 0);
	
	String(const String& a_string);
	
	~String();
	
	String<T>& operator =(const String& a_string);
	
	String<T>& operator +=(const T& a_letter);
	String<T>& operator +=(const String<T>& a_string);
	String<T>& operator +=(const char* a_string); 
	
	String<T>& operator *=(size_t a_num);

	T& operator[](size_t a_index);
	const T& operator[](size_t a_index) const;

	reverse_iterator RBegin();
	const_reverse_iterator RBegin() const;

	iterator Begin();
	const_iterator Begin() const;
	
	reverse_iterator REnd();
	const_reverse_iterator REnd() const;
	
	iterator End();
	const_iterator End() const;
		
	iterator Find(const String<T>& a_string);
	const_iterator Find(const String<T>& a_string) const;
	
	void ToUpper();
	void ToLower();
	
	size_t Size() const;
	
	void Resize(size_t a_newSize);
	
	std::ostream& Print(std::ostream& a_os) const;

	std::istream& Scan(std::istream& a_os);
	
	const T* myString() const;
	
private:
	void swap(String<T>& a_string);
    T* copy(const T* a_string);
    size_t size(const T* a_string);
    static const size_t SIZE_BUFFER = 255;
	
private:
	T *m_string;
	size_t m_size;
};

template <typename T>
std::ostream& operator <<(std::ostream& a_os, const String<T>& a_string);

template <typename T>
std::istream& operator >>(std::istream& a_is, String<T>& a_string);

template <typename T>
String<T> operator +(const String<T>& a_string, const T& a_letter);

template <typename T>
String<T> operator +(const T& a_letter, const String<T>& a_string);

template <typename T>
String<T> operator +(const String<T>& a_first, const char* a_second);

template <typename T>
String<T> operator +(const char* a_first, const String<T>& a_second);

template <typename T>
String<T> operator +(const String<T>& a_first, const String<T>& a_second);

template <typename T>
bool operator ==(const String<T>& a_first, const String<T>& a_second);

template <typename T>
bool operator ==(const char* a_first, const String<T>& a_second);

template <typename T>
bool operator ==(const String<T>& a_first, const char* a_second);

template <typename T>
bool operator !=(const String<T>& a_first, const String<T>& a_second);

template <typename T>
bool operator !=(const char* a_first, const String<T>& a_second);

template <typename T>
bool operator !=(const String<T>& a_first, const char* a_second);

template <typename T>
bool operator >=(const String<T>& a_first, const String<T>& a_second);

template <typename T>
bool operator >=(const char* a_first, const String<T>& a_second);

template <typename T>
bool operator >=(const String<T>& a_first, const char* a_second);

template <typename T>
bool operator <=(const String<T>& a_first, const String<T>& a_second);

template <typename T>
bool operator <=(const char* a_first, const String<T>& a_second);

template <typename T>
bool operator <=(const String<T>& a_first, const char* a_second);

template <typename T>
bool operator <(const String<T>& a_first, const String<T>& a_second);

template <typename T>
bool operator <(const char* a_first, const String<T>& a_second);

template <typename T>
bool operator <(const String<T>& a_first, const char* a_second);

template <typename T>
bool operator >(const String<T>& a_first, const String<T>& a_second);

template <typename T>
bool operator >(const char* a_first, const String<T>& a_second);

template <typename T>
bool operator >(const String<T>& a_first, const char* a_second);

template <typename T>
class Multiplication
{
public:
	explicit Multiplication(const String<T>& a_string);
	
	T operator()();

private:
	const String<T>& m_string;
	typename String<T>::const_iterator m_iter;
};

template <typename T>
class Printer
{
public:
	explicit Printer(std::ostream& a_os);
	
	void operator()(const T& a_char);	

private:
	std::ostream& m_os;
};

} // advcpp namespace

#include "inl/string.inl"

#endif // STRING_H
