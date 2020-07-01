#include "mu_test.h"

#include <utility> // pair

using namespace std;

pair<int, int>

UNIT(smoke)

    ASSERT_PASS();

END_UNIT

TEST_SUITE(ones)

    TEST(smoke)

END_SUITE    