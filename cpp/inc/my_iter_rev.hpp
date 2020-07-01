#ifndef MY_ITER_REV_HPP
#define MY_ITER_REV_HPP

#include <cstddef> // size_t
#include <list>

template <typename T>
class MyIterRev
{
public:
	MyIterRev(typename std::list<T>::reverse_iterator a_itr);
	
	// MyIterRev(const MyIterRev& a_other) = default
	// ~MyIterRev() = default
	// MyIterRev& operator=(const MyIterRev& a_other) = default
	
	MyIterRev& operator++();
	MyIterRev operator++(int);
	T& operator*() const;
	
	template <typename D>
	friend bool operator!=(const MyIterRev<D>& a_first,const MyIterRev<D>& a_second);
	
	template <typename U, typename Less>
	friend class SortedSequence;

private:
	typename std::list<T>::reverse_iterator Iter() const;	
	typename std::list<T>::iterator Base();
	
private:
	typename std::list<T>::reverse_iterator m_iter;	
};

template <typename D>
bool operator!=(const MyIterRev<D>& a_first,const MyIterRev<D>& a_second)
{
	return a_first.Iter() != a_second.Iter();	
}

template <typename T>
MyIterRev<T>::MyIterRev(typename std::list<T>::reverse_iterator a_itr)
: m_iter(a_itr)
{
}

template <typename T>
MyIterRev<T>& MyIterRev<T>::operator++()
{
	++m_iter;
	return *this;
}

template <typename T>
MyIterRev<T> MyIterRev<T>::operator++(int)
{
	MyIterRev<T> copy = Iter();
	++*this;
	return copy;
	
}

template <typename T>
T& MyIterRev<T>::operator*() const
{
	return *Iter();
}

template <typename T>
typename std::list<T>::reverse_iterator MyIterRev<T>::Iter() const
{
	return m_iter;
}

template <typename T>
typename std::list<T>::iterator MyIterRev<T>::Base()
{
	return Iter().base();
}

#endif // MY_ITER_REV_HPP
