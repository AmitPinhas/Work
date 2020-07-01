#include <iostream> // std::cout
#include <vector>
#include <cstdlib>     // srand, rand 
#include <ctime>       // time 
#include <cstdlib>     // atoi 
#include "mutex.hpp"
#include "mutex_exception.hpp"

struct IteratorsMutex
{
	std::vector<int>::iterator m_begin;
	std::vector<int>::iterator m_end;	
	advcpp::Mutex* m_mutex;
};

void* AverageCalculation(void* a_context);

static int g_sum = 0;

static std::vector<int> g_vector;

const static size_t numThreads = 4;

int main(int , char* argv[])
{
	srand (time(NULL));

	double sizeVector = atoi(argv[1]);
	
	g_vector.resize(sizeVector);
	
	size_t index = sizeVector;
	
	while(index-- >0)
	{
		g_vector[index] = rand() % 10;
	}
	
	index = sizeVector;
	
	while(index-- >0)
	{
		std::cout << g_vector[index] << " ";
	}
	
	std::cout << '\n';	
	
	size_t jump = sizeVector/4;
	
	IteratorsMutex iteartosMutex[4];
	
	index = numThreads;
	
	while(index-- >0)
	{
		iteartosMutex[index].m_begin = g_vector.begin() + (index * jump);
		iteartosMutex[index].m_end = g_vector.begin() + ((index + 1) * jump);
	}

	iteartosMutex[numThreads-1].m_end = g_vector.end();
	
	pthread_t threads[4];
	
	try
	{
		advcpp::Mutex mutex;
		
		iteartosMutex[0].m_mutex = &mutex;
		iteartosMutex[1].m_mutex = &mutex;
		iteartosMutex[2].m_mutex = &mutex;
		iteartosMutex[3].m_mutex = &mutex;
		
		size_t indexThreads = numThreads;
		
		while(indexThreads-- >0)
		{
			pthread_create(&threads[indexThreads], NULL, AverageCalculation, &iteartosMutex[indexThreads]);
		}
		
		indexThreads = numThreads;
		
		while(indexThreads-- >0)
		{
			pthread_join(threads[indexThreads], NULL);
		}
	}

	catch(const advcpp::MutexException& a_mutexException)
	{
		std::cout << a_mutexException.what();
	}

	std::cout << "the sum is : " << g_sum << '\n' ;		
	std::cout << "the average is : " << g_sum/sizeVector << '\n' ;	
	
	return 0;
}

void* AverageCalculation(void* a_context)
{
	IteratorsMutex* iteratorsMutex = static_cast<IteratorsMutex*>(a_context);
	std::vector<int>::iterator begin = iteratorsMutex-> m_begin;
	std::vector<int>::iterator end = iteratorsMutex-> m_end;	
	advcpp::Mutex* mutex = iteratorsMutex -> m_mutex;
	
	while(begin != end)
	{
		mutex->Lock();
		
		g_sum += *begin;
		++begin;
		
		mutex->UnLock();
	}
	
	pthread_exit(a_context);
}
