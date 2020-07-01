#include <cstdio>
#include <cassert>
#include "queue.hpp"


/***********************************/
void Queue::EnQueue(int a_num)
{
	assert( IsNotFull() );

	if( m_first.IsNotFull() )
	{
		m_first.Push(a_num) ;
		return;
	}
	if ( m_first.IsFull() && m_second.IsEmpty() )
	{
		flipPush(a_num);
		return;
	}
	if( m_first.IsFull() )
	{
		flipShakePush(a_num);
		return;
	}
}
/***********************************/
void Queue::Print()
{
	Stack tmp ;	
	m_second.Print() ;
	tmp.Drain(&m_first) ;
	tmp.Print() ;
}
/***********************************/
void Queue::flipPush(int a_num)
{
	m_second.Drain(&m_first) ;
	assert(m_first.IsNotFull());
	m_first.Push(a_num);
}
/***********************************/
void Queue::flipShakePush(int a_num)
{
	assert(m_second.IsNotEmpty());
		
	Stack tmp ;
	
	tmp.Drain(&m_second) ;
	m_second.Drain(&m_first) ;
	tmp.Drain(&m_second) ;
	m_first.Drain(&m_second);
	m_second.Drain(&tmp) ;
	
	m_first.Push(a_num);
}
/***********************************/
