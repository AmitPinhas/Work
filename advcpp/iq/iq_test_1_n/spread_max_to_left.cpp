#include "mu_test.h"

#include <vector>
#include <algorithm> // std::transform
#include <utility> // std::pair

namespace advcpp
{

typedef std::vector<std::pair<int, int> > VectorOfPairs;
typedef std::vector<int> VectorInt;

void SpreadMaxToLeft(VectorInt& a_vector);

VectorOfPairs FillVecPair(const VectorInt& a_vector);

void CopyResult(VectorOfPairs a_vecPair,
                VectorInt& a_vector);
                
size_t FindIndexMax(VectorOfPairs::reverse_iterator a_rBegin, 
                    VectorInt& a_vector,
                    VectorOfPairs a_vecPair);

void SpreadMaxToLeft(VectorInt& a_vector)
{	
	if(a_vector.empty())
	{
		return;
	} 	
		
	VectorOfPairs vecPair = FillVecPair(a_vector);

	VectorOfPairs::reverse_iterator rBegin = vecPair.rbegin();
	VectorOfPairs::reverse_iterator rEnd = vecPair.rend();	
	size_t index = a_vector.size() - 1;
	
	while(++rBegin != rEnd)
	{
		--index;
		
		if(rBegin->first < (rBegin - 1)->first)
		{
			rBegin->second = index + 1;
		}
		else if( (rBegin-1)->second == -1)
		{
			rBegin->second = -1;
		}
		else 
		{
			rBegin->second = FindIndexMax(rBegin, a_vector, vecPair);
		}	
	}
	
	CopyResult(vecPair, a_vector);
	
}

size_t FindIndexMax(VectorOfPairs::reverse_iterator a_rBegin, 
                    VectorInt& a_vector,
                    VectorOfPairs a_vecPair)
{
	int indexTmp = (a_rBegin-1)->second;
			
	while(indexTmp != -1 && a_vector[indexTmp] <= a_rBegin->first)
	{
		indexTmp = a_vecPair[indexTmp].second;
	}
			
	return indexTmp;	
}                    


VectorOfPairs FillVecPair(const VectorInt& a_vector)
{
	VectorOfPairs vecPair;
	
	size_t sizeVec = a_vector.size();
	
	for (size_t index = 0; index < sizeVec; ++index)
	{
		std::pair<int, int> pair;
		
		pair.first = a_vector[index];
		
		pair.second = -1;
		
		vecPair.push_back(pair);
	}
	
	return vecPair;
}

void CopyResult(VectorOfPairs a_vecPair, VectorInt& a_vector)
{
	size_t index = a_vector.size();
	
	while (index-- >0)
	{
		if (a_vecPair[index].second == -1)
		{
			a_vector[index] = -1;
		}
		else
		{
			size_t tmpIndex = a_vecPair[index].second;
			
			a_vector[index] = a_vecPair[tmpIndex].first;
		}
		
	}
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


UNIT(only_one_item)
	int arr[] = {778};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {-1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(same_value)
	int arr[] = {343, 343, 343, 343, 343, 343};
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


UNIT(all_negative_number)
	int arr[] = {-3, -43, -536, -36, -9, -5456};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {-1, -36, -36, -9, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(negative_and_positive)
	int arr[] = {3, 43, -536, -36, 9, -5456};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {43, -1, -36, 9, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(first_max)
	int arr[] = {78678, 43, 785, 34, 9, -5456};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {-1, 785, -1, -1, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(last_max)
	int arr[] = {-54, 43, 785, 34, 9, 78678};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {43, 785, 78678, 78678, 78678, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(mid_max)
	int arr[] = {-54, 43, 78678, 34, 9, 7};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {43, 78678, -1, -1, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT

UNIT(first_min)
	int arr[] = {-78678, 43, 785, 34, 9, -5456};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {43, 785, -1, -1, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(last_min)
	int arr[] = {-54, 43, 785, 34, 9, -78678};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {43, 785, -1, -1, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(mid_min)
	int arr[] = {-54, 43, -78678, 34, 9, 7};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {43, -1, 34, -1, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(empty_vector)

	std::vector<int> vector;
	
	advcpp::SpreadMaxToLeft(vector);
	
	ASSERT_PASS();

END_UNIT


UNIT(max_first_rest_same_value)
	int arr[] = {100, 5, 5, 5, 5, 5};
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


UNIT(big_vector)
	int arr[] = {12, 543, 2, 6547, -76, 4326, -543, -9, 652, 23, 68, -87, 7, 754, 9};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {543, 6547, 6547, -1, 4326, -1, -9, 652, 754, 68, 754, 7, 754, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT

UNIT(min_first_rest_same_value)
	int arr[] = {2, 5, 5, 5, 5, 5};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {5, -1, -1, -1, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(max_mid_rest_same_value)
	int arr[] = {5, 5, 5, 100, 5, 5, 5};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {100, 100, 100, -1, -1, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);	
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(min_mid_rest_same_value)
	int arr[] = {5, 5, 5, -100, 5, 5, 5};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {-1, -1, -1, 5, -1, -1, -1};
	
	advcpp::SpreadMaxToLeft(vector);	
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(max_last_rest_same_value)
	int arr[] = {5, 5, 5, 5, 5, 5, 100};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {100, 100, 100, 100, 100, 100, -1};
	
	advcpp::SpreadMaxToLeft(vector);	
	
	size_t index = sizeArr;
	
	while(index-- >0)
	{
		ASSERT_THAT(vector[index] == result[index]);
	}	

END_UNIT


UNIT(min_last_rest_same_value)
	int arr[] = {5, 5, 5, 5, 5, 5, -100};
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]) ;	
	std::vector<int> vector(arr, arr + sizeArr);
	int result[] = {-1, -1, -1, -1, -1, -1, -1};
	
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
	TEST(only_one_item)
	TEST(same_value)
	TEST(all_negative_number)
	TEST(negative_and_positive)
	TEST(empty_vector)
	TEST(first_max)
	TEST(last_max)
	TEST(mid_max)
	TEST(first_min)
	TEST(last_min)
	TEST(mid_min)
	TEST(big_vector)
	TEST(max_first_rest_same_value)
	TEST(min_first_rest_same_value)
	TEST(max_mid_rest_same_value)
	TEST(min_mid_rest_same_value)
	TEST(max_last_rest_same_value)
	TEST(min_last_rest_same_value)

END_SUITE


