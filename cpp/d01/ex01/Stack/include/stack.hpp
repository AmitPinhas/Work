#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

class Stack {
public:
	Stack();

	void	Push(int a_num);
	int		Pop();
	size_t	Drain(Stack *a_s);
	
	size_t	Size();
	size_t	Capacity();
	
	void	Print();		
private:
	static const size_t CAPACITY = 64;	
	int				m_data[CAPACITY] ;	
	unsigned int	m_tos ;
};

#endif /* STACK_HPP */
