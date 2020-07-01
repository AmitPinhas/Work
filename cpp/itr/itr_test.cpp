#include <vector>
#include <iterator>
#include "mu_test.h"
#include "itr.hpp"
#include "itr_test.hpp"

typedef std::vector<int>::iterator Iter;

UNIT(find_last_empty_list)
	
	std::vector<int> v;
    
    Iter it = FindLast( v.begin(), v.end(),  Pred<int>(rand()));
    
    ASSERT_THAT( it == v.end());

END_UNIT

UNIT(find_last_true)
	
	std::vector<int> v;
    const size_t N = 14;

    Fill(v, N, MakeSequence(1,3));
    
    Iter it = FindLast( v.begin(), v.end(),  Pred<int>(4));
    
    ASSERT_EQUAL( *it, 4);

END_UNIT


UNIT(find_last_false)
	
	std::vector<int> v;
    const size_t N = 14;

    Fill(v, N, MakeSequence(1));

    Iter it = FindLast( v.begin(), v.end(),  Pred<int>(5555));
    
    ASSERT_THAT( it == v.end());

END_UNIT

UNIT(find_last_same_value)
	
	std::vector<int> v;
    const size_t N = 14;

    Fill(v, N, MakeSequence(0,10));

    Iter it = FindLast( v.begin(), v.end(),  Pred<int>(10));
    
    ASSERT_EQUAL( *it, 10);
	ASSERT_EQUAL( Distance(v.begin(), it), 13);    

END_UNIT

UNIT(find_last_first_item)

	std::vector<int> v;
    const size_t N = 14;
	
	v.push_back(8);
	
    Fill(v, N, MakeSequence(0,10));

    Iter it = FindLast( v.begin(), v.end(),  Pred<int>(8));
    
    ASSERT_EQUAL( *it, 8);
	ASSERT_EQUAL( Distance(v.begin(), it), 0);        
    

END_UNIT

UNIT(find_last_last_item)

	std::vector<int> v;
    const size_t N = 14;
	
    Fill(v, N, MakeSequence(0,10));

	v.push_back(8);

    Iter it = FindLast( v.begin(), v.end(),  Pred<int>(8));
    
    ASSERT_EQUAL( *it, 8);
	ASSERT_EQUAL( Distance(v.begin(), it), 14);        
    

END_UNIT

UNIT(distance_first)
	
	std::vector<int> v;
    const size_t N = 14;

    Fill(v, N, MakeSequence(1));	

    Iter it = FindLast( v.begin(), v.end(),  Pred<int>(0));
    
    ASSERT_EQUAL( Distance(v.begin(), it), 0);

END_UNIT

UNIT(distance_last)
	
	std::vector<int> v;
    const size_t N = 14;

    Fill(v, N, MakeSequence(1));	

    Iter it = FindLast( v.begin(), v.end(),  Pred<int>(13));
    
    ASSERT_EQUAL( Distance(v.begin(), it), 13);

END_UNIT

UNIT(distance_mid)
	
	std::vector<int> v;
    const size_t N = 14;

    Fill(v, N, MakeSequence(1));	

    Iter it = FindLast( v.begin(), v.end(),  Pred<int>(7));
    
    ASSERT_EQUAL( Distance(v.begin(), it), 7);

END_UNIT

UNIT(bubble_sort)
	
	std::vector<int> v;
    const size_t N = 20;

    FillRandom(v, N);	
	
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == false);	

    BubbleSort(v.begin(), v.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	

END_UNIT

UNIT(bubble_sort_empty_vector)
	
	std::vector<int> v;

    BubbleSort(v.begin(), v.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	

END_UNIT


UNIT(bubble_sort_one_item)
	
	std::vector<int> v;

	v.push_back(2);

    BubbleSort(v.begin(), v.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	

END_UNIT

UNIT(bubble_sort_already_sort)
	
	std::vector<int> v;
    const size_t N = 14;

    Fill(v, N, MakeSequence(1));
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);    

    BubbleSort(v.begin(), v.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	

END_UNIT

UNIT(bubble_sort_big_vector)
	
	std::vector<int> v;
    const size_t N = 10000;

    FillRandom(v, N);
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == false);    

    BubbleSort(v.begin(), v.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	

END_UNIT

UNIT(bubble_sort_same_items)
	
	std::vector<int> v;
    const size_t N = 10000;

    Fill(v, N, MakeSequence(0,10));
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);    

    BubbleSort(v.begin(), v.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	

END_UNIT

UNIT(merge_sort)
	
	std::vector<int> v, d;
    const size_t N = 20;

    Fill(v, N, MakeSequence(1));
    Fill(d, 10, MakeSequence(1));
	
	std::vector<int> tmp = d;
	
	Iter it = FindLast( v.begin(), v.end(),  Pred<int>(10));

    Merge(v.begin(), it, v.end(), d.begin(), d.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	
    ASSERT_THAT(tmp == d); 

END_UNIT

UNIT(merge_sort_empty_a)
	
	std::vector<int> v, d;

    Fill(d, 10, MakeSequence(1));
	
	Iter it = FindLast( v.begin(), v.end(),  Pred<int>(10));

    Merge(v.begin(), it, v.end(), d.begin(), d.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	

END_UNIT

UNIT(merge_sort_empty_b)
	
	std::vector<int> v, d;

    Fill(v, 10, MakeSequence(1));
	
	Iter it = FindLast( v.begin(), v.end(),  Pred<int>(10));

    Merge(v.begin(), it, v.end(), d.begin(), d.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	

END_UNIT

UNIT(merge_sort_all_b)
	
	std::vector<int> v, d;

    Fill(v, 10, MakeSequence(0));
	Fill(d, 10, MakeSequence(1));

    Merge(v.begin(), v.begin(), v.end(), d.begin(), d.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);
	ASSERT_THAT(v == d);

END_UNIT

UNIT(merge_sort_big_b)
	
	std::vector<int> v, d;
    const size_t N = 20;

    Fill(v, N, MakeSequence(1));
    Fill(d, 10, MakeSequence(1,100));
	
	std::vector<int> tmp = d;
	
	Iter it = FindLast( v.begin(), v.end(),  Pred<int>(10));

    Merge(v.begin(), it, v.end(), d.begin(), d.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	
    ASSERT_THAT(tmp == d); 

END_UNIT

UNIT(merge_sort_big_a)
	
	std::vector<int> v, d;
    const size_t N = 20;

    Fill(v, N, MakeSequence(1,100));
    Fill(d, 10, MakeSequence(1));
	
	std::vector<int> tmp = d;
	
	Iter it = FindLast( v.begin(), v.end(),  Pred<int>(10));

    Merge(v.begin(), it, v.end(), d.begin(), d.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	
    ASSERT_THAT(tmp == d); 

END_UNIT

UNIT(merge_sort_different_size)
	
	std::vector<int> v, d;
    const size_t N = 30;

    Fill(v, N, MakeSequence(1,100));
    Fill(d, 10, MakeSequence(1));
	
	std::vector<int> tmp = v;
	
	Iter it = FindLast( v.begin(), v.end(),  Pred<int>(10));

    Merge(v.begin(), it, v.end(), d.begin(), d.end());
    
    ASSERT_THAT(MinToMax(v.begin(), v.end()) == true);	
    ASSERT_THAT(v == tmp); 

END_UNIT


TEST_SUITE(test the itr on fire)

	TEST(find_last_empty_list)
	TEST(find_last_true)
	TEST(find_last_false)
	TEST(find_last_same_value)
	TEST(find_last_first_item)
	TEST(find_last_last_item)
	TEST(distance_first)
	TEST(distance_last)
	TEST(distance_mid)
	TEST(bubble_sort)
	TEST(bubble_sort_empty_vector)
	TEST(bubble_sort_one_item)
	TEST(bubble_sort_already_sort)
	TEST(bubble_sort_big_vector)
	TEST(bubble_sort_same_items)
	TEST(merge_sort)
	TEST(merge_sort_empty_a)
	TEST(merge_sort_empty_b)
	TEST(merge_sort_all_b)
	TEST(merge_sort_big_b)
	TEST(merge_sort_big_a)
	TEST(merge_sort_different_size)

END_SUITE
