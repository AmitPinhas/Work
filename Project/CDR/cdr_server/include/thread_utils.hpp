#ifndef THREAD_UTILS_HPP
#define THREAD_UTILS_HPP

#include <sstream> // std::ostringstream
#include <vector>
#include "thread.hpp"

namespace advcpp
{

template <typename T, typename Generator>
void FillVector(std::vector<T>& a_vector, size_t a_nVector, Generator a_g, size_t a_nThread = 8);

template <typename T ,typename Generator>
class Fill : public IRunnable
{
public:
	typedef typename std::vector<T>::iterator iterator;
	
	Fill(iterator a_begin, iterator a_end, Generator a_generator);
	
	void Run() NOEXCEPT;

private:
	Generator m_generator;
	iterator m_begin;
	iterator m_end;
	
};

template <typename T, typename Generator>
Fill<T, Generator>::Fill(iterator a_begin, iterator a_end, Generator a_generator)
: m_generator(a_generator)
, m_begin(a_begin)
, m_end(a_end)
{
}

template <typename T, typename Generator>
void Fill<T, Generator>::Run() NOEXCEPT
{
	while(m_begin != m_end)
	{
		*m_begin = m_generator();
		++m_begin;
	}
}

template <typename T, typename Generator>
void FillVector(std::vector<T>& a_vector, size_t a_nVector, Generator a_g, size_t a_nThread)
{
	size_t jump = a_nVector/a_nThread ; 
	a_vector.resize(a_nVector);
	typename std::vector<T>::iterator begin = a_vector.begin();
	typename std::vector<T>::iterator end = a_vector.end();
	std::vector< Fill<T, Generator>* > fillVector;
	std::vector< Thread* > threadVector;
	size_t index = a_nThread-1;
	
	Fill<T, Generator> *fill = new Fill<T, Generator>(begin + (index * jump), end, a_g);
	fillVector.push_back(fill);
	
	while(index-- >0)
	{
		fill = new Fill<T, Generator>(begin + (index * jump), begin + ((index + 1) * jump), a_g);
		fillVector.push_back(fill);
	}
	
	index = a_nThread;
	
	while(index-- >0)
	{
		Thread *ptrThread = new Thread(fillVector[index]);
		threadVector.push_back(ptrThread);
	}	
	
	index = a_nThread;
	
	while(index-- > 0)
	{
		threadVector[index]->Join();
	}	
	
	index = a_nThread;
	while(index-- > 0)
	{
		delete fillVector[index];
		delete threadVector[index];		
	}

}

template <typename T>
std::string NumToStr( T a_num )
{
     std::ostringstream a_oStringStream;
     a_oStringStream << a_num;
     return a_oStringStream.str();
}

} // namespace advcpp

#endif // THREAD_UTILS_HPP
