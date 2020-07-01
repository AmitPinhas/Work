#include "mu_test.h"

#include <vector>

using namespace std;

bool IsPresent(vector<int>& a_vector,  int a_num)
{
    const size_t vectorSize = a_vector.size();

    if(0 == vectorSize)
    {
        return false;
    }

    const size_t indexLastElement = vectorSize - 1;

    if(a_vector[indexLastElement] == a_num)
    {
        return true;
    }

    a_vector[indexLastElement] = a_num;

    size_t i;

    for(i = 0; ; ++i)
    {
        if(a_vector[i] == a_num)
        {
            if(i == indexLastElement)
            {
                return false;
            }

            break;
        }
    }

    return true;
    
}

UNIT(smoke)

    vector<int> v{2, 7, 68, 633, -57664, 4, 0, 1};

    ASSERT_THAT(IsPresent(v, 68));

END_UNIT

TEST_SUITE(q1_readiness)

    TEST(smoke)

END_SUITE