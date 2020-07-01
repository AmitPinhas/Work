#include "mu_test.h"
#include "list.hpp"
#include "list_test.hpp"


UNIT(head)

	List<> list;
	
	FillListPushHead( list );
	
	list.PushHead(145);
	
	ASSERT_EQUAL( list.Head(), 145 );

END_UNIT

UNIT(tail)

	List<> list;
	
	FillListPushTail( list );
	
	list.PushTail(1212);
	
	ASSERT_EQUAL( list.Tail(), 1212 );
	
END_UNIT

UNIT(push_head)

	List<> list;

	size_t size = FillListPushHead(list);
	
	ASSERT_EQUAL( list.Size(), size );

END_UNIT

UNIT(push_tail)

	List<> list;

	size_t size = FillListPushTail( list );

	ASSERT_EQUAL( list.Size(), size );

END_UNIT

UNIT(size_empty)

	List<> list;
	
	ASSERT_EQUAL( list.Size(), 0 );
	
END_UNIT

UNIT(size)
	List<> list;
	
	size_t size = FillListPushHead(list);

	list.PushHead(10);
	ASSERT_EQUAL( list.Size(), size+1 );
	
	list.PushHead(11);
	ASSERT_EQUAL( list.Size(), size+2 );
	
	list.PushTail(13);
	ASSERT_EQUAL( list.Size(), size+3 );	

END_UNIT

UNIT(find_empty)

	List<> list;
	
	ASSERT_EQUAL( list.Find(546), 0 );
	
END_UNIT


UNIT(find)

	List<> list;
	
	list.PushHead(10);
	ASSERT_EQUAL( *(list.Find(10)), 10 );
	ASSERT_EQUAL( list.Find(546), 0 );
	
	list.PushHead(11);
	ASSERT_EQUAL( list.Head(), 11);	
	ASSERT_EQUAL( list.Tail(), 10);
	ASSERT_EQUAL( list.Size(), 2 );
	ASSERT_EQUAL( *(list.Find(10)), 10 );
	ASSERT_EQUAL( *(list.Find(11)), 11 );	
	ASSERT_EQUAL( list.Find(546), 0 );
		
	list.PushTail(13);
	ASSERT_EQUAL( list.Head(), 11);	
	ASSERT_EQUAL( list.Tail(), 13);
	ASSERT_EQUAL( list.Size(), 3 );	
	ASSERT_EQUAL( *(list.Find(10)), 10 );
	ASSERT_EQUAL( *(list.Find(11)), 11 );	
	ASSERT_EQUAL( *(list.Find(13)), 13 );	
	ASSERT_EQUAL( list.Find(546), 0 );

END_UNIT

UNIT(pop_head)

	List<> list;
	
	ASSERT_EQUAL( list.Size(), 0 );
	ASSERT_EQUAL( list.Find(546), 0 );
	
	list.PushHead(10);
	ASSERT_EQUAL( list.Head(), 10);
	ASSERT_EQUAL( list.Tail(), 10);
	ASSERT_EQUAL( list.Size(), 1 );
	ASSERT_EQUAL( *(list.Find(10)), 10 );
	ASSERT_EQUAL( list.Find(546), 0 );
	
	ASSERT_EQUAL( list.PopHead(), 10);
	
	list.PushHead(11);
	ASSERT_EQUAL( list.Head(), 11);	
	ASSERT_EQUAL( list.Tail(), 11);
	ASSERT_EQUAL( list.Size(), 1 );
	
	list.PushTail(13);
	ASSERT_EQUAL( list.Head(), 11);	
	ASSERT_EQUAL( list.Tail(), 13);
	ASSERT_EQUAL( list.Size(), 2 );

END_UNIT


UNIT(pop_tail)

	List<> list;
	
	list.PushHead(10);	
	list.PushHead(11);
	ASSERT_EQUAL( list.Head(), 11);	
	ASSERT_EQUAL( list.Tail(), 10);
	ASSERT_EQUAL( list.Size(), 2 );
	
	ASSERT_EQUAL( list.PopTail(), 10);
	
	list.PushTail(13);
	ASSERT_EQUAL( list.Head(), 11);	
	ASSERT_EQUAL( list.Tail(), 13);
	ASSERT_EQUAL( list.Size(), 2 );

END_UNIT

UNIT(remove_not_in_list)

	List<> list;
	
	ASSERT_EQUAL(list.Remove(43534), 0);
	
END_UNIT


UNIT(remove)

	List<> list;
	
	list.PushHead(10);	
	ASSERT_EQUAL(list.Remove(10), 1);
	list.PushHead(11);
	ASSERT_EQUAL( list.Head(), 11);	
	ASSERT_EQUAL( list.Tail(), 11);
	ASSERT_EQUAL( list.Size(), 1 );
	
	ASSERT_EQUAL( list.PopTail(), 11);
	
	list.PushTail(13);
	ASSERT_EQUAL( list.Head(), 13);	
	ASSERT_EQUAL( list.Tail(), 13);
	ASSERT_EQUAL( list.Size(), 1 );
	
	list.PushHead(20);
	list.PushHead(20);
	list.PushHead(20);
	list.PushHead(20);
	ASSERT_EQUAL( list.Size(), 5 );
	
	ASSERT_EQUAL(list.Remove(20), 4);
	ASSERT_EQUAL( list.Size(), 1 );

END_UNIT


UNIT(copy_constructor)
	List<> list;
	
	list.PushHead(20);
	list.PushHead(20);
	list.PushHead(20);
	list.PushHead(20);
	
	ASSERT_EQUAL( list.Size(), 4);
	ASSERT_EQUAL( list.Head(), 20);	
	
	List<> listCopy(list);
	
	ASSERT_EQUAL( listCopy.Size(), 4);
	ASSERT_EQUAL( listCopy.Head(), 20);
	
	listCopy.PushHead(50);
	
	ASSERT_EQUAL( listCopy.Size(), 5);
	ASSERT_EQUAL( listCopy.Head(), 50);
	ASSERT_EQUAL( list.Size(), 4);
	ASSERT_EQUAL( list.Head(), 20);		
		
END_UNIT


UNIT(assignment)
	List<> list;
	
	size_t size = FillListPushHead(list);

	list.PushHead(20);
	
	ASSERT_EQUAL( list.Size(), size+1);
	ASSERT_EQUAL( list.Head(), 20);	
	
	List<> listCopy = list;
	
	ASSERT_EQUAL( listCopy.Size(), size+1);
	ASSERT_EQUAL( listCopy.Head(), 20);
	
	listCopy.PushHead(50);
	
	ASSERT_EQUAL( listCopy.Size(), size+2);
	ASSERT_EQUAL( listCopy.Head(), 50);
	ASSERT_EQUAL( list.Size(), size+1);
	ASSERT_EQUAL( list.Head(), 20);	

END_UNIT


UNIT(assignment_to_active_list)
	List<> list;
	
	size_t sizeList = FillListPushHead(list);
	
	list.PushHead(20);
	
	ASSERT_EQUAL( list.Size(), sizeList+1);
	ASSERT_EQUAL( list.Head(), 20);	
	
	List<> listCopy;

	size_t size = FillListPushHead(listCopy);

	listCopy.PushHead(30);
	ASSERT_EQUAL( listCopy.Size(), size+1);
	ASSERT_EQUAL( listCopy.Head(), 30);	
	
	listCopy = list;
	
	listCopy.PushHead(50);
	
	ASSERT_EQUAL( listCopy.Size(), sizeList+2);
	ASSERT_EQUAL( listCopy.Head(), 50);
	ASSERT_EQUAL( list.Size(), sizeList+1);
	ASSERT_EQUAL( list.Head(), 20);	

END_UNIT


UNIT(is_empty_true)

	List<> list;
	
	ASSERT_EQUAL(list.IsEmpty(), 1);

END_UNIT

UNIT(is_empty_false)

	List<> list;
	
	FillListPushHead(list);
	
	ASSERT_EQUAL(list.IsEmpty(), 0);

END_UNIT

UNIT(clear)

	List<> list;
	
	size_t size = FillListPushHead(list);
	
	ASSERT_EQUAL(list.Size(), size);
	
	list.Clear();

	ASSERT_EQUAL(list.Size(), 0);
	
	list.PushHead(111);
	
	ASSERT_EQUAL(list.Size(), 1);	
	
END_UNIT

TEST_SUITE(test the list on fire)

	TEST(head)	
	TEST(tail)
	TEST(push_head)
	TEST(push_tail)
	TEST(size_empty)
	TEST(size)
	TEST(find_empty)
	TEST(find)
	TEST(pop_head)
	TEST(pop_tail)
	TEST(remove_not_in_list)
	TEST(remove)
	TEST(copy_constructor)
	TEST(assignment)
	TEST(assignment_to_active_list)
	TEST(is_empty_true)
	TEST(is_empty_false)
	TEST(clear)

END_SUITE
