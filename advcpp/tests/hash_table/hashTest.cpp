#include "mu_test.h"

#include "hash_table.hpp"
#include "my_iter.hpp"

typedef size_t (*MyHash)(size_t a_num);

size_t HashFunc(size_t a_num)
{
	return a_num;
}

UNIT(first_insert)
	size_t capacity = 50;
	
	advcpp::HashTable<size_t, size_t, MyHash> tmp(capacity, HashFunc);
	
	size_t key = 3;
	size_t value = 46;
	
	advcpp::MyIter<size_t , size_t> iter = tmp.Insert(key, value);
//	advcpp::HashTable<size_t, size_t, MyHash>::iterator iter = tmp.Insert(key, value);
	
	ASSERT_THAT((*iter).First() == key);
	ASSERT_THAT((*iter).Second() == value);

END_UNIT


UNIT(find_true)
	size_t capacity = 50;
	
	advcpp::HashTable<size_t, size_t, MyHash> tmp(capacity, HashFunc);
	
	size_t key = 7;
	size_t value = 46;
	
    tmp.Insert(key, value);
	
	advcpp::MyIter<size_t , size_t> iter = tmp.Find(key);
	
	ASSERT_THAT((*iter).First() == key);
	ASSERT_THAT((*iter).Second() == value);	

END_UNIT

UNIT(find_const)
	size_t capacity = 50;
	
	advcpp::HashTable<size_t, size_t, MyHash> tmp(capacity, HashFunc);
	
	size_t key = 7;
	size_t value = 46;
	
    tmp.Insert(key, value);
	
	advcpp::MyIter<size_t , size_t> iter = tmp.Find(key);
	
	ASSERT_THAT((*iter).First() == key);
	ASSERT_THAT((*iter).Second() == value);	

END_UNIT
/*
UNIT(find_flase)
	size_t capacity = 50;
	
	advcpp::HashTable<size_t, size_t, MyHash> tmp(capacity, HashFunc);
	
	size_t key = 47;
	
	advcpp::MyIter<size_t , size_t> iter = tmp.Find(key);
	
//	ASSERT_THAT(iter == tmp.End());

	ASSERT_PASS();

END_UNIT
*/

UNIT(remove_true)
	size_t capacity = 50;
	
	advcpp::HashTable<size_t, size_t, MyHash> tmp(capacity, HashFunc);
	
	size_t key = 76;
	size_t value = 46;
	size_t keyReturn = 0;
	
	tmp.Insert(key, value);
	
	ASSERT_THAT( tmp.Size() == 1);
	
	ASSERT_THAT(tmp.Remove(key,keyReturn) == true);
	
	ASSERT_THAT( tmp.Size() == 0);
		
	ASSERT_THAT(keyReturn == value);

END_UNIT

UNIT(remove_false)
	size_t capacity = 50;
	
	advcpp::HashTable<size_t, size_t, MyHash> tmp(capacity, HashFunc);
	
	size_t key = 76;
	size_t value = 46;
	size_t keyReturn = 0;
	
	tmp.Insert(key, value);
	
	ASSERT_THAT( tmp.Size() == 1);
	
	ASSERT_THAT(tmp.Remove(78678,keyReturn) == false);
	
	ASSERT_THAT( tmp.Size() == 1);
		
	ASSERT_THAT(keyReturn == 0);

END_UNIT

UNIT(operator_subscript)
	size_t capacity = 50;
	
	advcpp::HashTable<size_t, size_t, MyHash> tmp(capacity, HashFunc);
	
	size_t key = 3;
	size_t value = 46;
	
    tmp.Insert(key, value);
	
	ASSERT_EQUAL( tmp[key], value);

END_UNIT

UNIT(operator_subscript_insert)
	size_t capacity = 50;
	
	advcpp::HashTable<size_t, size_t, MyHash> tmp(capacity, HashFunc);
	
	size_t key = 7;
	size_t value = 46;
	
    tmp[key] = value;
	
	advcpp::MyIter<size_t , size_t> iter = tmp.Find(key);
	
	ASSERT_THAT((*iter).First() == key);
	ASSERT_THAT((*iter).Second() == value);

END_UNIT


UNIT(resize)
	size_t capacity = 10;
	
	advcpp::HashTable<size_t, size_t, MyHash> tmp(capacity, HashFunc);
	
	size_t key = 10;

	while (key-- > 0)
	{
		tmp[key] = key;
	}	

	tmp.Resize(20);
	
	ASSERT_THAT(tmp.Capacity() >= 20);
	
	size_t secondKey = 10;
	
	while (secondKey-- > 0)
	{	
		advcpp::MyIter<size_t , size_t> iter = tmp.Find(secondKey);

		ASSERT_THAT((*iter).First() == secondKey);
		ASSERT_THAT((*iter).Second() == secondKey);	
	}
	
	
	size_t newKey = 110;
	
	while(newKey-- > 100)
	{
		tmp.Insert(newKey, newKey);
	}
	
	size_t findKey = 110;
	
	while(findKey-- > 100)
	{
		advcpp::MyIter<size_t , size_t> iter = tmp.Find(findKey);

		ASSERT_THAT((*iter).First() == findKey);
		ASSERT_THAT((*iter).Second() == findKey);	
	}	
	
	
	

END_UNIT

TEST_SUITE(test the hash table on fire)

	TEST(first_insert)
	TEST(find_true)
	TEST(find_const)
//	TEST(find_flase)
	TEST(remove_true)
	TEST(remove_false)
	TEST(operator_subscript)
	TEST(operator_subscript_insert)
	TEST(resize)

END_SUITE
