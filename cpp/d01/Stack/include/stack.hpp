#ifndef STACK_HPP
#define STACK_HPP

#include <cassert>
#include <cstddef>
#include "exception_stack.hpp"

class Stack {
public:
	Stack();

	void	Push(int a_num);
	int		Pop();
	int		Top();
	size_t	Drain(Stack *a_s);
	
	size_t	Size();
	size_t	Capacity();
	bool 	IsEmpty();
	bool	IsNotEmpty();
	bool 	IsFull();
	bool	IsNotFull();
		
	void	Print();		
private:
	static const size_t CAPACITY = 64;	
	int				m_data[CAPACITY] ;	
	unsigned int	m_tos ;
};

/********************************************************************************************/

inline void Stack::Push(int a_num)
{
	if(m_tos >= CAPACITY)
	{
		throw advcpp::ExceptionOverFlow();
	} 
//	assert(m_tos < CAPACITY);	
	m_data[m_tos++] = a_num ;		
}

inline int Stack::Pop()
{
	if(m_tos == 0)
	{
		throw advcpp::ExceptionUnderFlow();
	} 	
//	assert(m_tos != 0);	
	return m_data[--m_tos] ;
}

inline int Stack::Top()
{
	assert( IsNotEmpty() ) ;
	return m_data[m_tos - 1] ;
}

inline size_t Stack::Size()
{	
	return m_tos ;
}

inline size_t Stack::Capacity()
{	
	return CAPACITY ;
}

inline bool Stack::IsEmpty()
{
	return Size() == 0 ;
}

inline bool Stack::IsNotEmpty()
{
	return Size() > 0 ;
}

inline bool Stack::IsFull()
{
	return Size() == Capacity() ;
}

inline bool Stack::IsNotFull()
{
	return Size() < Capacity() ;
}



#endif /* STACK_HPP */


