#ifndef SHAPE_TEST_HPP
#define SHAPE_TEST_HPP

#include <iostream>
#include <vector>
#include <cstdlib> //size_t, srand, rand
#include <ctime> // time 
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

const double g_pi = 3.14;

struct Seed{
    Seed()
    {
        srand(time(0));
    }
};
static Seed g_seed;


double AreaRectangle(const int a_height, const int m_width)
{
	return a_height * m_width;
}

double AreaCircle(const int a_radius)
{
	return g_pi * a_radius * a_radius;
}

template <typename Container>
void FillRandomCircle(Container & a_container,size_t a_size) 
{    
    while(a_size-- > 0)    
    {
    	cpp::Circle *myCircle = new cpp::Circle(rand());
        a_container.push_back(myCircle);
    }
}

template <typename Container, typename G>
// G: Nullary Function:   T operator()();
void Fill(Container & a_container, size_t a_size, G a_generate) 
{    
    while(a_size -- > 0)    
    {
    	cpp::Circle *myCircle = new cpp::Circle(a_generate());
        a_container.push_back(myCircle);
    }
}

template <typename Container>
void FillRandomRect(Container & a_container,size_t a_size) 
{    
    while(a_size-- > 0)    
    {
    	cpp::Rectangle *myRectangle = new cpp::Rectangle(rand(), rand());
        a_container.push_back(myRectangle);
    }
}

template <typename Container, typename G>
// G: Nullary Function:   T operator()();
void FillRect(Container & a_container, size_t a_size, G a_generate, G a_generate2) 
{    
    while(a_size -- > 0)    
    {
    	cpp::Rectangle *myRectangle = new cpp::Rectangle(a_generate(),a_generate2());
        a_container.push_back(myRectangle);
    }
}

template <typename Container, typename Iter>
void PopContainer(Container & a_container)
{
	Iter begin = a_container.begin();
	Iter end = a_container.end();
	size_t index = 0;
		
    while(begin != end)    
    {
    	delete a_container[index];
    	++begin;
    	++index;
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

#endif // SHAPE_TEST_HPP
