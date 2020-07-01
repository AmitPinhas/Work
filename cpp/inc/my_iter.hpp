#ifndef MY_ITER_HPP
#define MY_ITER_HPP

#include <cstddef> // size_t
#include <list>

template <typename T>
class MyIter
{
public:
	MyIter(typename std::list<T>::iterator a_itr);
	
	// MyIter(const MyIter& a_other) = default
	// ~MyIter() = default
	// MyIter& operator=(const MyIter& a_other) = default
	
	MyIter& operator++();
	MyIter operator++(int);
	T& operator*() const;
	
	template <typename D>
	friend bool operator!=(const MyIter<D>& a_first,const MyIter<D>& a_second);
	
	template <typename D>
	friend bool operator==(const MyIter<D>& a_first,const MyIter<D>& a_second);	
	
	template <typename U, typename Less>
	friend class SortedSequence;

private:
	typename std::list<T>::iterator Iter() const;	
	
private:
	typename std::list<T>::iterator m_iter;	
};

template <typename D>
bool operator!=(const MyIter<D>& a_first,const MyIter<D>& a_second)
{
	return a_first.Iter() != a_second.Iter();	
}

template <typename D>
bool operator==(const MyIter<D>& a_first,const MyIter<D>& a_second)
{
	return !(a_first.Iter() != a_second.Iter());	
}

template <typename T>
MyIter<T>::MyIter(typename std::list<T>::iterator a_itr)
: m_iter(a_itr)
{
}

template <typename T>
MyIter<T>& MyIter<T>::operator++()
{
	++m_iter;
	return *this;
}

template <typename T>
MyIter<T> MyIter<T>::operator++(int)
{
	MyIter<T> copy = Iter();
	++*this;
	return copy;
	
}

template <typename T>
T& MyIter<T>::operator*() const
{
	return *Iter();
}

template <typename T>
typename std::list<T>::iterator MyIter<T>::Iter() const
{
	return m_iter;
}

#endif // MY_ITER_HPP
