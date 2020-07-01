#ifndef LIST_TEST_HPP
#define LIST_TEST_HPP

size_t FillListPushHead( List<> &list )
{
	size_t n = rand() % 145430 ;
	size_t size = n ;
	
	while ( n-- > 0)
	{
		list.PushHead(rand() % 145430);
	}
	return size;	
}

size_t FillListPushTail( List<> &list )
{
	size_t n = rand() % 145430 ;
	size_t size = n ;
	
	while ( n-- > 0)
	{
		list.PushHead(rand() % 145430);
	}
	return size;	
}

#endif /* LIST_TEST_HPP */
