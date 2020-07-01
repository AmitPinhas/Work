#include "mu_test.h"

#include <vector>
#include <algorithm> // std::transform

namespace advcpp
{

void SpreadMaxToLeft(std::vector<int>& a_vector);
class Spread;
class FirstBigger;

class FirstBigger
{
public:
	explicit FirstBigger(int a_num);
	
	// ~FirstBigger(); = default
	// FirstBigger(const FirstBigger& a_other); = default
	// FirstBigger& operator =(const FirstBigger& a_other); = default
	
	bool operator()(int a_num) const;
	
private:
	int m_num;		
		
};

FirstBigger::FirstBigger(int a_num)
: m_num(a_num)
{
}

bool FirstBigger::operator()(int a_num) const
{
	return m_num < a_num;
}


class Spread
{
public:
	explicit Spread(const std::vector<int>& a_vector);
	
	// ~Spread(); = default
	// Spread(const Spread& a_other); = default
	// Spread& operator =(const Spread& a_other); = default
	
	int operator()(int a_num);

private:
	static const int NOT_FOUND = -1;

private:
  const std::vector<int>& m_vector;
  size_t m_index;
  
};

Spread::Spread(const std::vector<int>& a_vector)
: m_vector(a_vector)
, m_index()
{
}

int Spread::operator()(int a_num) 
{
	std::vector<int>::const_iterator iter;
	
	++m_index;
	
	iter = find_if(m_vector.begin() + m_index, m_vector.end(), FirstBigger(a_num));
	
	if (iter != m_vector.end())
	{
		return *iter;
	}
	
	return NOT_FOUND;
}




void SpreadMaxToLeft(std::vector<int>& a_vector)
{	
	std::transform(a_vector.begin(),
	               a_vector.end(), 
	               a_vector.begin(),
	               Spread(a_vector));
}

} // namespace advcpp

UNIT(test_class)
	int arr[] = {2, 5, 8, 6, 10, 3};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {5, 8, 10, 10, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(all_small)
	int arr[] = {10, 9, 8, 7, 6, 5};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {-1, -1, -1, -1, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(all_big)
	int arr[] = {1, 2, 3, 4, 5, 6};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {2, 3, 4, 5, 6, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT



TEST_SUITE(test the spread max to left on fire)

	TEST(test_class)
	TEST(all_small)
	TEST(all_big)

END_SUITE


