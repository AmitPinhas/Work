#include "mu_test.h"

#include <iostream> // cout
#include "string.hpp"
#include "iq_string.hpp"


UNIT(constructor_print_size)
	advcpp::String<> myString("hello world");
	const char tmp[] = "hello world";
	
	ASSERT_EQUAL( myString.Size() , 11);
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], tmp[size]);
	}

END_UNIT

UNIT(copy_constructor)
	advcpp::String<> myString("hello world");
	advcpp::String<> secondString(myString);
    const char first[] = "bello world";
    const char second[] = "hello world";
	
	myString[0] = 'b' ;	
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], first[size]);
		ASSERT_EQUAL(secondString[size], second[size]);
	}
	
END_UNIT

UNIT(operator_subscript)
	advcpp::String<> myString("hello world");
	const char tmp[] = "bello world";	
	
	myString[0] = 'b' ;
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], tmp[size]);
	}
	
	ASSERT_EQUAL(myString[0], 'b');		

END_UNIT

UNIT(operator_basic_assignment)
	advcpp::String<> myString("hello world");
	advcpp::String<> secondString("second");
    const char first[] = "hello world";
    const char second[] = "second";	

	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], first[size]);
	}	
	
	size_t sizeSecond = secondString.Size();
	
	while(sizeSecond-- >0)
	{
		ASSERT_EQUAL(secondString[sizeSecond], second[sizeSecond]);
	}	
	
	secondString = myString;
	
	myString[0] = 'b' ;	
	
    const char firstt[] = "bello world";	
	
	size_t sizel = myString.Size();
	
	while(sizel-- >0)
	{
		ASSERT_EQUAL(myString[sizel], firstt[sizel]);
	}	
	
	size_t sizee = secondString.Size();
	
	while(sizee-- >0)
	{
		ASSERT_EQUAL(secondString[sizee], first[sizee]);
	}	
	
	ASSERT_PASS();

END_UNIT


UNIT(operator_addition_assignment)
	advcpp::String<> myString("hello world");
	const char tmp[] = "hello worldr";
	
	myString += 'r';
	
	ASSERT_EQUAL( myString.Size() , 12);
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], tmp[size]);
	}

END_UNIT

UNIT(operator_addition_letter)
	advcpp::String<> myString("hello world");
	advcpp::String<> test("test");
	const char tmp[] = "hello worldr";
	const char second[] = "hello world";
		
	test = myString + 'r';
	
	size_t size = test.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(test[size], tmp[size]);
	}
	
	size_t sizeSecond = myString.Size();
	
	while(sizeSecond-- >0)
	{
		ASSERT_EQUAL(myString[sizeSecond], second[sizeSecond]);
	}	
	
END_UNIT


UNIT(operator_addition_assignment_string)
	advcpp::String<> myString("hello world");
	advcpp::String<> tmp("hello world");	
	const char tmpCheck[] = "hello worldhello world";
	
	myString += tmp;
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], tmpCheck[size]);
	}

END_UNIT



UNIT(operator_addition_string)
	advcpp::String<> myString("hello world");
	advcpp::String<> tmp("hello world");
	advcpp::String<> test("lolololo");		
	const char tmpCheck[] = "hello worldhello world";
	
	test = myString + tmp;
	
	size_t size = test.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(test[size], tmpCheck[size]);
	}

END_UNIT

UNIT(operator_multiplication_assignment)
	advcpp::String<> myString("hello world");
	const char tmpCheck[] = "hello worldhello worldhello world";
	
//	myString *= 100;

	myString *= 3;
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], tmpCheck[size]);
	}

END_UNIT

UNIT(operator_equal_to)
	advcpp::String<> myString("hello world");
	advcpp::String<> second("hello world");
	advcpp::String<> third("helgo world");
		
	ASSERT_EQUAL( (myString == second) , true);
	ASSERT_EQUAL( (myString == third) , false);
	
END_UNIT

UNIT(operator_not_equal_to)
	advcpp::String<> myString("hello world");
	advcpp::String<> second("hello world");
	advcpp::String<> third("helgo world");
		
	ASSERT_EQUAL( (myString != second) , false);
	ASSERT_EQUAL( (myString != third) , true);
	
END_UNIT

UNIT(find)
	advcpp::String<> myString("hello world");	
	advcpp::String<> second("wor");	
	
	ASSERT_EQUAL( *(myString.Find(second)) , 'w');	
		
END_UNIT

UNIT(find_false)
	advcpp::String<> myString("hello world");	
	advcpp::String<> second("wgr");	
	
	ASSERT_EQUAL( myString.Find(second) , myString.End());	
			
END_UNIT

UNIT(operator_greater_than_true)
	advcpp::String<> myString("abdkhlg");	
	advcpp::String<> second("dkjgltkh");	

	ASSERT_EQUAL( (second > myString) , true);	

END_UNIT 

UNIT(operator_greater_than_false)
	advcpp::String<> myString("egrgerg");	
	advcpp::String<> second("drgrhtrhrt");	

	ASSERT_EQUAL( (second > myString) , false);	

END_UNIT 

UNIT(operator_less_then_true)

	advcpp::String<> myString("lalalab");	
	advcpp::String<> second("lalalad");	

	ASSERT_EQUAL( (myString < second) , true);	
	
END_UNIT

UNIT(operator_less_then_false)

	advcpp::String<> myString("lalala");	
	advcpp::String<> second("lalala");	

	ASSERT_EQUAL( (myString < second) , false);	
	
END_UNIT

UNIT(wchar)
	
	wchar_t wsKey[] = L"apple\n";
	wchar_t secondWs[] = L"bbbbpple\n";
	
	advcpp::String<wchar_t> myString(wsKey);	
	advcpp::String<wchar_t> second(secondWs);	

	ASSERT_EQUAL( (second < myString) , false);	
	
END_UNIT

UNIT(operator_equal_to_wchar)
	
	wchar_t wmyString[] = L"hello world\n";
	wchar_t wsecond[] = L"hello world\n";		
	wchar_t wthird[] = L"helgo world\n";
	
	advcpp::String<wchar_t> myString(wmyString);
	advcpp::String<wchar_t> second(wsecond);
	advcpp::String<wchar_t> third(wthird);
		
	ASSERT_EQUAL( (myString == second) , true);
	ASSERT_EQUAL( (myString == third) , false);
	
END_UNIT

UNIT(operator_addition_assignment_const_char_pointer)
	advcpp::String<> myString("hello world");
	const char tmpCheck[] = "hello worldhello world";
	
	myString += "hello world";
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], tmpCheck[size]);
	}

END_UNIT

UNIT(to_upper_char)
	advcpp::String<> myString("hello world");
	const char tmpCheck[] = "HELLO WORLD";
	
	myString.ToUpper();
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], tmpCheck[size]);
	}

END_UNIT

UNIT(to_upper_wchar)
	
	wchar_t wmyString[] = L"hello world\n";
	wchar_t wsecond[] = L"HELLO WORLD\n";		
	
	advcpp::String<wchar_t> myString(wmyString);
	advcpp::String<wchar_t> second(wsecond);

	myString.ToUpper();	
		
	ASSERT_EQUAL( (myString == second) , true);
	
END_UNIT

UNIT(to_lower_char)
	advcpp::String<> myString("HELLO WORLD");
	const char tmpCheck[] = "hello world";
	
	myString.ToLower();
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], tmpCheck[size]);
	}

END_UNIT

UNIT(to_lower_wchar)
	
	wchar_t wmyString[] = L"HELLO WORLD\n";
	wchar_t wsecond[] = L"hello world\n";		
	
	advcpp::String<wchar_t> myString(wmyString);
	advcpp::String<wchar_t> second(wsecond);

	myString.ToLower();	
		
	ASSERT_EQUAL( (myString == second) , true);
	
END_UNIT

UNIT(reverse_iterator_char)
	advcpp::String<> myString("hello world");
	const char tmpCheck[] = "hello world";	
	size_t index = 10;
	
	advcpp::String<char>::reverse_iterator begin = myString.RBegin();
	
	advcpp::String<char>::reverse_iterator end = myString.REnd();	
	
	while(begin != 	end)
	{
		ASSERT_THAT( *begin == tmpCheck[index] );
		--index;
		++begin;
	}

END_UNIT


UNIT(censor)
	advcpp::String<> myString("hello world");
	advcpp::String<> second("hl");	
	const char tmpCheck[] = "*e**o wor*d";	
	
	advcpp::Censor(myString, second, '*');
	
	size_t size = myString.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(myString[size], tmpCheck[size]);
	}	

END_UNIT

UNIT(only_first_and_second)
	advcpp::String<> first("abcdef");
	advcpp::String<> second("ecaxyf");	
	advcpp::String<> a_third("zgfd");	
	
	advcpp::String<> result = OnlyFirstAndSecond(first, second, a_third);
		
	const char tmpCheck[] = "ace";	
	
	size_t size = result.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(result[size], tmpCheck[size]);
	}	

END_UNIT

UNIT(unique)
	advcpp::String<> first("ffghpernlwiefhwgreoi");	
	
	char result = advcpp::Unique(first);
	
	ASSERT_EQUAL(result, 'p');

END_UNIT

UNIT(not_unique)
	advcpp::String<> first("qwerasdfgtiyuiop");	
	
	char result = advcpp::NotUnique(first);
	
	ASSERT_EQUAL(result, 'i');

END_UNIT

UNIT(cin)
	advcpp::String<> string;
	const char tmpCheck[] = "hello world";
	
	std::cin >> string;
	
	size_t size = string.Size();
	
	while(size-- >0)
	{
		ASSERT_EQUAL(string[size], tmpCheck[size]);
	}	

END_UNIT

TEST_SUITE(test the string on fire)

	TEST(constructor_print_size)
	TEST(copy_constructor)
	TEST(operator_subscript)
	TEST(operator_basic_assignment)
	TEST(operator_addition_assignment)
	TEST(operator_addition_letter)
	TEST(operator_addition_assignment_string)
	TEST(operator_addition_string)
	TEST(operator_multiplication_assignment)
	TEST(operator_equal_to)
	TEST(operator_not_equal_to)
	TEST(find)
	TEST(find_false)
	TEST(operator_greater_than_true)
	TEST(operator_greater_than_false)
	TEST(operator_less_then_true)
	TEST(operator_less_then_false)
	TEST(wchar)
	TEST(operator_equal_to_wchar)
	TEST(operator_addition_assignment_const_char_pointer)
	TEST(to_upper_char)
	TEST(to_upper_wchar)
	TEST(to_lower_char)
	TEST(to_lower_wchar)
	TEST(reverse_iterator_char)
	TEST(censor)
	TEST(only_first_and_second)
	TEST(unique)
	TEST(not_unique)
	IGNORE_TEST(cin)

END_SUITE
