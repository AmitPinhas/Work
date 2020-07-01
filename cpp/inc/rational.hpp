#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstdio>
#include <cassert>

template< typename T = int >
class Rational
{
public:
	Rational(T a_numerator = 0, T a_denumerator = 1);
	
	double Value() const;
	T Numerator() const;
	T Denumerator() const;
	
	Rational operator+=(const Rational &a_rhs);
	Rational operator+=(T a_scaler);
	Rational operator-=(const Rational &a_rhs);
	Rational operator-=(T a_scaler);
	Rational operator*=(const Rational &a_rhs);
	Rational operator*=(T a_scaler);
	Rational operator/=(const Rational &a_rhs);
	Rational operator/=(T a_scaler);
	

private:
	void Add(const Rational &a_rhs);
	void Add(T a_scaler);
	void Sub(const Rational &a_rhs);
	void Sub(T a_scaler);
	void Mul(const Rational &a_rhs);
	void Mul(T a_scaler);
	void Div(const Rational &a_rhs);
	void Div(T a_scaler);
	
private:
	T m_numerator;
	T m_denumerator;
};


template< typename T >
Rational<T>::Rational(T a_numerator, T a_denumerator)
: m_numerator( a_numerator )
, m_denumerator( a_denumerator )
{
	assert( a_denumerator != 0 );
}

template< typename T >
double Rational<T>::Value() const
{
	return (double)m_numerator/m_denumerator;
}

template< typename T >
T Rational<T>::Numerator() const
{
	return m_numerator;
}

template< typename T >
T Rational<T>::Denumerator() const
{
	return m_denumerator;
}

template< typename T >
Rational<T> Rational<T>::operator+=(const Rational &a_rhs)
{
	Add(a_rhs);
	return *this;
}

template< typename T >
Rational<T> Rational<T>::operator+=(T a_scaler)
{
	Add(a_scaler);
	return *this;	
}

template< typename T >
Rational<T> Rational<T>::operator-=(T a_scaler)
{
	Sub(a_scaler);
	return *this;	
}

template< typename T >
Rational<T> Rational<T>::operator-=(const Rational &a_rhs)
{
	Sub(a_rhs);
	return *this;
}

template< typename T >
Rational<T> Rational<T>::operator*=(const Rational &a_rhs)
{
	Mul(a_rhs);
	return *this;
}

template< typename T >
Rational<T> Rational<T>::operator*=(T a_scaler)
{
	Mul(a_scaler);
	return *this;	
}

template< typename T >
Rational<T> Rational<T>::operator/=(const Rational &a_rhs)
{
	Div(a_rhs);
	return *this;	
}

template< typename T >
Rational<T> Rational<T>::operator/=(T a_scaler)
{
	Div(a_scaler);
	return *this;
}

template< typename T >
void Rational<T>::Add(const Rational &a_rhs)
{
	if ( m_denumerator !=  a_rhs.Denumerator() )
	{
		m_numerator = m_numerator*a_rhs.Denumerator() + a_rhs.Numerator() * m_denumerator ;
		m_denumerator = m_denumerator * a_rhs.Denumerator() ;
	}
	else
	{
		m_numerator = m_numerator + a_rhs.Numerator() ;
	}
}


template< typename T >
void Rational<T>::Sub(const Rational &a_rhs)
{
	if ( m_denumerator !=  a_rhs.Denumerator() )
	{	
	m_numerator = m_numerator*a_rhs.Denumerator() - a_rhs.Numerator() * m_denumerator ;
	m_denumerator = m_denumerator * a_rhs.Denumerator() ;
	}
	else
	{
		m_numerator = m_numerator - a_rhs.Numerator() ;	
	}
}

template< typename T >
void Rational<T>::Mul(const Rational &a_rhs)
{
	m_numerator = m_numerator * a_rhs.Numerator();
	m_denumerator = m_denumerator * a_rhs.Denumerator();
}

template< typename T >
void Rational<T>::Mul(T a_scaler)
{
	m_numerator = m_numerator * a_scaler * m_denumerator ;
	m_denumerator = m_denumerator * m_denumerator ;
}

template< typename T >
void Rational<T>::Div(T a_scaler)
{
	m_numerator = m_numerator * m_denumerator;
	m_denumerator = m_denumerator * m_denumerator * a_scaler;
}

template< typename T >
void Rational<T>::Div(const Rational &a_rhs)
{
	m_numerator = m_numerator * a_rhs.Denumerator(); 
	m_denumerator = m_denumerator * a_rhs.Numerator();
}

template< typename T >
void Rational<T>::Add(T a_scaler)
{
	m_numerator = a_scaler * m_denumerator + m_numerator ;
}

template< typename T >
void Rational<T>::Sub(T a_scaler)
{
	m_numerator = m_numerator - a_scaler * m_denumerator ;
}

template< typename T >
Rational<T> operator+(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	Rational<T> sumRational = a_lhs;
	sumRational += a_rhs ;
	return sumRational;
}

template< typename T >
Rational<T> operator+(const Rational<T> &a_lhs, T a_scaler)
{
	Rational<T> sumRational = a_lhs;
	sumRational += a_scaler ;
	return sumRational;
}

template< typename T >
Rational<T> operator+(T a_scaler, const Rational<T> &a_rhs)
{
	Rational<T> sumRational = a_rhs;
	sumRational += a_scaler ;
	return sumRational;
}

template< typename T >
Rational<T> operator-(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	Rational<T> subRational = a_lhs;
	subRational -= a_rhs ;
	return subRational;
}

template< typename T >
Rational<T> operator-(const Rational<T> &a_lhs, T a_scaler)
{
	Rational<T> subRational = a_lhs;
	subRational -= a_scaler ;
	return subRational;
}

template< typename T >
Rational<T> operator-(T a_scaler, const Rational<T> &a_rhs)
{
	Rational<T> subRational = a_rhs;
	Rational<T> tmp( a_scaler * a_rhs.Denumerator(), a_rhs.Denumerator());
	tmp -= subRational ;
	return tmp;
}

template< typename T >
Rational<T> operator*(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	Rational<T> mulRational = a_lhs;
	mulRational *= a_rhs ;
	return mulRational;
}

template< typename T >
Rational<T> operator*(const Rational<T> &a_lhs, T a_scaler)
{
	Rational<T> mulRational = a_lhs;
	mulRational *= a_scaler ;
	return mulRational;
}

template< typename T >
Rational<T> operator*(T a_scaler, const Rational<T> &a_rhs)
{
	Rational<T> mulRational = a_rhs;
	mulRational *= a_scaler ;
	return mulRational;
}


template< typename T >
Rational<T> operator/(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	Rational<T> divRational = a_lhs;
	divRational /= a_rhs ;
	return divRational;
}

template< typename T >
Rational<T> operator/(const Rational<T> &a_lhs, T a_scaler)
{
	Rational<T> divRational = a_lhs;
	divRational /= a_scaler ;
	return divRational;
}

template< typename T >
Rational<T> operator/(T a_scaler, const Rational<T> &a_rhs)
{
	Rational<T> divRational = a_rhs;
	Rational<T> tmp( a_scaler * a_rhs.Denumerator(), a_rhs.Denumerator());
	tmp /= divRational ;
	return tmp;
}

template< typename T >
bool operator==(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	Rational<T> res = a_lhs - a_rhs ;

	return (res.Numerator() == 0 ? 1 : 0);
}

template< typename T >
bool operator==(const Rational<T> &a_lhs, T a_scaler)
{
	Rational<T> res = a_lhs - a_scaler ;

	return (res.Numerator() == 0 ? 1 : 0);
}

template< typename T >
bool operator==(T a_scaler, const Rational<T> &a_rhs)
{
	Rational<T> res = a_scaler - a_rhs ;

	return (res.Numerator() == 0 ? 1 : 0);
}

template< typename T >
bool operator!=(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	return !(a_lhs == a_rhs);
}

template< typename T >
bool operator!=(const Rational<T> &a_lhs, T a_scaler)
{
	return !(a_lhs == a_scaler);
}

template< typename T >
bool operator!=(T a_scaler, const Rational<T> &a_rhs)
{
	return !(a_rhs == a_scaler);
}

void Print(int a_numerator, int a_denumerator)
{
	printf(" %d\n", a_numerator);
	printf("-----\n");
	printf(" %d\n", a_denumerator);	
}


template< typename T >
bool operator>(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	Rational<T> res = a_lhs - a_rhs ;

	return (res.Numerator() > 0 ? 1 : 0);
}

template< typename T >
bool operator>(const Rational<T> &a_lhs, T a_scaler)
{
	Rational<T> res = a_lhs - a_scaler ;

	return (res.Numerator() > 0 ? 1 : 0);
}

template< typename T >
bool operator>(T a_scaler, const Rational<T> &a_rhs)
{
	Rational<T> res = a_scaler - a_rhs ;

	return (res.Numerator() > 0 ? 1 : 0);
}


template< typename T >
bool operator<(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	Rational<T> res = a_lhs - a_rhs ;

	return (res.Numerator() < 0 ? 1 : 0);
}

template< typename T >
bool operator<(const Rational<T> &a_lhs, T a_scaler)
{
	Rational<T> res = a_lhs - a_scaler ;

	return (res.Numerator() < 0 ? 1 : 0);
}

template< typename T >
bool operator<(T a_scaler, const Rational<T> &a_rhs)
{
	Rational<T> res = a_scaler - a_rhs ;

	return (res.Numerator() < 0 ? 1 : 0);
}

template< typename T >
bool operator>=(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	return a_lhs > a_rhs || a_lhs == a_rhs ;
}

template< typename T >
bool operator>=(const Rational<T> &a_lhs, T a_scaler)
{
	return a_lhs > a_scaler || a_lhs == a_scaler ;
}

template< typename T >
bool operator>=(T a_scaler, const Rational<T> &a_rhs)
{
	return a_scaler > a_rhs || a_scaler == a_rhs ;
}

template< typename T >
bool operator<=(const Rational<T> &a_lhs, const Rational<T> &a_rhs)
{
	return a_lhs < a_rhs || a_lhs == a_rhs ;
}

template< typename T >
bool operator<=(const Rational<T> &a_lhs, T a_scaler)
{
	return a_lhs < a_scaler || a_lhs == a_scaler ;
}

template< typename T >
bool operator<=(T a_scaler, const Rational<T> &a_rhs)
{
	return a_scaler < a_rhs || a_scaler == a_rhs ;
}

template< typename T >
void Egypt(const Rational<T> &a_rational)
{
	Rational<T> tmp = a_rational;
	int n = 2 ;
	
	if ( 1 == tmp.Numerator())
	{
		Print( tmp.Numerator(), tmp.Denumerator() );
	}
	else
	{
		while ( tmp.Value() )
		{
			Rational<T> tmp2(1,n);
			if ( 1.0/n <= tmp.Value() )
			{
				tmp -= tmp2 ;
				Print( 1,n );
				printf(" +\n");
			}
			n++;
		}
	}
	
}

void Print(long a_numerator, long a_denumerator)
{
	printf(" %li\n", a_numerator);
	printf("-----\n");
	printf(" %li\n", a_denumerator);	
}

#endif /* RATIONAL_HPP */
