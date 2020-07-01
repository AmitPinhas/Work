#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include "stack.hpp"

class Queue {
public:
	void	EnQueue(int a_num);
	int		DeQueue();
	
	size_t	Size();
	size_t	Capacity();
	bool 	IsEmpty();
	bool	IsNotEmpty();
	bool 	IsFull();
	bool	IsNotFull();
		
	void	Print();
		
private:
	void flipPush(int a_num);
	void flipShakePush(int a_nume);
private:
	Stack	m_first ;	
	Stack	m_second ;
};


/**********************************************************************************/

inline int Queue::DeQueue()
{
	assert( IsNotEmpty() ) ;
	
	if ( m_second.IsEmpty() )
	{
		m_second.Drain(&m_first);	
	}
	
	assert( m_second.IsNotEmpty() );
	
	return m_second.Pop();
				
}

inline size_t Queue::Size()
{	
	return m_first.Size() + m_second.Size() ;
}

inline size_t Queue::Capacity()
{	
	return m_first.Capacity() + m_second.Capacity() ;
}

inline bool Queue::IsEmpty()
{
	return m_first.IsEmpty() && m_second.IsEmpty() ;
}

inline bool Queue::IsFull()
{
	return m_first.IsFull() && m_second.IsFull() ;
}

inline bool Queue::IsNotFull()
{
	return Size() < Capacity() ;
}

inline bool	Queue::IsNotEmpty()
{
	return Size() > 0 ;
}


#endif /* QUEUE_HPP */




