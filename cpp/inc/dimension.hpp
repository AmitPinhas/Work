#ifndef DIMENSION_HPP
#define DIMENSION_HPP

#include <cstddef>

struct Dimension
{
    Dimension(size_t a_rows, size_t a_columns);
    void Copy( Dimension a_other ) ;
    void Transfer( Dimension a_other ) ;
    size_t m_rows;
    size_t m_columns;
};

inline void Dimension::Copy( Dimension a_other ) 
{
	m_rows = a_other.m_rows ;
	m_columns = a_other.m_columns ;
}

inline void Dimension::Transfer( Dimension a_other ) 
{
	m_rows = a_other.m_columns ;
	m_columns = a_other.m_rows ;
}

#endif /* DIMENSION_HPP */
