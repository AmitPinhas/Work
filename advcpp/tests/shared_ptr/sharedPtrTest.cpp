#include "mu_test.h"

#include "shared_ptr.hpp"

class Base {};
class Derived: public Base {};

UNIT(constructor_negation_operator)
    advcpp::SharedPtr<int> ptr;

    if(!ptr)
    {
        ASSERT_PASS();
    }
    else
    {
        ASSERT_FAIL("ptr not null");
    }

END_UNIT

UNIT(copy_constructor_operator_is_equal)
    advcpp::SharedPtr<int> ptrInt(new int);
    advcpp::SharedPtr<int> copyPtr(ptrInt);

    ASSERT_EQUAL((ptrInt == copyPtr) , true);

END_UNIT

UNIT(copy_constructor_derived)
    advcpp::SharedPtr<Derived> ptrDerived(new Derived);
    advcpp::SharedPtr<Base> basePtr(ptrDerived);

    ASSERT_PASS();
    
END_UNIT

TEST_SUITE(test the shared ptr on fire)

    TEST(constructor_negation_operator)
    TEST(copy_constructor_operator_is_equal) 
    TEST(copy_constructor_derived)   

END_SUITE
