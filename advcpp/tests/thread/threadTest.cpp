#include "mu_test.h"

#include <cstdlib>     // srand, rand 
#include <ctime>       // time 
#include <iostream>    // std::cout
#include <vector>
#include "utils.hpp"

template <typename T>
class Generator
{
public:
	T operator()() const;
	
};

template <typename T>
T Generator<T>::operator()() const
{
	return rand() % 200 + (-100) ;
}

UNIT(fill_vector)
    srand (time(NULL));
	std::vector<int> vector;
	Generator<int> generator;
	
	advcpp::FillVector<int, Generator<int> >(vector, 20, generator);
	
	size_t index = 20;
	
	while(index-- >0)
	{
		std::cout << vector[index] << ' ';
	}
	std::cout << '\n';
	
	ASSERT_PASS();

END_UNIT

TEST_SUITE(test the thread on fire)

	TEST(fill_vector)

END_SUITE
