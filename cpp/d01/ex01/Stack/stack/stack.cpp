#include <cstdio>
#include <cassert>
#include "stack.hpp"


/***********************************/
Stack::Stack()
{
	m_tos = 0;
}
/***********************************/
void Stack::Push(int a_num)
{
	if(m_tos < CAPACITY){
		m_data[m_tos++] = a_num ;		
	}
}
/***********************************/
int Stack::Pop()
{
	if(m_tos == 0){
		return 0;  
	}

	return m_data[--m_tos] ;
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
	if ( NULL == a_s )
	{
		return 0 ;
	}
	
	size_t numItems = a_s->Size() ;
	size_t numItemsReturn = numItems ;
	
	while(numItems-- > 0)
	{
		Push( a_s->Pop() ) ;
	}
	
	return numItemsReturn ;
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
