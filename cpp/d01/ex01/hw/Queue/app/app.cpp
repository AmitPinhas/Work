#include "mu_test.h"

#include "queue.hpp"

UNIT(new_queue_is_empty)
    Queue q;
    ASSERT_EQUAL(q.Size(), 0);
    ASSERT_EQUAL(q.Capacity() , 128 );
END_UNIT

UNIT(new_queue_is_full)
    Queue q;
    int n = 128 ;
    while(n-- > 0)
    {
    	q.EnQueue( n ) ;
    } 
    ASSERT_EQUAL(q.Size(), 128);
    ASSERT_EQUAL(q.Capacity() , 128 );
END_UNIT

UNIT(new_queue_many_en)
    Queue q;
    int n = 89 ;
    while(n-- > 0)
    {
    	q.EnQueue( n ) ;
    } 
    ASSERT_EQUAL(q.Size(), 89);
    ASSERT_EQUAL(q.Capacity() , 128 );
END_UNIT

UNIT(new_queue_after_many_en_and_de)
    Queue q;
    int n = 53, n2 = 20 ;
    while(n-- > 0 )
    {
    	q.EnQueue( n ) ;
    }
    while(n2-- > 0 )
    {
    	q.DeQueue() ;
    }    
    
    ASSERT_EQUAL(q.Size(), 33);
    ASSERT_EQUAL(q.Capacity() , 128 );
END_UNIT


UNIT(queue_print)
    Queue q;
    int n = 128, n2 = 20 ;
    while(n-- > 0 )
    {
    	q.EnQueue( n ) ;
    }
    while(n2-- > 0 )
    {
    	q.DeQueue() ;
    }    
    
	q.Print();
	
	ASSERT_PASS();
	
END_UNIT

UNIT(queue_is_fifo)
    Queue q;
    q.EnQueue(42);
    q.EnQueue(888);
    q.EnQueue(999);
    ASSERT_EQUAL(q.DeQueue(), 42);
    ASSERT_EQUAL(q.DeQueue(), 888);
    ASSERT_EQUAL(q.DeQueue(), 999);
    
    ASSERT_EQUAL( q.Size(), 0 ) ;
    
END_UNIT


UNIT(queue_is_fifo2)
    Queue q;
    q.EnQueue(42);
    ASSERT_EQUAL(q.DeQueue(), 42);    
    q.EnQueue(888);
    q.EnQueue(999);
    ASSERT_EQUAL(q.DeQueue(), 888);
    ASSERT_EQUAL(q.DeQueue(), 999);
    q.EnQueue(1);
    q.EnQueue(2);
    q.EnQueue(3);
    q.EnQueue(4); 
    ASSERT_EQUAL(q.DeQueue(), 1);           
    
    ASSERT_EQUAL( q.Size(), 3 ) ;
    
END_UNIT

UNIT(test_enqueue_when_state_is_fron_full_back_not_full)
    Queue q;
    size_t size = q.Capacity();

    TRACER << "hello world\n";
    TRACER << "cap: " << q.Capacity() << " size: " << q.Size() << '\n';

    for (size_t i = 0; i < size/2; ++i)
    {
        q.EnQueue(i);
    }
        
    ASSERT_EQUAL(q.DeQueue(), 0);
    ASSERT_EQUAL(q.DeQueue(), 1);
    ASSERT_EQUAL(q.DeQueue(), 2);
    
    for (size_t i = 64; i < size; ++i)
    {
        q.EnQueue(i);
    }
    
    q.EnQueue(7777);
    q.EnQueue(8888);
    q.EnQueue(9999);

    ASSERT_THAT(q.IsFull());
    for (size_t i = 0; i < size-3; ++i)
    {
        ASSERT_EQUAL(q.DeQueue(), (int)i+3);
    }
    
    ASSERT_EQUAL(q.DeQueue(), 7777);
    ASSERT_EQUAL(q.DeQueue(), 8888);
    ASSERT_EQUAL(q.DeQueue(), 9999);
    
END_UNIT


UNIT(is_empty_true)
    Queue q;
    
    ASSERT_EQUAL( q.IsEmpty(), 1 ) ;
    
END_UNIT


UNIT(is_empty_false)
    Queue q;
    q.EnQueue(7777);    
    ASSERT_EQUAL( q.IsEmpty(), 0 ) ;
    
END_UNIT


UNIT(first_not_full_push_b_empty_pop)
    Queue q;
    int i = 64 , j = 64 ;
    while (i-- > 0)
    {
		q.EnQueue(i);     	
    }
    
    ASSERT_EQUAL( q.IsEmpty(), 0 ) ;
    ASSERT_EQUAL( q.IsNotEmpty(), 1 );
        
    while( j-- > 0 )
    {
    	ASSERT_EQUAL( q.DeQueue(), j);
    }

    ASSERT_EQUAL( q.IsEmpty(), 1 );             
    ASSERT_EQUAL( q.IsNotEmpty(), 0 );
        	
END_UNIT


UNIT(loop_pop_after_push)
    Queue q;
    int i = 128 ;
    while (i-- > 0)
    {
		q.EnQueue(i);  
    	ASSERT_EQUAL( q.DeQueue(), i);		   	
    }
    
END_UNIT


TEST_SUITE(test the queue on fire)
    TEST(test_enqueue_when_state_is_fron_full_back_not_full)
    TEST(new_queue_is_empty)
    TEST(new_queue_is_full)
    TEST(new_queue_many_en)
    TEST(new_queue_after_many_en_and_de)
    TEST(queue_print)
    TEST(queue_is_fifo)
    TEST(queue_is_fifo2)
    TEST(is_empty_true)
    TEST(is_empty_false)
    TEST(first_not_full_push_b_empty_pop)
    TEST(loop_pop_after_push)
END_SUITE


