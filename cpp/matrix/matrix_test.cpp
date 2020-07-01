#include "mu_test.h"

#include "matrix.hpp"
#include "magic.hpp"


UNIT(test_diag_pos)

	Matrix m(3,3) ;
	Matrix d(3,3) ;
	
	m.Diagonal(5) ;	
	
	size_t n = 3 ;
	
	while( n-- > 0 )
	{
		ASSERT_EQUAL( m.Get(n,n) , 5);
	}
		
	d.Diagonal(4) ;	

	n = 3 ;
		
	while( n-- > 0 )
	{
		ASSERT_EQUAL( d.Get(n,n) , 4);
	}
		
END_UNIT


UNIT(test_square)

	Matrix m(3);

	m.Diagonal(5);	
	
	m.Square();
	
	size_t n = 3 ;
	
	while( n-- > 0 )
	{
		ASSERT_EQUAL( m.Get(n,n) , 25);
	}
	
	Matrix r(353,7876);

	r = 3 ;

	r.Square();
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL( r.Get(i,j) , 9);
		}
	} 
		
END_UNIT


UNIT(test_dim)

	Matrix m(3);

	Dimension rowCol = m.Dim();
	
	ASSERT_EQUAL( rowCol.m_rows, 3 );
	ASSERT_EQUAL( rowCol.m_columns, 3 );
	
	Matrix r(353,7876);
	
	Dimension rDim = r.Dim();
	
	ASSERT_EQUAL( rDim.m_rows, 353 );
	ASSERT_EQUAL( rDim.m_columns, 7876 );			
		
END_UNIT


UNIT(test_set_get)

	Matrix m(3,4);
	int i =3, k=3  ;
	while(i-- > 0)
	{
		int j = 4 ;
		while(j-- > 0)
		{
			m.Set(i,j, i+j) ;
		}
		
	}

	while(k-- > 0)
	{
		int f = 4 ;
		while(f-- > 0)
		{
			ASSERT_EQUAL(m.Get(k,f), k+f) ;
		}
	}	
	
		
END_UNIT


UNIT(test_transpose_square)

	Matrix m(7);

	srand(time(0));
	
	for ( size_t i = 0 ; i < 7 ; ++i )
	{
		for ( size_t j = 0 ; j < 7 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 	
	
	Matrix tmp = m ;
	
	m.Transpose();
	
	for ( size_t i = 0 ; i < 7 ; ++i )
	{
		for ( size_t j = 0 ; j < 7 ; ++j )
		{
			ASSERT_EQUAL( m.Get(i,j), tmp.Get(j,i) ) ;
		}
	} 			
		
END_UNIT


UNIT(test_transpose_not_square)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 
	
	Matrix d = m ;
	
	m.Transpose();
	
	Dimension rowCol = m.Dim();
	
	ASSERT_EQUAL( rowCol.m_rows, 7876 );
	ASSERT_EQUAL( rowCol.m_columns, 353 );
	 
	
	for ( size_t i = 0 ; i < 7876 ; ++i )
	{
		for ( size_t j = 0 ; j < 353 ; ++j )
		{
			ASSERT_EQUAL( m.Get(i,j), d.Get(j,i) ) ;
		}
	} 	 			
		
END_UNIT


UNIT(constructor_square)

	Matrix m(534);
	Dimension tmp = m.Dim() ;
	
	ASSERT_EQUAL( tmp.m_rows , 534);
	ASSERT_EQUAL( tmp.m_columns , 534);	
		
END_UNIT

UNIT(copy_constructor)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 	
	
	Matrix d(m);
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL( d.Get(i,j), m.Get(i,j) );
		}
	} 
	
	d.Set(32,65, 101010);
	m.Set(32,65, 2323);	
	ASSERT_EQUAL( d.Get(32,65) , 101010 ) ;
	ASSERT_EQUAL( m.Get(32,65) , 2323 ) ;		
		
END_UNIT


UNIT(operator_assignment)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 	
	
	Matrix d = m;
	
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL( d.Get(i,j), m.Get(i,j) );
		}
	} 
	
	d.Set(32,65, 101010);
	m.Set(32,65, 2323);	
	ASSERT_EQUAL( d.Get(32,65) , 101010 ) ;
	ASSERT_EQUAL( m.Get(32,65) , 2323 ) ;	
		
END_UNIT

UNIT(operator_addition)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 	
	
	Matrix d(353,7876);
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			d.Set(i,j,rand() % 1430);
		}
	} 

	Matrix s(353,7876);
	
	s = m + d ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL(s.Get(i,j),  d.Get(i,j) + m.Get(i,j));
		}
	} 
		
END_UNIT

UNIT(operator_addition_elem_type)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 	

	Matrix s(353,7876);
	
	s = m + 5 ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL(s.Get(i,j),  m.Get(i,j) + 5 );
		}
	} 
		
END_UNIT


UNIT(operator_subtraction)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 	
	
	Matrix d(353,7876);
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			d.Set(i,j,rand() % 1430);
		}
	} 

	Matrix s(353,7876);
	
	s = m - d ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL(s.Get(i,j),  m.Get(i,j) - d.Get(i,j));
		}
	} 
		
END_UNIT

UNIT(operator_subtraction_elem_type)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 	

	Matrix s(353,7876);
	
	s = m - 5 ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL(s.Get(i,j),  m.Get(i,j) - 5 );
		}
	} 
		
END_UNIT


UNIT(operator_addition_assignment)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 	
	
	m.Set( 43, 54, 1111 );		
	
	Matrix d(353,7876), ret(353,7876);
	
	ret = d += m ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL( d.Get(i,j),  m.Get(i,j) );
		}
	} 

	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL( ret.Get(i,j),  d.Get(i,j) );
		}
	} 	
	
	ret.Set( 43, 54, 6666);		
	d.Set( 43, 54, 5555 );
	
	ASSERT_EQUAL( m.Get( 43, 54 ), 1111 );
	ASSERT_EQUAL( d.Get( 43, 54 ), 5555 );	
	ASSERT_EQUAL( ret.Get( 43, 54 ), 6666 );
	
		
END_UNIT

UNIT(operator_addition_assignment_elem_type)

	Matrix s(353,7876);
	
	s += 5 ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL(s.Get(i,j),  5 );
		}
	} 
		
END_UNIT

UNIT(operator_subtraction_assignment)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 	
	
	m.Set( 43, 54, 1111 );		
	
	Matrix d(353,7876), ret(353,7876);
	
	ret = d -= m ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL( d.Get(i,j),  -m.Get(i,j) );
		}
	} 
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL( ret.Get(i,j),  d.Get(i,j) );
		}
	} 	
	
	ret.Set( 43, 54, 6666);		
	d.Set( 43, 54, 5555 );
	
	ASSERT_EQUAL( m.Get( 43, 54 ), 1111 );
	ASSERT_EQUAL( d.Get( 43, 54 ), 5555 );	
	ASSERT_EQUAL( ret.Get( 43, 54 ), 6666 );	
			
END_UNIT

UNIT(operator_subtraction_assignment_elem_type)

	Matrix s(353,7876);
	
	s -= 5 ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL(s.Get(i,j),  -5 );
		}
	} 
		
END_UNIT

UNIT(operator_multiplication_assignment_elem_type)

	Matrix s(353,7876);

	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			s.Set(i,j, 1);
		}
	} 
	
	s *= 5 ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL(s.Get(i,j),  5 );
		}
	} 
		
END_UNIT

UNIT(operator_division_assignment_elem_type)

	Matrix s(353,7876);

	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			s.Set(i,j, 4);
		}
	} 
	
	s /= 4 ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			ASSERT_EQUAL(s.Get(i,j),  1 );
		}
	} 
		
END_UNIT

UNIT(operator_equal_to_true)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 		
	
	Matrix d(353,7876) ;
	
	d = m ;
	
	ASSERT_EQUAL( (d == m) , 1 );	
			
END_UNIT

UNIT(operator_equal_to_false)

	Matrix m(353,7876);
	
	srand(time(0));
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
			m.Set(i,j,rand() % 1430);
		}
	} 		
	
	Matrix d(353,7876) ;
	
	d = m ;
	
	m.Set( 43, 54, 1111 );		
	d.Set( 43, 54, 1542 );				
	
	ASSERT_EQUAL( (d == m) , 0 );	
			
END_UNIT

UNIT(operator_equal_to_false_not_congruent)

	Matrix m(353,7876);	
	
	Matrix d(353,7875) ;			
	
	ASSERT_EQUAL( (d == m) , 0 );	
			
END_UNIT


UNIT(operator_multiplication)

	Matrix s(1,3), b(3,2);
	
	s.Set(0,0,3);
	s.Set(0,1,1);
	s.Set(0,2,4);
	
	b.Set(0,0,4);
	b.Set(0,1,3);
	b.Set(1,0,2);
	b.Set(1,1,5);
	b.Set(2,0,6);
	b.Set(2,1,8);
	
	Matrix res = s * b ;
	
	ASSERT_EQUAL( res.Get(0,0), 38) ;
	ASSERT_EQUAL( res.Get(0,1), 46) ;					
		
END_UNIT

UNIT(operator_multiplication2)

	Matrix a(3,2), b(2,3);
	
	a.Set(0,0,3);
	a.Set(0,1,4);
	a.Set(1,0,7);
	a.Set(1,1,2);
	a.Set(2,0,5);
	a.Set(2,1,9);

	b.Set(0,0,3);
	b.Set(0,1,1);
	b.Set(0,2,5);
	b.Set(1,0,6);
	b.Set(1,1,9);
	b.Set(1,2,7);
		
	Matrix res = a * b ;
	
	ASSERT_EQUAL( res.Get(0,0), 33) ;		
	ASSERT_EQUAL( res.Get(0,1), 39) ;
	ASSERT_EQUAL( res.Get(0,2), 43) ;
	ASSERT_EQUAL( res.Get(1,0), 33) ;
	ASSERT_EQUAL( res.Get(1,1), 25) ;						
	ASSERT_EQUAL( res.Get(1,2), 49) ;
	ASSERT_EQUAL( res.Get(2,0), 69) ;
	ASSERT_EQUAL( res.Get(2,1), 86) ;
	ASSERT_EQUAL( res.Get(2,2), 88) ;	
			
END_UNIT


UNIT(operator_multiplication_assignment)

	Matrix s(1,3), b(3,2);
	
	s.Set(0,0,3);
	s.Set(0,1,1);
	s.Set(0,2,4);
	
	b.Set(0,0,4);
	b.Set(0,1,3);
	b.Set(1,0,2);
	b.Set(1,1,5);
	b.Set(2,0,6);
	b.Set(2,1,8);
	
	s *= b ;
	
	ASSERT_EQUAL( s.Get(0,0), 38) ;
	ASSERT_EQUAL( s.Get(0,1), 46) ;
	
				
		
END_UNIT


UNIT(operator_multiplication_elem_type)

	Matrix m(353,7876) ;
	
	m = 8 ;
	
	Matrix res = m * 2 ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
				ASSERT_EQUAL(res.Get(i,j), 16);
		}
	} 					
		
END_UNIT

UNIT(operator_multiplication_assignment2)

	Matrix a(3,2), b(2,3);
	
	a.Set(0,0,3);
	a.Set(0,1,4);
	a.Set(1,0,7);
	a.Set(1,1,2);
	a.Set(2,0,5);
	a.Set(2,1,9);

	b.Set(0,0,3);
	b.Set(0,1,1);
	b.Set(0,2,5);
	b.Set(1,0,6);
	b.Set(1,1,9);
	b.Set(1,2,7);
		
	 a *= b ;
	
	ASSERT_EQUAL( a.Get(0,0), 33) ;		
	ASSERT_EQUAL( a.Get(0,1), 39) ;
	ASSERT_EQUAL( a.Get(0,2), 43) ;
	ASSERT_EQUAL( a.Get(1,0), 33) ;
	ASSERT_EQUAL( a.Get(1,1), 25) ;						
	ASSERT_EQUAL( a.Get(1,2), 49) ;
	ASSERT_EQUAL( a.Get(2,0), 69) ;
	ASSERT_EQUAL( a.Get(2,1), 86) ;
	ASSERT_EQUAL( a.Get(2,2), 88) ;	
			
END_UNIT


UNIT(operator_assignment_elem_type)

	Matrix m(353,7876) ;
	
	m = 8 ;
	
	for ( size_t i = 0 ; i < 353 ; ++i )
	{
		for ( size_t j = 0 ; j < 7876 ; ++j )
		{
				ASSERT_EQUAL(m.Get(i,j), 8);
		}
	} 		
			
END_UNIT

UNIT(is_magic_square_true_odd)

	Matrix m(3);	
	
	m.Set(0,0,2);
	m.Set(0,1,9);
	m.Set(0,2,4);
	m.Set(1,0,7);
	m.Set(1,1,5);
	m.Set(1,2,3);		
	m.Set(2,0,6);
	m.Set(2,1,1);
	m.Set(2,2,8);	
		
	ASSERT_EQUAL( IsMagicSquare( m ) , 1 );	
			
END_UNIT

UNIT(is_magic_square_true_even)

	Matrix m(4);	
	
	m.Set(0,0,16);
	m.Set(0,1,3);
	m.Set(0,2,2);
	m.Set(0,3,13);	
	m.Set(1,0,5);
	m.Set(1,1,10);
	m.Set(1,2,11);
	m.Set(1,3,8);			
	m.Set(2,0,9);
	m.Set(2,1,6);
	m.Set(2,2,7);
	m.Set(2,3,12);	
	m.Set(3,0,4);
	m.Set(3,1,15);
	m.Set(3,2,14);
	m.Set(3,3,1);			
		
	ASSERT_EQUAL( IsMagicSquare( m ) , 1 );	
			
END_UNIT

UNIT(is_magic_square_false_not_square)

	Matrix m(4453,4324);
	
	ASSERT_EQUAL( IsMagicSquare( m ) , 0 );		

END_UNIT

UNIT(is_magic_square_false_illegal_input)

	Matrix m(10);
	
	m = 8 ;
	
	ASSERT_EQUAL( IsMagicSquare( m ) , 0 );		

END_UNIT

UNIT(is_magic_square_false_not_magic)

	Matrix m(3);	
	
	m.Set(0,0,2);
	m.Set(0,1,9);
	m.Set(0,2,4);
	m.Set(1,0,5);
	m.Set(1,1,5);
	m.Set(1,2,3);		
	m.Set(2,0,6);
	m.Set(2,1,1);
	m.Set(2,2,8);	
		
	ASSERT_EQUAL( IsMagicSquare( m ) , 0 );	
			
END_UNIT


UNIT(build_magic_square_odd)

	Matrix m = BuildMagicSquare(999);
	
	ASSERT_EQUAL( IsMagicSquare( m ) , 1 );		

END_UNIT

UNIT(build_magic_square_even)

	Matrix m = BuildMagicSquare(1000);
	
	ASSERT_EQUAL( IsMagicSquare( m ) , 1 );		

END_UNIT

TEST_SUITE(test the matrix on fire)
	TEST(test_diag_pos)
	TEST(test_square)
	TEST(test_dim)
	TEST(test_set_get)
	TEST(test_transpose_square)
	TEST(test_transpose_not_square)
	TEST(constructor_square)
	TEST(copy_constructor)
	TEST(operator_assignment)
	TEST(operator_addition)
	TEST(operator_addition_elem_type)
	TEST(operator_subtraction)
	TEST(operator_subtraction_elem_type)
	TEST(operator_addition_assignment)
	TEST(operator_addition_assignment_elem_type)
	TEST(operator_subtraction_assignment)
	TEST(operator_subtraction_assignment_elem_type)
	TEST(operator_multiplication_assignment_elem_type)
	TEST(operator_division_assignment_elem_type)
	TEST(operator_equal_to_true)
	TEST(operator_equal_to_false)
	TEST(operator_equal_to_false_not_congruent)
	TEST(operator_multiplication)
	TEST(operator_multiplication2)
	TEST(operator_multiplication_assignment)
	TEST(operator_multiplication_assignment2)
	TEST(operator_assignment_elem_type)
	TEST(operator_multiplication_elem_type)
	TEST(is_magic_square_true_odd)
	TEST(is_magic_square_true_even)
	TEST(is_magic_square_false_not_square)
	TEST(is_magic_square_false_illegal_input)
	TEST(is_magic_square_false_not_magic)
	TEST(build_magic_square_odd)
	TEST(build_magic_square_even)
END_SUITE
