#include "mu_test.h"

#include <vector>
#include <optional>

using namespace std;

optional<vector< vector<size_t>>> getSpiralMatrix(unsigned int a_num)
{
    if(0 == a_num)
    {
        return nullopt;
    }

    vector< vector<size_t>> spiralMatrix(a_num, vector<size_t>(a_num));

    if(1 == a_num)
    {
        spiralMatrix[0][0] = 1;
    }

    return spiralMatrix;
}

UNIT(zero)

    auto r = getSpiralMatrix(0);

    ASSERT_THAT(!r);

END_UNIT

UNIT(one)

    auto r = getSpiralMatrix(1);

    ASSERT_THAT((*r)[0][0] == 1);

END_UNIT


TEST_SUITE(get_spiral_matrix)

    TEST(zero)
    TEST(one)    

END_SUITE    