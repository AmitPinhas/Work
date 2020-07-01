#include <cstdio>
#include "stack.hpp"

static void TestCapacity();
static void TestSize();
static void TestPushPop();
static void TestDrain();
static void PrintResult(int _res);


static char g_pass[] = "Pass" ;
static char g_failed[] = "Failed" ;

int main()
{
	TestCapacity();
	TestSize();
	TestPushPop();
	TestDrain();
	return 0 ;
}

static void TestCapacity()
{
	Stack s ;
	int i = 0;
	size_t size = 64;
	while(size-- > 0){
		s.Push(i++);
	}
	s.Push(666);
	PrintResult(s.Pop() != 666);
	
	return ;
}


static void TestSize()
{
	Stack s ;
	int i = 0 ;
	size_t size = 60, sizeReturn;
	while(size-- > 0){
		s.Push(i++);
	}

	sizeReturn = s.Size() ;
	
	PrintResult(sizeReturn == 60);	
	
	return ;
}


static void TestPushPop()
{
	size_t size ;
	int pop , result ;
	Stack s ;
	
	s.Push(5) ;
	size	=	s.Size();
	pop = s.Pop() ;
	
	result = ( ( pop == 5 ) && ( size == 1 ) ) ;
	
	PrintResult( result ) ;
	
	return;	
}




static void TestDrain()
{
	Stack s1, s2 ;
	
	s1.Push(5) ;	
	s1.Push(4) ;
	s1.Push(3) ;
	s1.Push(2) ;
	s1.Push(1) ;
		
	s1.Print() ;
	
	s2.Drain(&s1) ;
	
	s2.Print();
	s1.Print();				
}


static void PrintResult(int _res)
{
	if ( _res )
	{
		puts(g_pass);
	}
	else
	{
		puts(g_failed);
	}
	
	return ;
}
