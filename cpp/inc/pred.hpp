#ifndef PRED_HPP
#define PRED_HPP

template<typename T, typename Comparator>
struct Pred
{
public:
	Pred(T const& a_value, Comparator a_cmp);
	
	bool operator()(T const& a_elemnt) const;
	
private:
	const T& Value() const;	
	
private:
	T const& m_value2Insert;
	Comparator m_cmp;
};

template<typename T, typename Comparator>
Pred<T, Comparator>::Pred(T const& a_value, Comparator a_cmp)
: m_value2Insert(a_value)
, m_cmp(a_cmp)
{
}

template<typename T, typename Comparator>
const T& Pred<T, Comparator>::Value() const
{
	return m_value2Insert;
}

template<typename T, typename Comparator>
bool Pred<T, Comparator>::operator()(T const& a_elemnt) const
{
	return !m_cmp(a_elemnt, Value());
}

#endif // PRED_HPP
