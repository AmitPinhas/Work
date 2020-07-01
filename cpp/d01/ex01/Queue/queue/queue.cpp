#include <cstdio>
#include "queue.hpp"


/***********************************/
void Queue::Inset(int a_num)
{
	m_master.Push(a_num) ;
}
/***********************************/
int Queue::Remove()
{
	int returnItem ;
	
	m_tmp.Drain( m_master ) ;
	
	
}
/***********************************/
size_t Stack::Size()
{	
	return m_tos ;
}
/***********************************/
size_t Stack::Capacity()
{	
	return CAPACITY ;
}
/***********************************/
size_t Stack::Drain(Stack *a_s)
{
	unsigned int i ;	
	size_t numItems = (*a_s).Size() ;
	
	for ( i = 0 ; i < numItems ; ++i )
	{
		Push( (*a_s).Pop() ) ;
	}
	
	return ( i - 1 ) ;
}
/***********************************/
void Stack::Print()
{
	unsigned int i ;	
	
	printf("Last ");
	
	for ( i = 0 ; i < m_tos ; ++i )
	{
		printf("%d ", m_data[ i ] ) ;
	}
	
	printf("Top\n");
}
/***********************************/
