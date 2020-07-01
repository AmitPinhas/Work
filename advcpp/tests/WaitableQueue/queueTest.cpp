#include "mu_test.h"
#include <vector>
#include "waitable_queue.hpp"
#include "thread.hpp"

const size_t sizeQ = 42424242;

template <typename T>
class Producer : public advcpp::IRunnable
{
public:
	Producer(advcpp::WaitableQueue<T>& a_queue, size_t a_start, size_t a_end);

	~Producer() NOEXCEPT;

	void Run() NOEXCEPT;

private:
	advcpp::WaitableQueue<T>& m_queue;
	size_t m_start;
	size_t m_end;
};

template <typename T>
Producer<T>::Producer(advcpp::WaitableQueue<T>& a_queue, size_t a_start, size_t a_end)
: m_queue(a_queue)
, m_start(a_start)
, m_end(a_end)
{
}

template <typename T>
Producer<T>::~Producer() NOEXCEPT
{
}

template <typename T>
void Producer<T>::Run() NOEXCEPT
{
	for(;m_start < m_end; ++m_start)
	{
		m_queue.Enqueue(m_start);
	}
}

template <typename T>
class Consumer : public advcpp::IRunnable
{
public:
	Consumer(advcpp::WaitableQueue<T>& a_queue, size_t a_start, size_t a_end);

	~Consumer() NOEXCEPT;

	void Run() NOEXCEPT;

	std::vector<T>& Vector();

private:
	advcpp::WaitableQueue<T>& m_queue;
	size_t m_start;
	size_t m_end;
	std::vector<T> m_vector;
};

template <typename T>
Consumer<T>::Consumer(advcpp::WaitableQueue<T>& a_queue, size_t a_start, size_t a_end)
: m_queue(a_queue)
, m_start(a_start)
, m_end(a_end)
{
}

template <typename T>
Consumer<T>::~Consumer() NOEXCEPT
{
}

template <typename T>
void Consumer<T>::Run() NOEXCEPT
{
	for(;m_start < m_end; ++m_start)
	{
		T i;
		m_queue.Dequeue(i);
		m_vector.push_back(i);
	}
}

template <typename T>
std::vector<T>& Consumer<T>::Vector()
{
	return m_vector;
}

UNIT(queue_one_thread)
	advcpp::WaitableQueue<size_t> queue(sizeQ);
	size_t index = sizeQ;
	while(index-- >0)
	{
		queue.Enqueue(index);
	}

	index = sizeQ;

	while(index-- >0)
	{
		size_t i;
		queue.Dequeue(i);
		ASSERT_THAT(i == index);
	}

END_UNIT

UNIT(queue_two_thread)
	advcpp::WaitableQueue<size_t> queue(sizeQ);

	Producer<size_t> pro(queue, 0, sizeQ);
	Consumer<size_t> con(queue, 0, sizeQ);

	advcpp::Thread proThread(&pro);
	advcpp::Thread conThread(&con);

	proThread.Join();
	conThread.Join();

	std::vector<size_t> vec = con.Vector();

	for(size_t i = 0; i < sizeQ ; ++i)
	{
		ASSERT_THAT(vec[i] == i);
	} 

END_UNIT

UNIT(queue_two_producer)
	advcpp::WaitableQueue<size_t> queue(sizeQ);

	Producer<size_t> pro(queue, 0, sizeQ/2);
	Producer<size_t> pro2(queue, sizeQ/2, sizeQ);
	Consumer<size_t> con(queue, 0, sizeQ);

	advcpp::Thread proThread(&pro);
	advcpp::Thread pro2Thread(&pro2);
	advcpp::Thread conThread(&con);

	proThread.Join();
	pro2Thread.Join();
	conThread.Join();

	std::vector<size_t> vec = con.Vector();

	for(size_t i = 0,  s = sizeQ/2,  index = 0; index < sizeQ ; ++index)
	{
		if(vec[index] == i)
		{
			++i;
		}
		else if(vec[index] == s)
		{
			++s;
		}
		else
		{
			ASSERT_FAIL("error");
		}
	} 
	ASSERT_PASS();

END_UNIT

UNIT(queue_two_consumer)
	advcpp::WaitableQueue<size_t> queue(sizeQ);

	Producer<size_t> pro(queue, 0, sizeQ);
	Consumer<size_t> con(queue, 0, sizeQ/2);
	Consumer<size_t> con2(queue, sizeQ/2, sizeQ);

	advcpp::Thread proThread(&pro);
	advcpp::Thread conThread(&con);
	advcpp::Thread con2Thread(&con2);

	proThread.Join();
	conThread.Join();
	con2Thread.Join();

	std::vector<size_t> vec = con.Vector();
	std::vector<size_t> vecSec = con2.Vector();

	size_t index = 0;
	for(size_t i = 0, j = 0; index < sizeQ ; ++index)
	{
		if(vec[i] == index)
		{
			++i;
		}
		else if(vecSec[j] == index)
		{
			++j;
		}
		else
		{
			ASSERT_FAIL("error");
		}
	} 
	ASSERT_THAT(index == sizeQ);

END_UNIT

UNIT(queue_two_two)
	advcpp::WaitableQueue<size_t> queue(sizeQ);

	Producer<size_t> pro(queue, 0, sizeQ/2);
	Producer<size_t> pro2(queue, sizeQ/2, sizeQ);
	Consumer<size_t> con(queue, 0, sizeQ/2);
	Consumer<size_t> con2(queue, sizeQ/2, sizeQ);

	advcpp::Thread proThread(&pro);
	advcpp::Thread pro2Thread(&pro2);
	advcpp::Thread conThread(&con);
	advcpp::Thread con2Thread(&con2);

	proThread.Join();
	pro2Thread.Join();
	conThread.Join();
	con2Thread.Join();

	std::vector<size_t> vec = con.Vector();
	std::vector<size_t> vecSec = con2.Vector();

	size_t index = 0;
	size_t indexSecond = sizeQ/2;
	for(size_t i = 0, j = 0; index < sizeQ/2 || indexSecond < sizeQ ; )
	{
		if(vec[i] == index || vec[i] == indexSecond)
		{
			if(vec[i] == index)
			{
				++index;
			}
			else
			{
				++indexSecond;
			}
			++i;
		}
		else if(vecSec[j] == index || vecSec[j] == indexSecond)
		{
			if(vecSec[j] == index)
			{
				++index;
			}
			else
			{
				++indexSecond;
			}		
			++j;
		}
		else
		{
			ASSERT_FAIL("error");
		}
	} 
	ASSERT_THAT(index == sizeQ/2);
	ASSERT_THAT(indexSecond == sizeQ);	
	
END_UNIT

UNIT(three_three)
	advcpp::WaitableQueue<size_t> queue(sizeQ);

	Producer<size_t> pro(queue, 0, sizeQ/3);
	Producer<size_t> pro2(queue, sizeQ/3, sizeQ - sizeQ/3);
	Producer<size_t> pro3(queue, sizeQ - sizeQ/3, sizeQ);
	Consumer<size_t> con(queue, 0, sizeQ/3);
	Consumer<size_t> con2(queue, sizeQ/3, sizeQ - sizeQ/3);
	Consumer<size_t> con3(queue, sizeQ - sizeQ/3, sizeQ);

	advcpp::Thread proThread(&pro);
	advcpp::Thread pro2Thread(&pro2);
	advcpp::Thread pro3Thread(&pro3);	
	advcpp::Thread conThread(&con);
	advcpp::Thread con2Thread(&con2);
	advcpp::Thread con3Thread(&con3);	

	proThread.Join();
	pro2Thread.Join();
	pro3Thread.Join();	
	conThread.Join();
	con2Thread.Join();
	con3Thread.Join();	

	std::vector<size_t> vec = con.Vector();
	std::vector<size_t> vecSec = con2.Vector();
	std::vector<size_t> vecTh = con3.Vector();	

	size_t index = 0;
	size_t indexSecond = sizeQ/3;
	size_t indexThree = sizeQ - sizeQ/3;
	for(size_t i = 0, j = 0, k = 0; index < sizeQ/3 || indexSecond < sizeQ - sizeQ/3 || indexThree < sizeQ; )
	{
		if(vec[i] == index || vec[i] == indexSecond || vec[i] == indexThree)
		{
			if(vec[i] == index)
			{
				++index;
			}
			else if(vec[i] == indexSecond) 
			{
				++indexSecond;
			}
			else
			{
				++indexThree;
			}
			++i;
		}
		else if(vecSec[j] == index || vecSec[j] == indexSecond || vecSec[j] == indexThree)
		{
			if(vecSec[j] == index)
			{
				++index;
			}
			else if(vecSec[j] == indexSecond) 
			{
				++indexSecond;
			}
			else
			{
				++indexThree;
			}		
			++j;
		}
		else if(vecTh[k] == index || vecTh[k] == indexSecond || vecTh[k] == indexThree)
		{
			if(vecTh[k] == index)
			{
				++index;
			}
			else if(vecTh[k] == indexSecond) 
			{
				++indexSecond;
			}
			else
			{
				++indexThree;
			}		
			++k;
		}		
		else
		{
			ASSERT_FAIL("error");
		}
	} 
	ASSERT_THAT(index == sizeQ/3);
	ASSERT_THAT(indexSecond == sizeQ - sizeQ/3);	
	ASSERT_THAT(indexThree == sizeQ);		
	
END_UNIT

TEST_SUITE(test the queue on fire)

	TEST(queue_one_thread)
	TEST(queue_two_thread)
	TEST(queue_two_producer)
	TEST(queue_two_consumer)
	TEST(queue_two_two)
	TEST(three_three)	

END_SUITE
