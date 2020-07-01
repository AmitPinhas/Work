#ifndef SORTED_SEQUANCE_HPP_TEST
#define SORTED_SEQUANCE_HPP_TEST

#include <cstdlib> //size_t, srand, rand
#include <ctime>  // time 
#include "sorted_sequence.hpp"
#include "cat.hpp"

struct Seed{
    Seed()
    {
        srand(time(0));
    }
};
static Seed g_seed;

struct LessInt
{
	bool operator()(int const& a_first, int const& a_second) const;
};

bool LessInt::operator()(int const& a_first, int const& a_second) const
{
	return a_first < a_second;
}

struct LessCats
{
	bool operator()(Cat const & a_catFirst, Cat const & a_catSecond) const;
};

bool LessCats::operator()(Cat const & a_catFirst, Cat const & a_catSecond ) const
{
	return a_catFirst.Age() < a_catSecond.Age();
}

template <typename T,typename U> 
void Print(SortedSequence<T,U> a_list) 
{
	MyIter<T> cur = a_list.Begin();
	MyIter<T> end = a_list.End();
	
	while(cur != end)
	{
		(*cur).Print();
		++cur;
	}
}

template <typename T>
void FillRandom(T & a_list, size_t a_size) 
{    
    while(a_size-- > 0)    
    {
    	Cat avi("avi", 5, rand());
        a_list.Push(avi);
    }
}

template <typename T>
void FillRandomInt(T & a_list, size_t a_size) 
{    
    while(a_size-- > 0)    
    {
        a_list.Push(rand());
    }
}

template <typename T>
void FillRandomTail(T & a_list, size_t a_size) 
{    
    while(a_size-- > 0)    
    {
    	Cat avi("avi", 5, rand());
        a_list.Push(avi, SortedSequence<Cat,LessCats>::TAIL);
    }
}

template <typename T>
void FillRandomTailInt(T & a_list, size_t a_size) 
{    
    while(a_size-- > 0)    
    {
		a_list.Push(rand(), SortedSequence<int,LessInt>::TAIL);
    }
}

template <typename T>
void PopHead(T & a_list, size_t a_size) 
{    
    while(a_size-- > 0)    
    {
    	a_list.PopHead();
    }
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
void Fill(T & a_list, size_t a_size, G generate) 
{    
    while(a_size -- > 0)    
    {
    	Cat avi("avi", 5, generate());
        a_list.Push(avi);
    }
}

template <typename T, typename G>
// G: Nullary Function:   T operator()();
void FillInt(T & a_list, size_t a_size, G generate) 
{    
    while(a_size -- > 0)    
    {
        a_list.Push(generate());
    }
}


#endif // SORTED_SEQUANCE_HPP_TEST
