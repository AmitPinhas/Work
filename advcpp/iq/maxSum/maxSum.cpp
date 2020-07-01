#include "mu_test.h"

#include <optional>
#include <vector>
#include <tuple>

using namespace std;

optional<tuple<vector<int>::const_iterator,vector<int>::const_iterator, int>> 
FindMaxRange(const vector<int>& a_vector);

static void fillVectorMax(const vector<int>& a_vector, vector<int>& maxVector);

static pair<size_t, int> findMaxSum(const vector<int>& a_maxVector);

static pair<vector<int>::const_iterator, vector<int>::const_iterator> 
findRange(const vector<int>& a_vector, size_t a_indexMax, int a_maxSum);

UNIT(empty)

    vector<int> v;

    auto r = FindMaxRange(v);

    if(!r)
    {
        ASSERT_PASS();
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }

END_UNIT

UNIT(one_elements)

    vector<int> v{5};

    auto r = FindMaxRange(v);

    if(r)
    {
        int maxSum = get<2>(*r);

        ASSERT_THAT(maxSum == 5);

        auto begin = get<0>(*r);
        auto end = get<1>(*r);

        vector<int> vectorTestResult{5};

        auto testBegin = vectorTestResult.begin();
        auto testEnd = vectorTestResult.end();

        while(begin != end && testBegin != testEnd)
        {
           ASSERT_THAT(*begin == *testBegin); 
           ++begin;
           ++testBegin;
        }
        ASSERT_THAT(begin == end);
        ASSERT_THAT(testBegin == testEnd);
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }
    
END_UNIT

UNIT(two_elements)

    vector<int> v{5, 20};

    auto r = FindMaxRange(v);

    if(r)
    {
        int maxSum = get<2>(*r);

        ASSERT_THAT(maxSum == 25);

        auto begin = get<0>(*r);
        auto end = get<1>(*r);

        vector<int> vectorTestResult{5, 20};

        auto testBegin = vectorTestResult.begin();
        auto testEnd = vectorTestResult.end();

        while(begin != end && testBegin != testEnd)
        {
           ASSERT_THAT(*begin == *testBegin); 
           ++begin;
           ++testBegin;
        }
        ASSERT_THAT(begin == end);
        ASSERT_THAT(testBegin == testEnd);
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }
    
END_UNIT

UNIT(two_elements_one_neg_left)

    vector<int> v{-5, 20};

    auto r = FindMaxRange(v);

    if(r)
    {
        int maxSum = get<2>(*r);

        ASSERT_THAT(maxSum == 20);

        auto begin = get<0>(*r);
        auto end = get<1>(*r);

        vector<int> vectorTestResult{20};

        auto testBegin = vectorTestResult.begin();
        auto testEnd = vectorTestResult.end();

        while(begin != end && testBegin != testEnd)
        {
           ASSERT_THAT(*begin == *testBegin); 
           ++begin;
           ++testBegin;
        }
        ASSERT_THAT(begin == end);
        ASSERT_THAT(testBegin == testEnd);
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }
    
END_UNIT

UNIT(two_elements_one_neg_right)

    vector<int> v{20, -5};

    auto r = FindMaxRange(v);

    if(r)
    {
        int maxSum = get<2>(*r);

        ASSERT_THAT(maxSum == 20);

        auto begin = get<0>(*r);
        auto end = get<1>(*r);

        vector<int> vectorTestResult{20};

        auto testBegin = vectorTestResult.begin();
        auto testEnd = vectorTestResult.end();

        while(begin != end && testBegin != testEnd)
        {
           ASSERT_THAT(*begin == *testBegin); 
           ++begin;
           ++testBegin;
        }
        ASSERT_THAT(begin == end);
        ASSERT_THAT(testBegin == testEnd);
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }
    
END_UNIT

UNIT(big_range_in_start)

    vector<int> v{10, -2, 40, -3, 60, -5, 30, -40, -35, -3533};

    auto r = FindMaxRange(v);

    if(r)
    {
        int maxSum = get<2>(*r);

        ASSERT_THAT(maxSum == 130);

        auto begin = get<0>(*r);
        auto end = get<1>(*r);

        vector<int> vectorTestResult{10, -2, 40, -3, 60, -5, 30};

        auto testBegin = vectorTestResult.begin();
        auto testEnd = vectorTestResult.end();

        while(begin != end && testBegin != testEnd)
        {
           ASSERT_THAT(*begin == *testBegin); 
           ++begin;
           ++testBegin;
        }
        ASSERT_THAT(begin == end);
        ASSERT_THAT(testBegin == testEnd);
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }
    
END_UNIT

UNIT(big_range_in_last)

    vector<int> v{-40, -35, -3533, 10, -2, 40, -3, 60, -5, 30};

    auto r = FindMaxRange(v);

    if(r)
    {
        int maxSum = get<2>(*r);

        ASSERT_THAT(maxSum == 130);

        auto begin = get<0>(*r);
        auto end = get<1>(*r);

        vector<int> vectorTestResult{10, -2, 40, -3, 60, -5, 30};

        auto testBegin = vectorTestResult.begin();
        auto testEnd = vectorTestResult.end();

        while(begin != end && testBegin != testEnd)
        {
           ASSERT_THAT(*begin == *testBegin); 
           ++begin;
           ++testBegin;
        }
        ASSERT_THAT(begin == end);
        ASSERT_THAT(testBegin == testEnd);
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }
    
END_UNIT

UNIT(big_range_in_mid)

    vector<int> v{-40, -35, -3533, 10, -2, 40, -3, 60, -5, 30, -40, -35, -3533};

    auto r = FindMaxRange(v);

    if(r)
    {
        int maxSum = get<2>(*r);

        ASSERT_THAT(maxSum == 130);

        auto begin = get<0>(*r);
        auto end = get<1>(*r);

        vector<int> vectorTestResult{10, -2, 40, -3, 60, -5, 30};

        auto testBegin = vectorTestResult.begin();
        auto testEnd = vectorTestResult.end();

        while(begin != end && testBegin != testEnd)
        {
           ASSERT_THAT(*begin == *testBegin); 
           ++begin;
           ++testBegin;
        }
        ASSERT_THAT(begin == end);
        ASSERT_THAT(testBegin == testEnd);
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }
    
END_UNIT

TEST_SUITE(max_sum)

    TEST(empty)
    TEST(one_elements)
    TEST(two_elements)
    TEST(two_elements_one_neg_left)
    TEST(two_elements_one_neg_right)
    TEST(big_range_in_start)
    TEST(big_range_in_last)
    TEST(big_range_in_mid)

END_SUITE

optional<tuple<vector<int>::const_iterator,vector<int>::const_iterator, int>> 
FindMaxRange(const vector<int>& a_vector)
{
    const size_t vectorSize = a_vector.size();

    if(vectorSize == 0)
    {
        return nullopt;
    }

    if(vectorSize == 1)
    {
        return make_tuple(a_vector.begin(), a_vector.end(), a_vector[0]);
    }   

    vector<int> maxVector;

    maxVector.resize(vectorSize);

    fillVectorMax(a_vector, maxVector);

    auto [indexMax, maxSum] = findMaxSum(maxVector);

    auto [b, e] = findRange(a_vector, indexMax, maxSum);

    return make_tuple(b, e, maxSum);
}

static void fillVectorMax(const vector<int>& a_vector, vector<int>& a_maxVector)
{
    a_maxVector[0] = a_vector[0];

    for(size_t i = 1; i < a_vector.size(); ++i)
    {
        if(a_maxVector[i - 1] + a_vector[i] > a_vector[i])
        {
            a_maxVector[i] = a_maxVector[i - 1] + a_vector[i];
        }
        else
        {
            a_maxVector[i] = a_vector[i];
        }
        
    }
}

static pair<size_t, int> findMaxSum(const vector<int>& a_maxVector)
{
    size_t indexMaxSum = 0;

    int maxSum = a_maxVector[0];

    for(size_t i = 1; i < a_maxVector.size(); ++i)
    {
        if(a_maxVector[i] > maxSum)
        {
            maxSum = a_maxVector[i];
            indexMaxSum = i;
        }
    }

    return make_pair(indexMaxSum, maxSum);
}

static pair<vector<int>::const_iterator, vector<int>::const_iterator> 
findRange(const vector<int>& a_vector, size_t a_indexMax, int a_maxSum)
{
    auto end = a_vector.begin();

    advance(end, a_indexMax + 1);

    int i = a_indexMax;

    while(i >= 0)
    {
        a_maxSum -= a_vector[i];

        if(a_maxSum == 0)
        {
            break;
        }
        else
        {
            --i;
        }
    }

    auto begin = a_vector.begin();

    advance(begin, i);

    return make_pair(begin, end);
}