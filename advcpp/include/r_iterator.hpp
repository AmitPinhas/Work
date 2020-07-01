#ifndef R_ITERATOR_H
#define R_ITERATOR_H

namespace advcpp
{

template <typename T>
class RIterator
{
public:
	typedef typename T::iterator iterator;
	typedef typename T::value_type value_type;
	
	RIterator(const iterator a_rIter, T& a_string);
	
	value_type& operator *();
	
	RIterator& operator ++();
	RIterator& operator --();
	
	RIterator& operator +=(size_t a_num);
	RIterator& operator -=(size_t a_num);	
	
	const iterator MyIter() const;

private:
	T& m_string;
	iterator m_rIter;
};

template <typename T>
bool operator ==(RIterator<T> a_first, RIterator<T> a_second);

template <typename T>
bool operator !=(RIterator<T> a_first, RIterator<T> a_second);

template <typename T>
bool operator <=(RIterator<T> a_first, RIterator<T> a_second);

template <typename T>
bool operator >=(RIterator<T> a_first, RIterator<T> a_second);

template <typename T>
bool operator <(RIterator<T> a_first, RIterator<T> a_second);

template <typename T>
bool operator >(RIterator<T> a_first, RIterator<T> a_second);

template <typename T>
RIterator<T> operator +(RIterator<T> a_iter, size_t a_num);

template <typename T>
RIterator<T> operator +(size_t a_num, RIterator<T> a_iter);

template <typename T>
RIterator<T> operator -(RIterator<T> a_iter, size_t a_num);

template <typename T>
RIterator<T> operator -(RIterator<T> a_first, RIterator<T> a_second);

} // namespace advcpp

#include "inl/r_iterator.inl"

#endif // R_ITERATOR_H
