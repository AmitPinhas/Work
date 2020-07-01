#include "mu_test.h"
#include "stack.hpp"

	

UNIT(new_stack_is_empty)
    Stack s;
    ASSERT_EQUAL(s.Size(), 0);
    ASSERT_THAT(s.Capacity() > 0 );
END_UNIT


UNIT(new_stack_is_full)
    Stack s;
    int n = 64 ;
    while(n-- > 0 )
    {
    	s.Push( 1 ) ;
    }
    ASSERT_EQUAL(s.Size(), 64);
    ASSERT_EQUAL(s.Capacity() , 64 );
END_UNIT

UNIT(new_stack_after_many_push)
    Stack s;
    int n = 34 ;
    while(n-- > 0 )
    {
    	s.Push( 1 ) ;
    }
    ASSERT_EQUAL(s.Size(), 34);
    ASSERT_EQUAL(s.Capacity() , 64 );
END_UNIT

UNIT(new_stack_after_many_push_and_pop)
    Stack s;
    int n = 53, n2 = 20 ;
    while(n-- > 0 )
    {
    	s.Push( 1 ) ;
    }
    while(n2-- > 0 )
    {
    	s.Pop() ;
    }    
    
    ASSERT_EQUAL(s.Size(), 33);
    ASSERT_EQUAL(s.Capacity() , 64 );
END_UNIT

UNIT(stack_print)
    Stack s;
    int n = 65, n2 = 20 ;
    while(n-- > 0 )
    {
    	try
    	{
    	s.Push( n ) ;
    	}
    	catch (advcpp::ExceptionOverFlow const& a_over)
    	{
    		std::cout << "overflow\n" ;
    	}
    }
    while(n2-- > 0 )
    {
    	s.Pop() ;
    }    
    
	s.Print();
	ASSERT_PASS();
	
END_UNIT


UNIT(stack_drain)
    Stack s, sDrain;
    int n = 9 ,n2 = 9;
    size_t res ;
    while(n-- > 0 )
    {
    	s.Push( n ) ;
    }
   
    res = sDrain.Drain(&s) ;

	ASSERT_EQUAL( res, 9 ) ;   
    ASSERT_EQUAL( s.Size() , 0 ) ;
    ASSERT_EQUAL( sDrain.Size() , 9 ) ;
    
    while(n2-- > 0 )
    {
    	ASSERT_EQUAL( sDrain.Pop(), n2) ;
    }
       	
END_UNIT


UNIT(stack_drain_null)
    Stack sDrain;
	size_t res ;
   
    res = sDrain.Drain(NULL) ;
    
    ASSERT_EQUAL( res , 0 ) ;
       	
END_UNIT


UNIT(stack_drain_half)
    Stack s, s2;
    int n = 60 , n2=10;
    while(n-- > 0 )
    {
    	s.Push( n ) ;
    }
    while(n2-- > 0 )
    {
    	s2.Push( n2 ) ;
    }    
    
    s.Drain(&s2) ;
    
    ASSERT_EQUAL( s.Size(), 64 ) ;
    ASSERT_EQUAL( s2.Size(), 6 ) ;
    
    ASSERT_EQUAL( s2.Pop(), 4 ) ;
    ASSERT_EQUAL( s2.Pop(), 5 ) ;
    ASSERT_EQUAL( s2.Pop(), 6 ) ;
    ASSERT_EQUAL( s2.Pop(), 7 ) ;
    ASSERT_EQUAL( s2.Pop(), 8 ) ;
    ASSERT_EQUAL( s2.Pop(), 9 ) ;                        
    
       	
END_UNIT

UNIT(stack_is_lifo)
    Stack s;
    s.Push(42);
    s.Push(888);
    s.Push(999);
    ASSERT_EQUAL(s.Pop(), 999);
    ASSERT_EQUAL(s.Pop(), 888);
    ASSERT_EQUAL(s.Pop(), 42);
END_UNIT

UNIT(drain_into_new_stack_copy)
    Stack s;
    
    ASSERT_THAT(s.Capacity() > 10);
    for (int i = 0; i < 10; ++i)
    {
        s.Push(i);
    }
    ASSERT_EQUAL(s.Size(), 10U);
    
    Stack d;
    ASSERT_EQUAL(d.Size(), 0U);
    d.Drain(&s);
    ASSERT_EQUAL(s.Size(), 0U);
    ASSERT_EQUAL(d.Size(), 10U);
    
    for (int i = 0; i < 10; ++i)
    {
        ASSERT_EQUAL(d.Pop(), i);
    }
    ASSERT_EQUAL(d.Size(), 0U);
END_UNIT


UNIT(top_func_after_push_and_many_tops)
	Stack s;
    ASSERT_THAT(s.Capacity() > 10);
    for (int i = 0; i < 10; ++i)
    {
        s.Push(i);
    }
    
    ASSERT_EQUAL( s.Top() , 9 );	
    ASSERT_EQUAL( s.Top() , 9 );	
    ASSERT_EQUAL( s.Top() , 9 );	
    ASSERT_EQUAL( s.Top() , 9 );	
    
    ASSERT_EQUAL( s.Size() , 10 ) ;
            	
END_UNIT

TEST_SUITE(test the stack on fire)
    TEST(new_stack_is_empty)
    TEST(new_stack_is_full)
    TEST(new_stack_after_many_push)
    TEST(new_stack_after_many_push_and_pop)
    TEST(stack_drain)
    TEST(stack_drain_null)
    TEST(stack_drain_half)
    TEST(stack_print)
    TEST(stack_is_lifo)
    TEST(drain_into_new_stack_copy)
    TEST(top_func_after_push_and_many_tops)
END_SUITE
