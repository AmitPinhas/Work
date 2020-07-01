#include "mu_test.h"

#include "bit_set.hpp"

using namespace std;
using namespace advcpp;

UNIT(set_and_get)

    const size_t numBits = 640;

    BitSet<numBits> bitSet;

    const size_t index = 100;

    ASSERT_THAT(!bitSet.Get(index));

    bitSet.Set(index);

    ASSERT_THAT(bitSet.Get(index));

END_UNIT

UNIT(clear_operator_subscript)

    const size_t numBits = 640;

    BitSet<numBits> bitSet;

    const size_t index = 100;

    bitSet.Set(index);

    ASSERT_THAT(bitSet[index]);

    bitSet.Clear(index);    

    ASSERT_THAT(!bitSet[index]);        

END_UNIT

UNIT(assignment_by_bitwise_AND)

    const size_t numBits = 640;

    BitSet<numBits> first;

    const size_t indexFirst = 100;

    first.Set(indexFirst);

    BitSet<numBits> second;

    const size_t indexSecond = 45;
  
    second.Set(indexFirst);
    second.Set(indexSecond);

    second &= first; 

    ASSERT_THAT(second.Get(indexFirst));
    ASSERT_THAT(!second[indexSecond]);

END_UNIT

UNIT(assignment_by_bitwise_OR)

    const size_t numBits = 640;

    BitSet<numBits> first;

    const size_t indexFirst = 100;

    first.Set(indexFirst);

    BitSet<numBits> second;

    const size_t indexSecond = 45;
  
    second.Set(indexFirst);
    second.Set(indexSecond);

    second |= first; 

    ASSERT_THAT(second.Get(indexFirst));
    ASSERT_THAT(second[indexSecond]);

END_UNIT


UNIT(assignment_by_bitwise_XOR)

    const size_t numBits = 640;

    BitSet<numBits> first;

    const size_t indexFirst = 100;

    first.Set(indexFirst);

    BitSet<numBits> second;

    const size_t indexSecond = 45;
  
    second.Set(indexFirst);
    second.Set(indexSecond);

    second ^= first; 

    ASSERT_THAT(!second.Get(indexFirst));
    ASSERT_THAT(second[indexSecond]);

END_UNIT

UNIT(bitwise_NOT)

    const size_t numBits = 640;

    BitSet<numBits> first;

    const size_t indexFirst = 100;

    first.Set(indexFirst);

    ~first;

    ASSERT_THAT(!first[indexFirst]);

END_UNIT

UNIT(count)

    const size_t numBits = 640;

    BitSet<numBits> first;

    const size_t indexFirst = 100;

    first.Set(indexFirst);

    ASSERT_THAT(first.Count() == 1);

    ~first;

    ASSERT_THAT(first.Count() == 639);    

END_UNIT

UNIT(any)

    const size_t numBits = 640;

    BitSet<numBits> first;

    const size_t indexFirst = 100;

    ASSERT_THAT(!first.Any());

    first.Set(indexFirst);

    ASSERT_THAT(first.Any());  

END_UNIT

UNIT(all)

    const size_t numBits = 640;

    BitSet<numBits> first;

    ASSERT_THAT(!first.All());

    ~first;

    ASSERT_THAT(first.All());  


END_UNIT

UNIT(none)

    const size_t numBits = 640;

    BitSet<numBits> first;

    ASSERT_THAT(first.None());

    const size_t indexFirst = 100;    

    first.Set(indexFirst);

    ASSERT_THAT(!first.None());  


END_UNIT

UNIT(assignment_by_bitwise_left_shift)

    const size_t numBits = 640;    

    BitSet<numBits> first;

    const size_t indexFirst = 100;   

    first.Set(indexFirst);

    const size_t numS = 64;

    first <<= numS;

    ASSERT_THAT(!first.Get(indexFirst));

    ASSERT_THAT(!first.Get(indexFirst + numS));        

END_UNIT

TEST_SUITE(bit_set)

    TEST(set_and_get)
    TEST(clear_operator_subscript)
    TEST(assignment_by_bitwise_AND)
    TEST(assignment_by_bitwise_OR)
    TEST(assignment_by_bitwise_XOR)
    TEST(bitwise_NOT)
    TEST(count)
    TEST(any)
    TEST(all)
    TEST(none)
    TEST(assignment_by_bitwise_left_shift)

END_SUITE