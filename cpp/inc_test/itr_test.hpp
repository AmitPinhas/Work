#ifndef ITR_TEST_HPP
#define ITR_TEST_HPP

#include <iostream> // cout
#include <cstdlib> //size_t, srand, rand
#include <ctime>  // time 


struct Seed{
    Seed()
    {
        srand(time(0));
    }
};
static Seed g_seed;

template <typename T>
void Print(T const& a_v)
{
    typename T::const_iterator it = a_v.begin();
    typename T::const_iterator const end = a_v.end();
    while (it != end){
        std::cout << *it << ", ";
        ++it;
    }
    std::cout << '\n';
}

template <typename T, typename U>
struct Sequence {    	
    Sequence(U const& a_delta, T const& a_iv = T());
    
    T operator()();

private:
    T m_initialValue;
    U m_delta;	    
};

template <typename T, typename U>
Sequence<T,U>::Sequence(U const& a_delta, T const& a_iv)
: m_initialValue(a_iv)
, m_delta(a_delta)
{
}

template <typename T, typename U>
T Sequence<T,U>::operator()()
{
	T v = m_initialValue;
	m_initialValue += m_delta;
	return v;	
}

template <typename T, typename U>
Sequence<T,U> MakeSequence(T const& a_delta, U const& a_vi){
    return Sequence<T,U>(a_delta, a_vi);
}

template <typename T>
Sequence<T,T> MakeSequence(T const& a_delta = T()){
    return Sequence<T,T>(a_delta, T());
}

template <typename T, typename G>
// G: Nullary Function:   T operator()();
void Fill(T & a_vector, size_t a_size, G generate) 
{    
    a_vector.reserve(a_size);
    while(a_size -- > 0)    
    {
        a_vector.push_back( generate() );
    }
}

template <typename T>
void FillRandom (T & a_vector, size_t a_size) 
{    
    a_vector.reserve(a_size);
    while(a_size -- > 0)    
    {
        a_vector.push_back(rand());
    }
}

template <typename Iter>
bool MinToMax(Iter a_begin,const Iter a_end)
{
	if( a_begin == a_end)
	{
		return true;
	}

	Iter first = a_begin;
	Iter second = ++a_begin;
	
	while(second != a_end)
	{
		if( *first > *second)
		{
			return false;
		}
		++first;
		++second;
	}
	return true;
}


#endif // ITR_TEST_HPP
