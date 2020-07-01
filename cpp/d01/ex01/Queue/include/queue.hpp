#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stddef.h>
#include "stack.hpp"

class Queue {
public:
	void	EnQueue(int a_num);
	int		DeQueue();
	size_t	Size();
	size_t	Capacity();
	void	Print();
		
private:
	Stack	m_master ;	
	Stack	m_tmp ;
};

#endif /* QUEUE_HPP */
