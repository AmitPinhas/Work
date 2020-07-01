#ifndef IQ_STRING_H
#define IQ_STRING_H

#include <algorithm> // for each

namespace advcpp
{

template <typename T>
class MyCensor
{
public:
	MyCensor(T& a_string, typename T::value_type a_newValue);
	
	void operator()(typename T::value_type a_oldValue);

private:
	T& m_string;
	typename T::value_type m_newValue;
};	

template <typename T>
MyCensor<T>::MyCensor(T& a_string, typename T::value_type a_newValue)
: m_string(a_string)
, m_newValue(a_newValue)
{
}

template <typename T>
void MyCensor<T>::operator()(typename T::value_type a_oldValue)
{
	std::replace(m_string.Begin(), m_string.End(), a_oldValue, m_newValue);
}

template <typename T>
void Censor(T& a_first, T& a_second, typename T::value_type a_newValue)
{
	std::for_each(a_second.Begin(), a_second.End(),
	MyCensor<T>(a_first, a_newValue));
}


template <typename T>
class Intersection
{
public:
	explicit Intersection(const T& a_string, T& a_result);	
	
	void operator()(typename T::value_type a_value);

private:
	T& m_result;
	const T& m_string;
};


template <typename T>
Intersection<T>::Intersection(const T& a_string, T& a_result)
: m_result(a_result)
, m_string(a_string)
{
}

template <typename T>
void Intersection<T>::operator()(typename T::value_type a_value)
{
	typename T::const_iterator iter;
	
	iter = std::find(m_string.Begin(), m_string.End(), a_value);
	
	if(iter !=  m_string.End())
	{
		iter = std::find(m_result.Begin(), m_result.End(), a_value);
		
		if(iter == m_result.End())
		{
			m_result += a_value;
		}
	}
}

template <typename T>
class Difference
{
public:
	explicit Difference(const T& a_string, T& a_result);
	
	void operator()(typename T::value_type a_value);

private:
	T& m_result;
	const T& m_string;
};


template <typename T>
Difference<T>::Difference(const T& a_string, T& a_result)
: m_result(a_result)
, m_string(a_string)
{
}

template <typename T>
void Difference<T>::operator()(typename T::value_type a_value)
{
	typename T::const_iterator iter;
	
	iter = std::find(m_string.Begin(), m_string.End(), a_value);
	
	if(iter ==  m_string.End())
	{
		iter = std::find(m_result.Begin(), m_result.End(), a_value);
		
		if(iter == m_result.End())
		{
			m_result += a_value;
		}
	}
	
}

template <typename T>
T OnlyFirstAndSecond(const T& a_first, const T& a_second, const T& a_third)
{
	T resultInter;
	Intersection<T> inter(a_second, resultInter);
	
	std::for_each(a_first.Begin(), a_first.End(), inter);
		
	T resultDiffer;	
	
	Difference<T> differ(a_third, resultDiffer);
	
	std::for_each(resultInter.Begin(), resultInter.End(), differ);
	
	return resultDiffer;
}

template <typename T>
class MyUnique
{
public:
	explicit MyUnique(const T& a_string);
	
	bool operator()(typename T::value_type a_value);
	
private:
	const T& m_string;
};

template <typename T>
MyUnique<T>::MyUnique(const T& a_string)
: m_string(a_string)
{
}

template <typename T>
bool MyUnique<T>::operator()(typename T::value_type a_value)
{
	static size_t m_index;
	
	typename T::const_iterator iter;
	
	++m_index;
	
	iter = std::find(m_string.Begin() + m_index, m_string.End(), a_value);
	
	if(iter == m_string.End())
	{
		return true;
	}
	
	return false;
}

template <typename T>
class MyNotUnique
{
public:
	explicit MyNotUnique(const T& a_string);
	
	bool operator()(typename T::value_type a_value);
	
private:
	const T& m_string;
};

template <typename T>
MyNotUnique<T>::MyNotUnique(const T& a_string)
: m_string(a_string)
{
}

template <typename T>
bool MyNotUnique<T>::operator()(typename T::value_type a_value)
{
	static size_t m_index;
	
	typename T::const_iterator iter;
	
	++m_index;
	
	iter = std::find(m_string.Begin() + m_index, m_string.End(), a_value);
	
	if(iter != m_string.End())
	{
		return true;
	}
	
	return false;
}

template <typename T>
typename T::value_type Unique(const T& a_string)
{
	typename T::const_iterator iter;
	
	iter = std::find_if(a_string.Begin(), a_string.End(), (MyUnique<T>(a_string)));
	
	return *iter;
}

template <typename T>
typename T::value_type NotUnique(const T& a_string)
{
	typename T::const_iterator iter;
	
	iter = std::find_if(a_string.Begin(), a_string.End(), (MyNotUnique<T>(a_string)));
	
	return *iter;
}
	
} // namespace advcpp


#endif // IQ_STRING_H
