#ifndef NODE_HPP
#define NODE_HPP

template< typename T >
// T: default ctor
class Node
{
public:
	Node(T a_data, Node* a_prev = 0, Node* a_next = 0);
	Node(Node *a_prev = 0, Node *a_next = 0);
	
	void Next(Node &a_node);
	Node* Next() const;
	
	void Prev(Node &a_node);
	Node* Prev() const;	
	
	void Data(T a_data);
	const T& Data() const;
	T& Data();

private:
	T m_data;
	Node *m_next;
	Node *m_prev;
};

template< typename T >
Node<T>::Node(T a_data, Node* a_prev, Node* a_next)
: m_data(a_data)
, m_next(a_next)
, m_prev(a_prev)
{
}

template< typename T >
Node<T>::Node(Node *a_prev, Node *a_next)
: m_next(a_next)
, m_prev(a_prev)
{
}

template< typename T >
void Node<T>::Next(Node &a_node)
{
	m_next = &a_node;
}

template< typename T >
Node<T>* Node<T>::Next() const
{
	return m_next;
}


template< typename T >
void Node<T>::Prev(Node &a_node)
{
	m_prev = &a_node;
}

template< typename T >
Node<T>* Node<T>::Prev() const
{
	return m_prev;
}

template< typename T >
void Node<T>::Data(T a_data)
{
	m_data = a_data;
}

template< typename T >
T& Node<T>::Data() 
{
	return m_data;
}

template< typename T >
const T& Node<T>::Data() const
{
	return m_data;
}

#endif /* NODE_HPP */


