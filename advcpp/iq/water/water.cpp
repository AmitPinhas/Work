#include "mu_test.h"

#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <iterator> // distance , begin, end

using namespace std;

template <typename ForwardIter>
size_t Water(ForwardIter a_begin, ForwardIter a_end);

template <typename ForwardIter>
static void findNewBegin(ForwardIter& a_begin, ForwardIter a_end);

template <typename ForwardIter>
void startFillingWater(ForwardIter& a_begin, ForwardIter a_end, size_t& a_tmpWater);

UNIT(empty_container_vector)

    vector<unsigned int> v;

    size_t water = Water(v.begin(), v.end());

    ASSERT_EQUAL(water, 0);

END_UNIT

UNIT(one_elements_vector)

    vector<unsigned int> v{45};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 0);

END_UNIT

UNIT(two_elements_list)

    list<unsigned int> v{45, 654};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 0);

END_UNIT

UNIT(three_elements)

    vector<unsigned int> v{45, 10, 50};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 35);

END_UNIT

UNIT(ascending_order)

    vector<unsigned int> v{1, 2, 3, 4, 6, 10, 243, 500};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 0);

END_UNIT

UNIT(descending)

    vector<unsigned int> v{100000, 20000, 3000, 400, 60, 10, 2, 1};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 0);

END_UNIT

UNIT(same_elements)

    vector<unsigned int> v{543, 543, 543, 543, 543, 543, 543, 543};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 0);

END_UNIT

UNIT(odd_container_array)

    unsigned int a[] = {2, 543, 0, 543, 1543};

    size_t water = Water(begin(a), end(a));

    ASSERT_EQUAL(water, 543);

END_UNIT

UNIT(even_container_list)

    list<unsigned int> v{2, 543, 0, 543};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 543);

END_UNIT

UNIT(two_parts_fill_water_vector)

    vector<unsigned int> v{10, 2, 10, 20, 0, 30};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 28);

END_UNIT

UNIT(three_parts_fill_water_forward_list)

    forward_list<unsigned int> v{10, 2, 10, 20, 0, 30, 40, 60, 70, 100, 30, 100};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 98);

END_UNIT

UNIT(one_big_part_fill_water_deque)

    deque<unsigned int> v{100, 20, 10, 30, 300};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 240);

END_UNIT

UNIT(two_big_part_fill_water_list)

    list<unsigned int> v{100, 20, 10, 30, 300, 500, 100, 200, 100, 400, 600};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 1440);

END_UNIT

UNIT(three_big_part_fill_water)

    vector<unsigned int> v{100, 20, 10, 30, 300, 500, 100, 200, 100, 400, 600, 1000, 900, 940, 2000};

    size_t water = Water(v.begin(), v.end());;

    ASSERT_EQUAL(water, 1600);

END_UNIT

TEST_SUITE(water_tests)

    TEST(empty_container_vector)
    TEST(one_elements_vector)
    TEST(two_elements_list)   
    TEST(three_elements)
    TEST(ascending_order) 
    TEST(descending)
    TEST(same_elements)
    TEST(odd_container_array)
    TEST(even_container_list)
    TEST(two_parts_fill_water_vector)
    TEST(three_parts_fill_water_forward_list)
    TEST(one_big_part_fill_water_deque)
    TEST(two_big_part_fill_water_list)
    TEST(three_big_part_fill_water)

END_SUITE

template <typename ForwardIter>
size_t Water(ForwardIter a_begin, ForwardIter a_end)
{
    size_t water = 0;

    if(distance(a_begin, a_end) < 3)
    {
        return water;
    }

    while(a_begin != a_end)
    {
        findNewBegin(a_begin, a_end);

        if(a_begin == a_end)
        {
            break;
        }

        size_t tmpWater = 0;

        startFillingWater(a_begin, a_end, tmpWater);

        water+= tmpWater;
                
    }

    return water;
}

template <typename ForwardIter>
static void findNewBegin(ForwardIter& a_begin, ForwardIter a_end)
{
    while(a_begin != a_end)
    {
        auto first = a_begin;

        ++a_begin;

        if(a_begin == a_end)
        {
            break;
        }

        auto second = a_begin;

        if(*first > *second)
        {
            a_begin = first;
            break;
        }
    }
}

template <typename ForwardIter>
void startFillingWater(ForwardIter& a_begin, ForwardIter a_end, size_t& a_tmpWater)
{
    const unsigned int first = *a_begin;

    ++a_begin;

    unsigned int second = *a_begin;

    while(first > second)
    {
        a_tmpWater += first - second;

        ++a_begin;

        if(a_begin == a_end)
        {
            a_tmpWater = 0;
            break;
        }

        second = *a_begin;            
    }
}