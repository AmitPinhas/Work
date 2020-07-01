#include <cstdio>
#include "stack.hpp"


/***********************************/
Stack::Stack()
{
	m_tos = 0;
}
/***********************************/
size_t Stack::Drain(Stack *a_s)
{
	if ( NULL == a_s )
	{
		return 0 ;
	}
	
	size_t numItems = a_s -> Size() ;
	size_t numItemsInsert = 0 ;
	
	while((Capacity() > Size()) && (numItems-- > 0 ) )
	{
		Push( a_s->Pop() ) ;
		numItemsInsert++ ;
	}
	
	return numItemsInsert ;
}
/***********************************/
void Stack::Print()
{
	size_t n = Size();

	while(n-- > 0){
		printf("%d ", m_data[n]);
	}

}
