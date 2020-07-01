#include <iostream> // std::cout
#include <cstdlib>     // atoi 
#include <ctime>      // clock 
#include "mutex.hpp"
#include "mutex_exception.hpp"

struct Context
{
	advcpp::Mutex* m_mutex;
	size_t m_rounds;
};

void* Increase(void* a_context);
void* Substruct(void* a_context);

static int g_num = 0;

int main(int , char* argv[])
{
	int status;
	pthread_t add;	
	pthread_t sub;
	
	Context contexts[2];
	
	try
	{
		advcpp::Mutex mutex;
		
		contexts[0].m_mutex = &mutex;
		contexts[0].m_rounds = atoi(argv[1]);	
		contexts[1].m_mutex = &mutex;
		contexts[1].m_rounds = atoi(argv[1]);	
		
		clock_t t1 = clock();		
		
		status = pthread_create(&add, NULL, Increase, &contexts[0]);
		if(status)
		{
			std::cout << "\nERROR " << status;
		}
	
		status = pthread_create(&sub, NULL, Substruct, &contexts[1]);
		if(status)
		{
			std::cout << "\nERROR " << status;
		}
	
		pthread_join(add, NULL);
		pthread_join(sub, NULL);
		
		t1 = clock()-t1 ;
		
		double time = static_cast<double>(t1)/ CLOCKS_PER_SEC;
		
		std::cout << "time: " << time << '\n';		

	}
	
	catch(const advcpp::MutexException& a_mutexException)
	{
		std::cout << a_mutexException.what();
	}
	
	std::cout << "global num is : " << g_num << '\n' ;	
}

void * Increase(void* a_context)
{
	Context *context = static_cast<Context*>(a_context);
	for ( size_t i = 0; i < context->m_rounds; ++i )
	{
		context->m_mutex->Lock();
		++g_num;
		context->m_mutex->UnLock();
	}
	
	pthread_exit(a_context);
}

void * Substruct(void * a_context)
{
	Context *context = static_cast<Context*>(a_context);
	for ( size_t i = 0; i < context->m_rounds; ++i )
	{
		context->m_mutex->Lock();
		--g_num;
		context->m_mutex->UnLock();
	}
	
	pthread_exit(a_context);
}




