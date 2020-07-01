#include "mu_test.h"
#include "sorted_sequence.hpp"
#include "sorted_sequence_test.hpp"
#include "cat.hpp"
#include <vector>

const size_t g_smallSize = 50;
const size_t g_midSize = 500;
const size_t g_bigSize = 50000;

UNIT(size_empty_int)

	SortedSequence<int,LessInt> myList((LessInt()));

	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);
	ASSERT_EQUAL( myList.Size(), 0);

END_UNIT

UNIT(size_empty_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));

	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessCats())), true);
	ASSERT_EQUAL( myList.Size(), 0);

END_UNIT

UNIT(size_big_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillRandomInt(myList, g_smallSize);
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);
	ASSERT_EQUAL( myList.Size(), g_smallSize);

END_UNIT

UNIT(size_big_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	FillRandom(myList, g_smallSize);
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessCats())), true);	
	ASSERT_EQUAL( myList.Size(), g_smallSize);

END_UNIT

UNIT(size_push_and_pop_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillRandomInt(myList, g_smallSize);
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);
	
	PopHead(myList, 20);

	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);

	ASSERT_EQUAL( myList.Size(), g_smallSize-20);

END_UNIT


UNIT(size_push_and_pop_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	FillRandom(myList, g_smallSize);
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessCats())), true);
	
	PopHead(myList, 20);

	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessCats())), true);

	ASSERT_EQUAL( myList.Size(), g_smallSize-20);

END_UNIT


UNIT(push_head_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillRandomInt(myList, g_bigSize);
		
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);	

END_UNIT


UNIT(push_head_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	FillRandom(myList, g_bigSize);
		
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessCats())), true);	

END_UNIT


UNIT(push_tail_int)

	SortedSequence<int,LessInt> myList((LessInt()));

	FillRandomTailInt(myList, g_bigSize);
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);

END_UNIT


UNIT(push_tail_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));

	FillRandomTail(myList, g_bigSize);
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessCats())), true);

END_UNIT


UNIT(pop_head_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillInt(myList, g_bigSize, MakeSequence(-1,g_bigSize-1));
	
	size_t sizePop = g_bigSize;	
	int i = 0 ;
	
	while(sizePop-- > 0)
	{
		ASSERT_EQUAL(myList.PopHead(), i++);
	}	
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);

END_UNIT


UNIT(pop_head_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	Fill(myList, g_bigSize, MakeSequence(-1,g_bigSize-1));
	
	size_t sizePop = g_bigSize;	
	int i = 0 ;
	
	while(sizePop-- > 0)
	{
		ASSERT_EQUAL(myList.PopHead().Age(), i++);
	}	
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessCats())), true);

END_UNIT


UNIT(pop_tail_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillInt(myList, g_bigSize, MakeSequence(-1,g_bigSize-1));
	
	int sizePop = g_bigSize;	
	
	while(sizePop-- > 0)
	{
		ASSERT_EQUAL(myList.PopTail(), sizePop);
	}	
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);	

END_UNIT


UNIT(pop_tail_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	Fill(myList, g_bigSize, MakeSequence(-1,g_bigSize-1));
	
	int sizePop = g_bigSize;	
	
	while(sizePop-- > 0)
	{
		ASSERT_EQUAL(myList.PopTail().Age(), sizePop);
	}	
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessCats())), true);	

END_UNIT

UNIT(remove_not_exists_item_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillInt(myList, g_midSize, MakeSequence(-1,g_midSize-1));
	
	ASSERT_EQUAL(myList.Size(), g_midSize);
	
	ASSERT_EQUAL(myList.Remove(g_midSize*2), 0);
	
	ASSERT_EQUAL(myList.Size(), g_midSize);

END_UNIT

UNIT(remove_not_exists_item_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	Fill(myList, g_midSize, MakeSequence(-1,g_midSize-1));
	
	ASSERT_EQUAL(myList.Size(), g_midSize);
	
	Cat soso("soso", 5, 12);
	
	ASSERT_EQUAL(myList.Remove(soso), 0);
	
	ASSERT_EQUAL(myList.Size(), g_midSize);

END_UNIT

UNIT(remove_one_item_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillInt(myList, g_midSize, MakeSequence(-1,g_midSize-1));

	ASSERT_EQUAL(myList.Size(), g_midSize);	
	
	ASSERT_EQUAL(myList.Remove(12), 1);
	
	ASSERT_EQUAL(myList.Size(), g_midSize-1);		

END_UNIT

UNIT(remove_one_item_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	Fill(myList, g_midSize, MakeSequence(-1,g_midSize-1));

	ASSERT_EQUAL(myList.Size(), g_midSize);	
	
	Cat avi2("avi", 5, 12);
	
	ASSERT_EQUAL(myList.Remove(avi2), 1);
	
	ASSERT_EQUAL(myList.Size(), g_midSize-1);		

END_UNIT

UNIT(remove_first_item_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillInt(myList, g_midSize, MakeSequence(-1,g_midSize-1));
	
	ASSERT_EQUAL(myList.Size(), g_midSize);	
	
	myList.Push(-680);
	
	ASSERT_EQUAL(myList.Size(), g_midSize+1);		
	
	ASSERT_EQUAL(myList.Remove(-680), 1);
	
	ASSERT_EQUAL(myList.Size(), g_midSize);		

END_UNIT

UNIT(remove_first_item_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	Fill(myList, g_midSize, MakeSequence(-1,g_midSize-1));
	
	ASSERT_EQUAL(myList.Size(), g_midSize);	
	
	Cat soso("soso", 5, 0);
	
	myList.Push(soso);
	
	ASSERT_EQUAL(myList.Size(), g_midSize+1);		
	
	ASSERT_EQUAL(myList.Remove(soso), 1);
	
	ASSERT_EQUAL(myList.Size(), g_midSize);		

END_UNIT

UNIT(remove_last_item_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillInt(myList, g_midSize, MakeSequence(-1,g_midSize-1));
	
	ASSERT_EQUAL(myList.Size(), g_midSize);		
	
	myList.Push(1222, SortedSequence<int,LessInt>::TAIL);
	
	ASSERT_EQUAL(myList.Size(), g_midSize+1);		
	
	ASSERT_EQUAL(myList.Remove(1222), 1);
	
	ASSERT_EQUAL(myList.Size(), g_midSize);		

END_UNIT

UNIT(remove_last_item_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	Fill(myList, g_midSize, MakeSequence(-1,g_midSize-1));
	
	ASSERT_EQUAL(myList.Size(), g_midSize);		
	
	Cat soso("soso", 5, 1222);
	
	myList.Push(soso, SortedSequence<Cat,LessCats>::TAIL);
	
	ASSERT_EQUAL(myList.Size(), g_midSize+1);		
	
	ASSERT_EQUAL(myList.Remove(soso), 1);
	
	ASSERT_EQUAL(myList.Size(), g_midSize);		

END_UNIT

UNIT(remove_all_items_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillInt(myList, g_midSize, MakeSequence(0,12));
	
	ASSERT_EQUAL(myList.Size(), g_midSize);		
	
	ASSERT_EQUAL(myList.Remove(12), g_midSize);
	
	ASSERT_EQUAL(myList.Size(), 0);

END_UNIT

UNIT(remove_all_items_cat)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	Fill(myList, g_midSize, MakeSequence(0,12));
	
	ASSERT_EQUAL(myList.Size(), g_midSize);		
	
	Cat soso("avi", 5, 12);
	
	ASSERT_EQUAL(myList.Remove(soso), g_midSize);
	
	ASSERT_EQUAL(myList.Size(), 0);

END_UNIT

UNIT(merge)

	SortedSequence<Cat,LessCats> myList((LessCats()));
	
	FillRandom(myList, g_midSize);
	
	SortedSequence<Cat,LessCats> ListToInsert((LessCats()));
	
	FillRandom(ListToInsert, 100);
	
	ASSERT_EQUAL(Merge(myList, ListToInsert.Begin(), ListToInsert.End()), 100);
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessCats())), true);		

END_UNIT

UNIT(merge_int)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillRandomInt(myList, g_midSize);
	
	SortedSequence<int,LessInt> ListToInsert((LessInt()));
	
	FillRandomInt(ListToInsert, 100);
	
	ASSERT_EQUAL(Merge(myList, ListToInsert.Begin(), ListToInsert.End()), 100);
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);		

END_UNIT

UNIT(merge_vector)

	SortedSequence<int,LessInt> myList((LessInt()));
	
	FillRandomInt(myList, g_midSize);
	
	int vs[]={ 1, 2, 3, 4, 5, 6, 7};
	std::vector<int> vec(vs, vs+7);
	
	ASSERT_EQUAL(Merge(myList, vec.begin(), vec.end()), 7);
	
	ASSERT_EQUAL(IsSorted(myList.Begin(), myList.End(), (LessInt())), true);		

END_UNIT


TEST_SUITE(test the sorted sequence on fire)
	TEST(size_empty_int)
	TEST(size_empty_cat)
	TEST(size_big_int)
	TEST(size_big_cat)
	TEST(size_push_and_pop_int)
	TEST(size_push_and_pop_cat)
	TEST(push_head_int)
	TEST(push_head_cat)
	TEST(push_tail_int)
	TEST(push_tail_cat)
	TEST(pop_head_int)
	TEST(pop_head_cat)
	TEST(pop_tail_int)
	TEST(pop_tail_cat)
	TEST(remove_not_exists_item_int)
	TEST(remove_not_exists_item_cat)
	TEST(remove_one_item_int)
	TEST(remove_one_item_cat)
	TEST(remove_first_item_int)
	TEST(remove_first_item_cat)
	TEST(remove_last_item_int)
	TEST(remove_last_item_cat)
	TEST(remove_all_items_int)
	TEST(remove_all_items_cat)
	TEST(merge)
	TEST(merge_int)
	TEST(merge_vector)
END_SUITE
