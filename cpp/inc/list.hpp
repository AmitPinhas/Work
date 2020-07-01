#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>	/* size_t , cout , endl */
#include "node.hpp"

template< typename T = int >
class List
{
public:

	List();
	List(const List &a_other);
	~List();
	
	List& operator=(const List &a_rhs);

	void PushHead(const T &a_data);
	void PushTail(const T &a_data);
	void PushTail(const List &a_other);
		
	T& Head() const;
	T& Tail() const;
	
	T* Find(T const& a_data);
	const T* Find(T const& a_data) const;
	bool Find(T const& a_data, T& a_found);
	
	T PopHead();
	T PopTail();
	
	void Clear();
	size_t Remove(const T &a_data);
	
	bool IsEmpty() const;
	size_t Size() const;	
	
	void Print() const;
	
private:
	void Push(Node<T> &a_reff ,Node<T> &a_NewNode);	
	Node<T>* Pop( Node<T> &a_reff);
	void InitHead();
	void InitTail();
	void DeleteNode(Node<T> **a_node);
	void ClearData();

private:
	Node<T> m_head;
 	Node<T> m_tail;
};

template< typename T >
List<T>::List()
: m_head(&m_head, &m_tail)
, m_tail(&m_head, &m_tail)
{
}

template< typename T >
List<T>::List(const List &a_other)
: m_head(&m_head, &m_tail)
, m_tail(&m_head, &m_tail)  
{
	PushTail(a_other);
}

template< typename T >
List<T>& List<T>::operator=(const List &a_rhs)
{
	Clear();		
	PushTail(a_rhs);
	return *this;	
}

template< typename T >
List<T>::~List()
{
	ClearData();	
}

template< typename T >
void List<T>::PushHead(const T &a_data)
{
	Node<T> *node = new Node<T>(a_data);
	Push( *(m_head.Next()), *node );
}

template< typename T >
T List<T>::PopHead()
{	
	Node<T> *nodeDelete = Pop( *(m_head.Next()) );	
	T data = nodeDelete->Data();	
	delete nodeDelete;	
	return data;
}

template< typename T >
T List<T>::PopTail()
{
	Node<T> *nodeDelete = Pop( *(m_tail.Prev()) );	
	T data = nodeDelete->Data();	
	delete nodeDelete;	
	return data;
}

template< typename T >
void List<T>::PushTail(const T &a_data)
{
	Node<T> *node = new Node<T>(a_data);
	Push( m_tail, *node );
}

template< typename T >
void List<T>::Push(Node<T> &a_reff ,Node<T> &a_NewNode)
{
     a_NewNode.Prev(*(a_reff.Prev()));
     a_NewNode.Next(a_reff);
     a_reff.Prev()->Next(a_NewNode);
     a_reff.Prev(a_NewNode);
}	

template< typename T >
Node<T>* List<T>::Pop( Node<T> &a_reff)
{
	a_reff.Next()->Prev(*(a_reff.Prev()));
	a_reff.Prev()->Next(*(a_reff.Next()));	
	return &a_reff;
}

template< typename T >
T& List<T>::Head() const
{
	return m_head.Next()->Data();
}

template< typename T >
T& List<T>::Tail() const
{
	return m_tail.Prev()->Data();
}

template< typename T >
size_t List<T>::Size() const
{
	size_t size = 0;
	Node<T> *tmpNode = m_head.Next();
	
	while ( tmpNode != &m_tail )
	{
		++size;
		tmpNode = tmpNode->Next();
	}
	return size;
}

template< typename T >
T* List<T>::Find(T const& a_data)
{
	Node<T> *tmpNode = m_head.Next();
	
	while ( tmpNode != &m_tail )
	{
		if (tmpNode->Data() == a_data)
		{
			return &(tmpNode->Data());
		}		
		tmpNode = tmpNode->Next();
	}
	return 0;
}

template< typename T >
const T* List<T>::Find(T const& a_data) const
{
	Node<T> *tmpNode = m_head.Next();
	
	while ( tmpNode != &m_tail )
	{
		if (tmpNode->Data() == a_data)
		{
			return &(tmpNode->Data());
		}		
		tmpNode = tmpNode->Next();
	}
	return 0;
}

template< typename T >
bool List<T>::Find(T const& a_data, T& a_found)
{
	Node<T> *tmpNode = m_head.Next();
	
	while ( tmpNode != &m_tail )
	{
		if (tmpNode->Data() == a_data)
		{
			return true;
		}		
		tmpNode = tmpNode->Next();
	}
	return false;	
}

template< typename T >
size_t List<T>::Remove(const T &a_data)
{	
	if ( 0 == Find(a_data))
	{
		return 0 ;
	}
	
	size_t size = 0;
	Node<T> *tmpNode = m_head.Next();
	
	while ( tmpNode != &m_tail )
	{
		if (tmpNode->Data() == a_data)
		{
			DeleteNode(&tmpNode);
			++size;
		}
		tmpNode = tmpNode->Next();
	}	
	return size;		
}

template< typename T >
void List<T>::Print() const
{
	Node<T> *tmpNode = m_head.Next();
	while ( tmpNode != &m_tail )
	{
		std::cout << tmpNode->Data() << ' ' ;
		tmpNode = tmpNode->Next();
	}
	std::cout << std::endl ;
}

template< typename T >
void List<T>::InitHead()
{
	m_head.Next( m_tail );
	m_head.Prev( m_head );
}

template< typename T >
void List<T>::InitTail()
{
	m_tail.Next( m_tail );
	m_tail.Prev( m_head );		
}

template< typename T >
void List<T>::PushTail(const List &a_other)
{
	Node<T> *current = a_other.m_head.Next() ;
	Node<T> *end = a_other.m_tail.Next();
	
	while ( current != end )
	{
		PushTail( current->Data() );
		current = current->Next();
	}
}

template< typename T >
void List<T>::Clear()
{
	ClearData();
	m_head.Next(m_tail);
	m_tail.Prev(m_head);	
}

template< typename T >
void List<T>::DeleteNode(Node<T> **a_node)
{
	Node<T> *removeNode = *a_node;
	*a_node = (*a_node)->Prev();
	Pop( *removeNode );
	delete removeNode; 	
}

template< typename T >
bool List<T>::IsEmpty() const
{
	if ( m_head.Next() == &m_tail )
	{
		return true;
	}
	return false;
}

template <typename T>
void List<T>::ClearData()
{
	Node<T>* p = m_head.Next();
	while (p != &m_tail )
	{
		Node<T>* q = p;
		p = p->Next();
		delete q;
	}
}

#endif /* LIST_HPP */
