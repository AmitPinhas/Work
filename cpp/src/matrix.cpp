#include <cstdio>	
#include <cassert>	

#include "matrix.hpp"
#include "utils.hpp"

Matrix::Matrix(size_t a_rows, size_t a_columns)
: m_dimension(a_rows, a_columns)
, m_elements( Alloc(a_rows, a_columns) ) 
{
}

Matrix::Matrix(size_t a_size)
: m_dimension(a_size, a_size)
, m_elements( Alloc(a_size, a_size) ) 
{
}

Matrix::Matrix(const Matrix &a_other) 
: m_dimension(a_other.Rows(), a_other.Columns())
, m_elements( Alloc(a_other.Rows(), a_other.Columns()) ) 
{
	Copy(a_other);
}

Matrix::~Matrix()
{
	delete[] m_elements;
}

Dimension Matrix::Dim() const
{
	Dimension tmp(Rows(), Columns()) ;	
	return tmp;
}

Matrix::ElemType Matrix::Get(size_t a_i, size_t a_j) const
{
	assert( InRange(a_i, a_j) );
	return *At(a_i, a_j);
}

void Matrix::Set(size_t a_i, size_t a_j, ElemType a_value)
{
	assert( InRange(a_i, a_j) );
	*(At(a_i, a_j)) = a_value;
}

void Matrix::Square()
{
	size_t n = Size() ;
	
	while(n-- > 0)
	{		
		m_elements[n] *= m_elements[n] ;
	}	
}

bool Matrix::operator==(const Matrix &a_rhs) const
{
	return EqualTo(a_rhs) ;
}

Matrix& Matrix::operator=(const Matrix &a_rhs) 
{
	Copy(a_rhs) ;
	return *this ;
}

Matrix& Matrix::operator=(ElemType a_scaler)
{
	Copy(a_scaler) ;
	return *this ;
}

Matrix Matrix::operator+(const Matrix &a_rhs) const
{
	Matrix sumMatrix(*this) ;	
	sumMatrix.Add(a_rhs) ;		
	return sumMatrix ;
}

Matrix Matrix::operator+(ElemType a_scaler) const
{
	Matrix sumMatrix(*this) ;	
	sumMatrix.Add(a_scaler) ;		
	return sumMatrix ;	
}

Matrix Matrix::operator-(const Matrix &a_rhs) const
{
	Matrix subMatrix(*this) ;	
	subMatrix.Sub(a_rhs) ;		
	return subMatrix ;
}

Matrix Matrix::operator-(ElemType a_scaler) const
{
	Matrix subMatrix(*this) ;	
	subMatrix.Sub(a_scaler) ;		
	return subMatrix ;	
}

Matrix Matrix::operator*(const Matrix &a_rhs) const
{
	Matrix mulMatrix(*this) ;	
	mulMatrix.Mul(a_rhs) ;		
	return mulMatrix ;
}

Matrix Matrix::operator*(ElemType a_scaler) const
{
	Matrix mulMatrix(*this) ;	
	mulMatrix.Mul(a_scaler) ;		
	return mulMatrix ;	
}

Matrix& Matrix::operator+=(const Matrix &a_rhs)
{
	Add(a_rhs) ;
	return *this ;
}

Matrix& Matrix::operator+=(ElemType a_scaler)
{
	Add(a_scaler) ;
	return *this ;	
}

Matrix& Matrix::operator-=(const Matrix &a_rhs)
{
	Sub(a_rhs) ;
	return *this ;
}

Matrix& Matrix::operator-=(ElemType a_scaler)
{
	Sub(a_scaler) ;
	return *this ;	
}

Matrix& Matrix::operator*=(const Matrix &a_rhs)
{
	Mul(a_rhs) ;
	return *this ;
}

Matrix& Matrix::operator*=(ElemType a_scaler)
{
	Mul(a_scaler) ;
	return *this ;	
}

Matrix& Matrix::operator/=(ElemType a_scaler)
{
	Div(a_scaler) ;
	return *this ;	
}

void Matrix::Copy(const Matrix &a_matrix)
{
	if ( IsNotSameSize(a_matrix) )
	{
		delete[] m_elements ;	
		m_elements = new ElemType[a_matrix.Rows() * a_matrix.Columns()]() ;
		m_dimension.Copy( a_matrix.m_dimension ) ;						
	}

	size_t n = Size() ;
	
	while(n-- > 0)
	{
		m_elements[n] = a_matrix.m_elements[n] ;
	}

}

void Matrix::Copy(ElemType a_scaler)
{
	size_t n = Size() ;
	
	while(n-- > 0)
	{
		m_elements[n] = a_scaler ;
	}
}


void Matrix::Transpose()
{
	if ( IsSquare() )
	{
		TransposeSquare();
		return ;
	}
	
	TransposeNotSquare();
}


void Matrix::Diagonal(ElemType a_value)
{
	assert ( IsSquare() ) ;
	
	int n = Rows() ;
	
	while ( n-- > 0 )
	{
		*At(n, n) = a_value ;
	}
}

void Matrix::Add(const Matrix &a_matrix)
{
	assert ( IsSameSize(a_matrix) ) ;
	
	size_t n = Size() ;
	
	while ( n-- > 0 )
	{
		m_elements[n] += a_matrix.m_elements[n] ;
	}
}

void Matrix::Add(ElemType a_scaler)
{	
	size_t n = Size() ;
	
	while ( n-- > 0 )
	{
		m_elements[n] += a_scaler ;
	}	
}

void Matrix::Sub(ElemType a_scaler)
{	
	size_t n = Size() ;
	
	while ( n-- > 0 )
	{
		m_elements[n] -= a_scaler ;
	}	
}

void Matrix::Sub(const Matrix &a_matrix)
{
	assert ( IsSameSize(a_matrix) ) ;
	
	size_t n = Size() ;
	
	while ( n-- > 0 )
	{
		m_elements[n] -= a_matrix.m_elements[n] ;
	}
}

void Matrix::Mul(ElemType a_scaler)
{	
	size_t n = Size() ;
	
	while ( n-- > 0 )
	{
		m_elements[n] *= a_scaler ;
	}	
}

void Matrix::Div(ElemType a_scaler)
{	
	size_t n = Size() ;
	
	while ( n-- > 0 )
	{
		m_elements[n] /= a_scaler ;
	}	
}

void Matrix::Mul(const Matrix &a_matrix)
{
	assert( CanBeMul(a_matrix) ) ;
	
	Matrix tmp( Rows(), a_matrix.Columns());
	
	const size_t rowsA = Rows() ;
	const size_t AcolumnsRowsB = Columns();
	const size_t columnsB = a_matrix.Columns();
	
	for ( size_t i = 0 ; i < rowsA ; ++i )
	{	
		for ( size_t z = 0 ; z < columnsB ; ++z )
		{
			ElemType sum = 0 ;	
			
			for ( size_t j = 0 ; j < AcolumnsRowsB ; ++j )
			{
				ElemType a = Get(i,j) ;
				ElemType b = a_matrix.Get(j,z) ;
				sum += a*b ;
			}
			
			tmp.Set( i, z, sum) ;
		}
	}	
	
	Copy(tmp) ;
	
}

void Matrix::Print() const
{
	const size_t r = Rows();
	const size_t c = Columns();
	
	printf("Matrix %ldX%ld :\n" , r, c); 
		
	for ( size_t i = 0 ; i < r ; ++i )
	{
		printf("{ ");
		for ( size_t j = 0 ; j < c ; ++j )
		{
			printf("%.2f ", *At(i, j));
		}	
		printf("}\n");
	}
}

bool Matrix::CanBeMul(const Matrix &a_rhs) const
{
	return Columns() == a_rhs.Rows() ;
}

bool Matrix::EqualTo(const Matrix &a_rhs) const
{
	if( IsNotSameSize(a_rhs) )
	{
		return 0 ;
	}
	
	size_t n = Size() ;
	
	while ( n-- > 0 )
	{
		if ( m_elements[n] != a_rhs.m_elements[n] )
		{
			return 0 ;
		}
	}
	
	return 1 ;	
}


void Matrix::TransposeSquare()
{
	const size_t n = Rows() ;
	
	for ( size_t i = 0 ; i < n ; ++i )
	{
		for ( size_t j = i+1 ; j < n ; ++j )
		{
			Swap( *At(i,j) , *At(j,i) );
		}
	}	
}

void Matrix::TransposeNotSquare()
{
	const size_t n = Size();
	const size_t r = Rows();
	const size_t c = Columns();
	
	for ( size_t start = 0 ; start < n ; ++start )
	{
		size_t next = start ;
		size_t i = 0 ;
		do
		{
			++i;
			next = (next % r) * c + next / r;
		} while ( next > start ) ;
		
		if ( next >= start && i != 1)
		{
			const double tmp = m_elements[start];
			next = start;
			do
			{
				i = (next % r) * c + next / r;
				m_elements[next] = ( i == start ) ? tmp : m_elements[i];
				next = i ;
			} while ( next > start );
		}	
	}
	
	m_dimension.Transfer( m_dimension ) ;	
	
	return ;
}

inline bool Matrix::IsSameSize(const Matrix &a_rhs) const
{
	return Rows() == a_rhs.Rows() && Columns() == a_rhs.Columns() ; 
}


inline bool Matrix::IsNotSameSize(const Matrix &a_rhs) const
{
	return Rows() != a_rhs.Rows() || Columns() != a_rhs.Columns() ;
}


inline size_t Matrix::Size() const
{
	return Rows() * Columns() ;
}

Matrix::ElemType* Matrix::Alloc(size_t a_rows, size_t a_columns)
{
	assert( a_rows > 0 && a_columns > 0 ) ;
	
	return new ElemType[ a_rows * a_columns ]();	
}

bool Matrix::IsSquare() const 
{
	return Rows() == Columns() ;
}

inline Matrix::ElemType* Matrix::At(size_t a_i, size_t a_j) const
{
    return m_elements + a_i * m_dimension.m_columns + a_j;
}

inline size_t Matrix::Rows() const
{
    return m_dimension.m_rows;
}

inline size_t Matrix::Columns() const
{
    return m_dimension.m_columns;
}

inline bool Matrix::InRange(size_t a_i, size_t a_j) const
{
    return a_i < Rows() && a_j < Columns();
}

