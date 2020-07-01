#include "mu_test.h"

#include <optional>
#include <vector>
#include <stack>

using namespace std;

static void updateMaxMin(int& a_max, int&  a_min, int a_first, int a_second);

static void updateMax(int& a_max, int a_candidate);

static void updateMin(int& a_min, int a_candidate);

static bool isOdd(size_t a_size);

optional<pair<int,int>> MinMax(vector<int> const& a_vector);

template <typename ForwardIter>
optional<pair<ForwardIter, ForwardIter>> MinMax(ForwardIter a_begin, ForwardIter a_end);

template <typename C>
optional<pair<typename C::iterator, typename C::iterator>> MinMax(C const& a_c);

template <typename ForwardIter>
void checkLastElement(ForwardIter a_first, ForwardIter& a_maxIter, ForwardIter& a_minIter);

template <typename ForwardIter>
void checkElements(ForwardIter a_first, ForwardIter a_second, ForwardIter& a_maxIter, ForwardIter& a_minIter);

template <typename ForwardIter>
void checkMax(ForwardIter& a_maxIter, ForwardIter& maxCandidateIter);

template <typename ForwardIter>
void checkMin(ForwardIter& a_minIter, ForwardIter& minCandidateIter);

UNIT(empty_vector)

    vector<int> v;
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(!r){
        ASSERT_PASS();
    }
    else
    {
        ASSERT_FAIL("empty_vector");
    }
    

END_UNIT

UNIT(one_item)

    vector<int> v{56};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, 56);
        ASSERT_EQUAL(*r->second, 56);
    }
    else
    {
        ASSERT_FAIL("one_item");
    }
    

END_UNIT

UNIT(odd_vector)

    vector<int> v{-543, 435, 0, 4745, -23, 7453, 54};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, -543);
        ASSERT_EQUAL(*r->second, 7453);
    }
    else
    {
        ASSERT_FAIL("odd_vector");        
    }
    
END_UNIT

UNIT(even_vector)

    vector<int> v{-543, 435, 0, 4745, -23, 7453, 54, -3};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, -543);
        ASSERT_EQUAL(*r->second, 7453);
    }
    else
    {
        ASSERT_FAIL("even_vector");        
    }
    
END_UNIT

UNIT(same_item)

    vector<int> v{435, 435, 435, 435, 435, 435, 435, 435};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, 435);
        ASSERT_EQUAL(*r->second, 435);
    }
    else
    {
        ASSERT_FAIL("same_item");        
    }
    
END_UNIT

UNIT(small_to_big)

    vector<int> v{-435, -43, -4, 0, 435, 4355, 44535, 4343435};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, -435);
        ASSERT_EQUAL(*r->second, 4343435);
    }
    else
    {
        ASSERT_FAIL("small_to_big");        
    }
    
END_UNIT

UNIT(big_to_small)

    vector<int> v{435, 43, 4, 0, -435, -4355, -44535, -4343435};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, -4343435);
        ASSERT_EQUAL(*r->second, 435);
    }
    else
    {
        ASSERT_FAIL("big_to_small");        
    }
    
END_UNIT

UNIT(big_test)

    vector<int> v{54535, 43, 4, 0, -4435, -145435, -7445435, -4343435,
                  64435, 743435, 34, 0, -3435, -14355, -944535, -84343435,
                  4335, 43, 4, 10, -435, -4355, -644535, -654343435,
                  64325, 843, 4, 1000000000, -1435, -4355, -944535, -4343435,
                  4435, 4543, 34, 0, -3435, -54355, -144535, -4343435,
                  6435, 743, 44, 40, -435, -94355, -1000000000, -4343435,
                  4135, 743, 84, 50, -1435, -4355, -44535, -84343435};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, -1000000000);
        ASSERT_EQUAL(*r->second, 1000000000);
    }
    else
    {
        ASSERT_FAIL("big_test");        
    }
    
END_UNIT

UNIT(big_test_min_last_item)

    vector<int> v{54535, 43, 4, 0, -4435, -145435, -7445435, -4343435,
                  64435, 743435, 34, 0, -3435, -14355, -944535, -84343435,
                  4335, 43, 4, 10, -435, -4355, -644535, -654343435,
                  64325, 843, 4, 1000000000, -1435, -4355, -944535, -4343435,
                  4435, 4543, 34, 0, -3435, -54355, -144535, -4343435,
                  6435, 743, 44, 40, -435, -94355, -84343435, -4343435,
                  4135, 743, 84, 50, -1435, -4355, -44535, -1000000000};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, -1000000000);
        ASSERT_EQUAL(*r->second, 1000000000);
    }
    else
    {
        ASSERT_FAIL("big_test");        
    }
    
END_UNIT

UNIT(big_test_min_first_item)

    vector<int> v{-1000000000, 43, 4, 0, -4435, -145435, -7445435, -4343435,
                  64435, 743435, 34, 0, -3435, -14355, -944535, -84343435,
                  4335, 43, 4, 10, -435, -4355, -644535, -654343435,
                  64325, 843, 4, 1000000000, -1435, -4355, -944535, -4343435,
                  4435, 4543, 34, 0, -3435, -54355, -144535, -4343435,
                  6435, 743, 44, 40, -435, -94355, -84343435, -4343435,
                  4135, 743, 84, 50, -1435, -4355, -44535, 54535};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, -1000000000);
        ASSERT_EQUAL(*r->second, 1000000000);
    }
    else
    {
        ASSERT_FAIL("big_test");        
    }
    
END_UNIT

UNIT(big_test_max_last_item)

    vector<int> v{54535, 43, 4, 0, -4435, -145435, -7445435, -4343435,
                  64435, 743435, 34, 0, -3435, -14355, -944535, -84343435,
                  4335, 43, 4, 10, -435, -4355, -644535, -654343435,
                  64325, 843, 4, -1000000000, -1435, -4355, -944535, -4343435,
                  4435, 4543, 34, 0, -3435, -54355, -144535, -4343435,
                  6435, 743, 44, 40, -435, -94355, -84343435, -4343435,
                  4135, 743, 84, 50, -1435, -4355, -44535, 1000000000};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, -1000000000);
        ASSERT_EQUAL(*r->second, 1000000000);
    }
    else
    {
        ASSERT_FAIL("big_test");        
    }
    
END_UNIT

UNIT(big_test_max_first_item)

    vector<int> v{1000000000, 43, 4, 0, -4435, -145435, -7445435, -4343435,
                  64435, 743435, 34, 0, -3435, -14355, -944535, -84343435,
                  4335, 43, 4, 10, -435, -4355, -644535, -654343435,
                  64325, 843, 4, -1000000000, -1435, -4355, -944535, -4343435,
                  4435, 4543, 34, 0, -3435, -54355, -144535, -4343435,
                  6435, 743, 44, 40, -435, -94355, -84343435, -4343435,
                  4135, 743, 84, 50, -1435, -4355, -44535, 54535};
   // auto r = MinMax(v);
   auto r = MinMax(v.begin(), v.end());
    if(r){
        ASSERT_EQUAL(*r->first, -1000000000);
        ASSERT_EQUAL(*r->second, 1000000000);
    }
    else
    {
        ASSERT_FAIL("big_test");        
    }
    
END_UNIT

TEST_SUITE(iq_test_min_max)

    TEST(empty_vector)
    TEST(one_item)
    TEST(odd_vector)
    TEST(even_vector)    
    TEST(same_item)
    TEST(small_to_big)
    TEST(big_to_small)
    TEST(big_test)
    TEST(big_test_min_last_item)
    TEST(big_test_min_first_item)   
    TEST(big_test_max_last_item) 
    TEST(big_test_max_first_item)

END_SUITE

optional<pair<int,int>> MinMax(vector<int> const& a_vector){

    if(a_vector.size() == 0)
    {
       return nullopt; 
    }

    const size_t indexLastItem = a_vector.size() - 1;

    const int lastItem = a_vector[indexLastItem];

    int max = lastItem;
    int min = lastItem;

    auto end = a_vector.end();

    if(isOdd(a_vector.size()))
    {
        --end;  
    }    

    for(auto begin = a_vector.begin(); begin + 1 < end; begin += 2)
    {
        const int first = *begin;
        const int second = *(begin + 1);

        updateMaxMin(max, min, first, second);
    }

    return make_pair(min, max);
}

static void updateMaxMin(int& a_max, int&  a_min, int a_first, int a_second)
{
    int maxCandidate;
    int minCandidate;

    if(a_first > a_second)
    {
        maxCandidate = a_first;
        minCandidate = a_second;
    }
    else
    {
        maxCandidate = a_second;
        minCandidate = a_first;
    }   

    updateMax(a_max, maxCandidate);
    updateMin(a_min, minCandidate); 
}

static void updateMax(int& a_max, int a_candidate)
{
    if(a_candidate > a_max)
    {
        a_max = a_candidate;
    }    
}

static void updateMin(int& a_min, int a_candidate)
{
    if(a_candidate < a_min)
    {
        a_min = a_candidate;
    }    
}

static bool isOdd(size_t a_size)
{
    return a_size % 2;
}

template <typename ForwardIter>
optional<pair<ForwardIter, ForwardIter>> MinMax(ForwardIter a_begin, ForwardIter a_end)
{
    if(a_begin == a_end)
    {
        return nullopt;
    }
    auto maxIter = a_begin;
    auto minIter = a_begin;
    
    if(++a_begin == a_end)
    {
        return make_pair(minIter, maxIter);
    }

    while(a_begin != a_end)
    {
        auto first = a_begin;
        ++a_begin;
        if(a_begin == a_end)
        {
            checkLastElement(first, maxIter, minIter);         
            break;
        }
        auto second = a_begin;   
        checkElements(first, second, maxIter, minIter);
        ++a_begin;
    }
    return make_pair(minIter, maxIter);
}

template <typename C>
optional<pair<typename C::iterator, typename C::iterator>> MinMax(C const& a_c)
{
   auto r = MinMax(a_c.begin(), a_c.end());
   return make_pair(r->first, r->second);
}

template <typename ForwardIter>
void checkLastElement(ForwardIter a_first, ForwardIter& a_maxIter, ForwardIter& a_minIter)
{
    if(!(*a_first < *a_maxIter))
    {
        a_maxIter = a_first;
    }
    else if(*a_first < *a_minIter)
    {
        a_minIter = a_first;
    }          
}

template <typename ForwardIter>
void checkElements(ForwardIter a_first, ForwardIter a_second, ForwardIter& a_maxIter, ForwardIter& a_minIter)
{
    ForwardIter maxCandidateIter;
    ForwardIter minCandidateIter;

    if(*a_first > *a_second)
    {
        maxCandidateIter = a_first;
        minCandidateIter = a_second;
    }   
    else
    {
        maxCandidateIter = a_second;
        minCandidateIter = a_first;           
    }

    checkMax(a_maxIter, maxCandidateIter);
    checkMin(a_minIter, minCandidateIter);    
}

template <typename ForwardIter>
void checkMax(ForwardIter& a_maxIter, ForwardIter& maxCandidateIter)
{
    if(!(*maxCandidateIter < *a_maxIter))
    {
        a_maxIter = maxCandidateIter;
    }    
}

template <typename ForwardIter>
void checkMin(ForwardIter& a_minIter, ForwardIter& minCandidateIter)
{
    if(*minCandidateIter < *a_minIter)
    {
        a_minIter = minCandidateIter;
    }       
}