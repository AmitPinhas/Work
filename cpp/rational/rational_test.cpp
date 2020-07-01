#include "mu_test.h"

#include "rational.hpp"

UNIT(value_numerator_denumerator_int)

	Rational<> rational(2) ;
	
	ASSERT_EQUAL( rational.Value(), 2);
	ASSERT_EQUAL( rational.Numerator(), 2);
	ASSERT_EQUAL( rational.Denumerator(), 1);

			
END_UNIT

UNIT(value_numerator_denumerator_long)

	Rational<long> rational(75675) ;
	
	ASSERT_EQUAL( rational.Value(), 75675);
	ASSERT_EQUAL( rational.Numerator(), 75675);
	ASSERT_EQUAL( rational.Denumerator(), 1);

			
END_UNIT

UNIT(value_numerator_denumerator_int_big_input)

	Rational<> rational(3408530,2) ;
	
	ASSERT_EQUAL( rational.Value(), 1704265);
	ASSERT_EQUAL( rational.Numerator(), 3408530);
	ASSERT_EQUAL( rational.Denumerator(), 2);

			
END_UNIT


UNIT(value_numerator_denumerator_long_big_input)

	Rational<long> rational(36781320,5) ;
	
	ASSERT_EQUAL( rational.Value(), 7356264);
	ASSERT_EQUAL( rational.Numerator(), 36781320);
	ASSERT_EQUAL( rational.Denumerator(), 5);
	
			
END_UNIT

UNIT(addition_assignment)

	Rational<> rational1(1,2), rational2(3,9) ;
	
	rational1 += rational2 ;
	
	ASSERT_EQUAL( rational1.Value(), (double)15/18);
	ASSERT_EQUAL( rational1.Numerator(), 15);
	ASSERT_EQUAL( rational1.Denumerator(), 18);
	
			
END_UNIT

UNIT(default_constructor)

	Rational<> rational ;
	
	ASSERT_EQUAL( rational.Value(), 0);
	ASSERT_EQUAL( rational.Numerator(), 0);
	ASSERT_EQUAL( rational.Denumerator(), 1);
	
			
END_UNIT

UNIT(subtraction_assignment)

	Rational<> rational1(1,2), rational2(3,9) ;
	
	rational1 -= rational2 ;
	
	ASSERT_EQUAL( rational1.Value(), (double)3/18);
	ASSERT_EQUAL( rational1.Numerator(), 3);
	ASSERT_EQUAL( rational1.Denumerator(), 18);
	
			
END_UNIT

UNIT(multiplication_assignment)

	Rational<> rational1(3,7), rational2(3,9) ;
	
	rational1 *= rational2 ;
	
	ASSERT_EQUAL( rational1.Value(), (double)9/63);
	ASSERT_EQUAL( rational1.Numerator(), 9);
	ASSERT_EQUAL( rational1.Denumerator(), 63);
			
END_UNIT


UNIT(division_assignment)

	Rational<> rational1(35,4), rational2(5,69) ;
	
	rational1 /= rational2 ;
	
	ASSERT_EQUAL( rational1.Value(), (double)2415/20);
	ASSERT_EQUAL( rational1.Numerator(), 2415);
	ASSERT_EQUAL( rational1.Denumerator(), 20);
			
END_UNIT


UNIT(addition_assignment_T)

	Rational<> rational(5,3) ;
	
	rational += 5 ;
	
	ASSERT_EQUAL( rational.Value(), (double)20/3);
	ASSERT_EQUAL( rational.Numerator(), 20);
	ASSERT_EQUAL( rational.Denumerator(), 3);
			
END_UNIT


UNIT(subtraction_assignment_T)

	Rational<> rational(5,3) ;
	
	rational -= 5 ;
	
	ASSERT_EQUAL( rational.Value(), (double)-10/3);
	ASSERT_EQUAL( rational.Numerator(), -10);
	ASSERT_EQUAL( rational.Denumerator(), 3);
			
END_UNIT

UNIT(multiplication_assignment_T)

	Rational<> rational(5,3) ;
	
	rational *= 5 ;
	
	ASSERT_EQUAL( rational.Value(), (double)75/9);
	ASSERT_EQUAL( rational.Numerator(), 75);
	ASSERT_EQUAL( rational.Denumerator(), 9);
			
END_UNIT

UNIT(division_assignment_T)

	Rational<> rational(5,3) ;
	
	rational /= 5 ;
	
	ASSERT_EQUAL( rational.Value(), (double)15/45);
	ASSERT_EQUAL( rational.Numerator(), 15);
	ASSERT_EQUAL( rational.Denumerator(), 45);
			
END_UNIT


UNIT(addition)

	Rational<> rational1(1,2), rational2(3,9) ;
	
	Rational<> res = rational1 + rational2 ;
	
	ASSERT_EQUAL( res.Value(), (double)15/18);
	ASSERT_EQUAL( res.Numerator(), 15);
	ASSERT_EQUAL( res.Denumerator(), 18);
	
			
END_UNIT


UNIT(addition_T)

	Rational<> rational(5,3) ;
	
	Rational<> res = rational + 5 ;
	
	ASSERT_EQUAL( res.Value(), (double)20/3);
	ASSERT_EQUAL( res.Numerator(), 20);
	ASSERT_EQUAL( res.Denumerator(), 3);
	
			
END_UNIT


UNIT(addition_T_left)

	Rational<> rational(5,3) ;
	
	Rational<> res =  5 + rational ;
	
	ASSERT_EQUAL( res.Value(), (double)20/3);
	ASSERT_EQUAL( res.Numerator(), 20);
	ASSERT_EQUAL( res.Denumerator(), 3);
	
			
END_UNIT

UNIT(subtraction)

	Rational<> rational1(1,2), rational2(3,9) ;
	
	Rational<> res = rational1 - rational2 ;
	
	ASSERT_EQUAL( res.Value(), (double)3/18);
	ASSERT_EQUAL( res.Numerator(), 3);
	ASSERT_EQUAL( res.Denumerator(), 18);
	
			
END_UNIT


UNIT(subtraction_T)

	Rational<> rational(5,3) ;
	
	Rational<> res = rational - 5 ;
	
	ASSERT_EQUAL( res.Value(), (double)-10/3);
	ASSERT_EQUAL( res.Numerator(), -10);
	ASSERT_EQUAL( res.Denumerator(), 3);
			
END_UNIT

UNIT(subtraction_T_left)

	Rational<> rational(5,3) ;
	
	Rational<> res = 5 - rational ;
	
	ASSERT_EQUAL( res.Value(), (double)10/3);
	ASSERT_EQUAL( res.Numerator(), 10);
	ASSERT_EQUAL( res.Denumerator(), 3);
			
END_UNIT


UNIT(multiplication)

	Rational<> rational1(3,7), rational2(3,9) ;
	
	Rational<> res = rational1 * rational2 ;
	
	ASSERT_EQUAL( res.Value(), (double)9/63);
	ASSERT_EQUAL( res.Numerator(), 9);
	ASSERT_EQUAL( res.Denumerator(), 63);
			
END_UNIT

UNIT(multiplication_T)

	Rational<> rational(5,3) ;
	
	Rational<> res = rational * 5 ;
	
	ASSERT_EQUAL( res.Value(), (double)75/9);
	ASSERT_EQUAL( res.Numerator(), 75);
	ASSERT_EQUAL( res.Denumerator(), 9);
			
END_UNIT

UNIT(multiplication_T_left)

	Rational<> rational(5,3) ;
	
	Rational<> res = 5 * rational ;
	
	ASSERT_EQUAL( res.Value(), (double)75/9);
	ASSERT_EQUAL( res.Numerator(), 75);
	ASSERT_EQUAL( res.Denumerator(), 9);
			
END_UNIT

UNIT(division)

	Rational<> rational1(35,4), rational2(5,69) ;
	
	Rational<> res = rational1 / rational2 ;
	
	ASSERT_EQUAL( res.Value(), (double)2415/20);
	ASSERT_EQUAL( res.Numerator(), 2415);
	ASSERT_EQUAL( res.Denumerator(), 20);
			
END_UNIT

UNIT(division_T)

	Rational<> rational(5,3) ;
	
	Rational<> res = rational / 5 ;
	
	ASSERT_EQUAL( res.Value(), (double)15/45);
	ASSERT_EQUAL( res.Numerator(), 15);
	ASSERT_EQUAL( res.Denumerator(), 45);
			
END_UNIT

UNIT(division_T_left)

	Rational<> rational(5,3) ;
	
	Rational<> res = 5 / rational ;
	
	ASSERT_EQUAL( res.Value(), 45/15);
	ASSERT_EQUAL( res.Numerator(), 45);
	ASSERT_EQUAL( res.Denumerator(), 15);
			
END_UNIT

UNIT(equal_to_true)
{
	Rational<> rational1(5,3), rational2(10,6) ;
	
	ASSERT_EQUAL( (rational1 == rational2), 1);
}

END_UNIT

UNIT(equal_to_false)
{
	Rational<> rational1(5,3), rational2(11,6) ;
	
	ASSERT_EQUAL( (rational1 == rational2), 0);
}

END_UNIT

UNIT(equal_to_true_T)
{
	Rational<> rational1(6,3) ;
	
	ASSERT_EQUAL( (rational1 == 2), 1);
}

END_UNIT

UNIT(equal_to_false_T)
{
	Rational<> rational1(7,3) ;
	
	ASSERT_EQUAL( (rational1 == 2), 0);
}

END_UNIT

UNIT(equal_to_true_T_left)
{
	Rational<> rational1(6,3) ;
	
	ASSERT_EQUAL( (2 == rational1), 1);
}

END_UNIT

UNIT(equal_to_false_T_left)
{
	Rational<> rational1(7,3) ;
	
	ASSERT_EQUAL( (2 == rational1), 0);
}

END_UNIT

UNIT(not_equal_to_true)
{
	Rational<> rational1(5,3), rational2(11,6) ;
	
	ASSERT_EQUAL( (rational1 != rational2), 1);
}

END_UNIT

UNIT(not_equal_to_false)
{
	Rational<> rational1(5,3), rational2(10,6) ;
	
	ASSERT_EQUAL( (rational1 != rational2), 0);
}

END_UNIT

UNIT(not_equal_to_true_T)
{
	Rational<> rational1(7,3) ;
	
	ASSERT_EQUAL( (rational1 != 2), 1);
}

END_UNIT

UNIT(not_equal_to_false_T)
{
	Rational<> rational1(6,3) ;
	
	ASSERT_EQUAL( (rational1 != 2), 0);
}

END_UNIT

UNIT(not_equal_to_true_T_left)
{
	Rational<> rational1(7,3) ;
	
	ASSERT_EQUAL( (2 != rational1), 1);
}

END_UNIT

UNIT(not_equal_to_false_T_left)
{
	Rational<> rational1(6,3) ;
	
	ASSERT_EQUAL( (2 != rational1), 0);
}

END_UNIT


UNIT(greater_than_true)
{
	Rational<> rational1(10,3), rational2(10,6) ;
	
	ASSERT_EQUAL( (rational1 > rational2), 1);
}

END_UNIT

UNIT(greater_than_false)
{
	Rational<> rational1(5,6), rational2(11,6) ;
	
	ASSERT_EQUAL( (rational1 > rational2), 0);
}

END_UNIT

UNIT(greater_than_true_T)
{
	Rational<> rational1(8,3) ;
	
	ASSERT_EQUAL( (rational1 > 2), 1);
}

END_UNIT

UNIT(greater_than_false_T)
{
	Rational<> rational1(4,3) ;
	
	ASSERT_EQUAL( (rational1 > 2), 0);
}

END_UNIT

UNIT(greater_than_true_T_left)
{
	Rational<> rational1(5,3) ;
	
	ASSERT_EQUAL( (2 > rational1), 1);
}

END_UNIT

UNIT(greater_than_false_T_left)
{
	Rational<> rational1(7,3) ;
	
	ASSERT_EQUAL( (2 > rational1), 0);
}

END_UNIT


UNIT(less_than_to_true)
{
	Rational<> rational1(10,3), rational2(10,2) ;
	
	ASSERT_EQUAL( (rational1 < rational2), 1);
}

END_UNIT

UNIT(less_than_to_false)
{
	Rational<> rational1(55,6), rational2(11,6) ;
	
	ASSERT_EQUAL( (rational1 < rational2), 0);
}

END_UNIT	


UNIT(less_than_to_true_T)
{
	Rational<> rational1(2,3) ;
	
	ASSERT_EQUAL( (rational1 < 2), 1);
}

END_UNIT

UNIT(less_than_to_false_T)
{
	Rational<> rational1(8,3) ;
	
	ASSERT_EQUAL( (rational1 < 2), 0);
}

END_UNIT
	
UNIT(less_than_to_true_T_left)
{
	Rational<> rational1(7,3) ;
	
	ASSERT_EQUAL( (2 < rational1), 1);
}

END_UNIT	
	
UNIT(less_than_to_false_T_left)	
{
	Rational<> rational1(5,3) ;
	
	ASSERT_EQUAL( (2 < rational1), 0);
}

END_UNIT


UNIT(greater_than_or_true)
{
	Rational<> rational1(10,3), rational2(10,6) ;
	
	ASSERT_EQUAL( (rational1 >= rational2), 1);
	
	Rational<> rational3(10,6), rational4(10,6) ;

	ASSERT_EQUAL( (rational3 >= rational4), 1);		
}

END_UNIT

UNIT(greater_than_or_false)
{
	Rational<> rational1(5,6), rational2(11,6) ;
	
	ASSERT_EQUAL( (rational1 >= rational2), 0);
	
	Rational<> rational3(1,6), rational4(10,6) ;

	ASSERT_EQUAL( (rational3 >= rational4), 0);				
}

END_UNIT

UNIT(greater_than_or_true_T)
{
	Rational<> rational1(8,3) ;
	
	ASSERT_EQUAL( (rational1 >= 2), 1);
	
	Rational<> rational3(6,6) ;	
	
	ASSERT_EQUAL( (rational3 >= 1), 1);	
}

END_UNIT

UNIT(greater_than_or_false_T)
{
	Rational<> rational1(4,3) ;
	
	ASSERT_EQUAL( (rational1 >= 2), 0);
	
	Rational<> rational3(5,6) ;		
	
	ASSERT_EQUAL( (rational3 >= 1), 0);		
}

END_UNIT

UNIT(greater_than_or_true_T_left)
{
	Rational<> rational1(5,3) ;
	
	ASSERT_EQUAL( (2 >= rational1), 1);
	
	Rational<> rational3(6,6) ;		
	
	ASSERT_EQUAL( (1 >= rational3), 1);		
}

END_UNIT

UNIT(greater_than_or_false_T_left)
{
	Rational<> rational1(7,3) ;
	
	ASSERT_EQUAL( (2 >= rational1), 0);
	
	Rational<> rational3(8,6) ;		
	
	ASSERT_EQUAL( (1 >= rational3), 0);	
}

END_UNIT


UNIT(less_than_or_true)
{
	Rational<> rational1(10,7), rational2(10,6) ;
	
	ASSERT_EQUAL( (rational1 <= rational2), 1);
	
	Rational<> rational3(10,6), rational4(10,6) ;

	ASSERT_EQUAL( (rational3 <= rational4), 1);		
}

END_UNIT

UNIT(less_than_or_false)
{
	Rational<> rational1(12,6), rational2(11,6) ;
	
	ASSERT_EQUAL( (rational1 <= rational2), 0);
	
	Rational<> rational3(11,6), rational4(10,6) ;

	ASSERT_EQUAL( (rational3 <= rational4), 0);				
}

END_UNIT

UNIT(less_than_or_true_T)
{
	Rational<> rational1(5,3) ;
	
	ASSERT_EQUAL( (rational1 <= 2), 1);
	
	Rational<> rational3(6,6) ;	
	
	ASSERT_EQUAL( (rational3 <= 1), 1);	
}

END_UNIT

UNIT(less_than_or_false_T)

	Rational<> rational1(8,3) ;
	
	ASSERT_EQUAL( (rational1 <= 2), 0);
	
	Rational<> rational3(7,6) ;		
	
	ASSERT_EQUAL( (rational3 <= 1), 0);		

END_UNIT

UNIT(less_than_or_true_T_left)

	Rational<> rational1(8,3) ;
	
	ASSERT_EQUAL( (2 <= rational1), 1);
	
	Rational<> rational3(6,6) ;		
	
	ASSERT_EQUAL( (1 <= rational3), 1);		

END_UNIT

UNIT(less_than_or_false_T_left)

	Rational<> rational1(5,3) ;
	
	ASSERT_EQUAL( (2 <= rational1), 0);
	
	Rational<> rational3(7,8) ;		
	
	ASSERT_EQUAL( (1 <= rational3), 0);	

END_UNIT


UNIT(egypt)

	Rational<> rational1(7,16) ;
	
	Egypt( rational1 ) ;
	
	ASSERT_PASS();

END_UNIT

TEST_SUITE(test the rational on fire)

	TEST(value_numerator_denumerator_int)
	TEST(value_numerator_denumerator_long)
	TEST(value_numerator_denumerator_int_big_input)
	TEST(value_numerator_denumerator_long_big_input)
	TEST(addition_assignment)
	TEST(default_constructor)
	TEST(subtraction_assignment)
	TEST(multiplication_assignment)
	TEST(division_assignment)
	TEST(addition_assignment_T)
	TEST(subtraction_assignment_T)
	TEST(multiplication_assignment_T)
	TEST(division_assignment_T)
	TEST(addition)
	TEST(addition_T)
	TEST(addition_T_left)
	TEST(subtraction)
	TEST(subtraction_T)
	TEST(subtraction_T_left)
	TEST(multiplication)
	TEST(multiplication_T)
	TEST(multiplication_T_left)
	TEST(division)
	TEST(division_T)
	TEST(division_T_left)
	TEST(equal_to_true)
	TEST(equal_to_false)
	TEST(equal_to_true_T)
	TEST(equal_to_false_T)
	TEST(equal_to_true_T_left)
	TEST(equal_to_false_T_left)
	TEST(not_equal_to_true)
	TEST(not_equal_to_false)
	TEST(not_equal_to_true_T)
	TEST(not_equal_to_false_T)
	TEST(not_equal_to_true_T_left)
	TEST(not_equal_to_false_T_left)
	TEST(greater_than_true)
	TEST(greater_than_false)
	TEST(greater_than_true_T)
	TEST(greater_than_false_T)
	TEST(greater_than_true_T_left)
	TEST(greater_than_false_T_left)
	TEST(less_than_to_true)
	TEST(less_than_to_false)
	TEST(less_than_to_true_T)
	TEST(less_than_to_false_T)
	TEST(less_than_to_true_T_left)
	TEST(less_than_to_false_T_left)	
	TEST(greater_than_or_true)
	TEST(greater_than_or_false)
	TEST(greater_than_or_true_T)
	TEST(greater_than_or_false_T)
	TEST(greater_than_or_true_T_left)
	TEST(greater_than_or_false_T_left)	
	TEST(less_than_or_true)
	TEST(less_than_or_false)
	TEST(less_than_or_true_T)
	TEST(less_than_or_false_T)
	TEST(less_than_or_true_T_left)
	TEST(less_than_or_false_T_left)	
	TEST(egypt)		

END_SUITE
