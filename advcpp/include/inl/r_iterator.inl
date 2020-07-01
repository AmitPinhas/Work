
namespace advcpp
{

template <typename T>
RIterator<T>::RIterator(const typename T::iterator a_rIter, T& a_string)
: m_string(a_string)
, m_rIter(a_rIter)
{
}

template <typename T>
typename RIterator<T>::value_type& RIterator<T>::operator *()
{
	return *m_rIter;
}

template <typename T>
RIterator<T>& RIterator<T>::operator++()
{
	if(m_rIter != m_string.Begin())
	{
		--m_rIter;
		return *this;
	}

	m_rIter = m_string.End();
	return *this;
	
}                                                                 

template <typename T>
RIterator<T>& RIterator<T>::operator--()
{
	return ++m_rIter;
}

template <typename T>
const typename RIterator<T>::iterator RIterator<T>::MyIter() const
{
	return m_rIter;
}

template <typename T>
bool operator ==(RIterator<T> a_first, RIterator<T> a_second)
{
	return a_first.MyIter() == a_second.MyIter() ;
}

template <typename T>
bool operator !=(RIterator<T> a_first, RIterator<T> a_second)
{
	return !(a_first == a_second) ;
}

template <typename T>
bool operator <=(RIterator<T> a_first, RIterator<T> a_second)
{
	return a_first.MyIter() <= a_second.MyIter() ;
}

template <typename T>
bool operator >=(RIterator<T> a_first, RIterator<T> a_second)
{
	return a_first.MyIter() >= a_second.MyIter() ;	
}

template <typename T>
bool operator <(RIterator<T> a_first, RIterator<T> a_second)
{
	return !(a_first.MyIter() >= a_second.MyIter()) ;	
}

template <typename T>
bool operator >(RIterator<T> a_first, RIterator<T> a_second)
{
	return !(a_first.MyIter() <= a_second.MyIter()) ;	
}

template <typename T>
RIterator<T>& RIterator<T>::operator +=(size_t a_num)
{
	m_rIter -= a_num;
	return  *this;
}

template <typename T>
RIterator<T>& RIterator<T>::operator -=(size_t a_num)
{
	m_rIter += a_num;
	return  *this;	
}

template <typename T>
RIterator<T> operator +(RIterator<T> a_iter, size_t a_num)
{
	return a_iter.MyIter() + a_num;
}

template <typename T>
RIterator<T> operator +(size_t a_num, RIterator<T> a_iter)
{
	return a_iter.MyIter() + a_num;	
}

template <typename T>
RIterator<T> operator -(RIterator<T> a_iter, size_t a_num)
{
	return a_iter.MyIter() - a_num;
}

template <typename T>
RIterator<T> operator -(RIterator<T> a_first, RIterator<T> a_second)
{
	return a_first.MyIter() - a_second.MyIter();
}


} // namespace advcpp
