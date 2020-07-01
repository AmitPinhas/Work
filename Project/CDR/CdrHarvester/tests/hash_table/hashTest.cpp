#include <cstdlib>// atoi


#include "mu_test.h"
#include "hash_table.hpp"
#include "cat.hpp"



static const int Base = 10;
typedef advcpp::HashTable<std::string, Cat, unsigned int (*)(std::string const& a_key) > MyHush;
typedef advcpp::HashTable<std::string, int, unsigned int (*)(std::string const& a_key) > MyIntHush;



unsigned int HashFunc(std::string const& a_key)
{
	size_t result = 0;
	for(size_t i = 0; i < a_key.length(); i++)
    {
        result = result * Base + a_key[i];
    }
	return result; 
}

void ForEachFunc(int& a_num)
{
	++a_num;
}


UNIT(test_hash_insert_find)
	Cat catA(4, 5, "sergey");
	Cat catB(6, 7, "yuval");

	MyHush h(100, 10, HashFunc);
	h.Insert("myFirstCat", catA);


	advcpp::Iterator<std::string, Cat> it = h.Find("myFirstCat");
	ASSERT_THAT( (*it).second == catA);
END_UNIT


UNIT(test_squere_brecets_operator)
	Cat catA(4, 5, "sergey");
	Cat catB(6, 7, "yuval");

	MyHush h(100, 100, HashFunc);
	h["myFirstCat"] =  catA;

	advcpp::Iterator<std::string, Cat> it = h.Find("myFirstCat");
	ASSERT_THAT( (*it).second == catA);

	h["myFirstCat"] = catB;

	it = h.Find("myFirstCat");
	ASSERT_THAT( (*it).second == catB);
END_UNIT


UNIT(test_size)
	Cat catA(4, 5, "sergey");
	Cat catB(6, 7, "yuval");
	Cat catC(4, 5, "alex");
	Cat catD(6, 7, "putin");
	Cat catE(4, 5, "ariel");
	Cat catF(6, 7, "alon");

	MyHush h(100, 100, HashFunc);


	ASSERT_EQUAL(h.Size(), 0);
	h.Insert("1", catA);
	ASSERT_EQUAL(h.Size(), 1);
	h["2"] =  catB;
	ASSERT_EQUAL(h.Size(), 2);
	h.Insert("myFirstCat", catC);
	ASSERT_EQUAL(h.Size(), 3);
	h.Insert("myFirstCat", catA);
	ASSERT_EQUAL(h.Size(), 3);
	h.Insert("4", catD);
	ASSERT_EQUAL(h.Size(), 4);
	h.Remove("1", catE);
	ASSERT_EQUAL(h.Size(), 3);
	h.Clear();
	ASSERT_EQUAL(h.Size(), 0);
END_UNIT

UNIT(test_re_size)
	Cat catA(4, 5, "sergey");
	Cat catB(6, 7, "yuval");

	MyHush h(1001, 100, HashFunc);
	h["myFirstCat"] =  catA;
	h.Insert("mySecondCat", catB);

	ASSERT_EQUAL(h.Capacity(), 1009);

	h.ReSize(2003);

	advcpp::Iterator<std::string, Cat> it = h.Find("myFirstCat");
	ASSERT_THAT( (*it).second == catA);


	it = h.Find("mySecondCat");
	ASSERT_THAT( (*it).second == catB);	
END_UNIT

UNIT(test_swap)
	MyHush h(1001, 100, HashFunc);
	MyHush h2(502, 100, HashFunc);

	Cat catA(4, 5, "sergey");
	Cat catB(6, 7, "yuval");
	Cat catC(4, 5, "alex");
	Cat catD(6, 7, "putin");
	Cat catE(4, 5, "ariel");
	Cat catF(6, 7, "alon");
	
	h.Insert("1" , catA);
	h.Insert("2" , catB);
	h.Insert("3" , catC);
	h2.Insert("1" , catD);
	h2.Insert("2" , catE);
	h2.Insert("3" , catF);

	ASSERT_EQUAL(h.Capacity(), 1009);
	ASSERT_EQUAL(h2.Capacity(), 503);

	h.Swap(h2);
	
	ASSERT_EQUAL(h2.Capacity(), 1009);
	ASSERT_EQUAL(h.Capacity(), 503);

	ASSERT_THAT((* h.Find("1") ).second == catD);
	ASSERT_THAT((* h.Find("2") ).second == catE);
	ASSERT_THAT((* h.Find("3") ).second == catF);
	ASSERT_THAT((* h2.Find("1") ).second == catA);
	ASSERT_THAT((* h2.Find("2") ).second == catB);
	ASSERT_THAT((* h2.Find("3") ).second == catC);
END_UNIT

UNIT(test_prime)
	size_t num = myMath::GetNextPrime(1);
	ASSERT_EQUAL(num, 2);

	num = myMath::GetNextPrime(1000);
	ASSERT_EQUAL(num, 1009);

	num = myMath::GetNextPrime(1009);
	ASSERT_EQUAL(num, 1009);

END_UNIT


UNIT(for_each)
	MyIntHush h(50, 10, HashFunc);
	h.Insert("a", 1);
	h.Insert("b", 2);
	h.Insert("c", 3);
	h.Insert("d", 4);

	h.ForEach(ForEachFunc);

	advcpp::Iterator<std::string, int> it = h.Find("a");
	ASSERT_THAT( (*it).second == 2);

	it = h.Find("b");
	ASSERT_THAT( (*it).second == 3);

	it = h.Find("c");
	ASSERT_THAT( (*it).second == 4);

	it = h.Find("d");
	ASSERT_THAT( (*it).second == 5);

END_UNIT




TEST_SUITE(hash table tests)
	TEST(test_hash_insert_find)
	TEST(test_size)
	TEST(test_squere_brecets_operator)
	TEST(test_re_size)
	TEST(test_swap)
	TEST(test_prime)
	TEST(for_each)
END_SUITE




