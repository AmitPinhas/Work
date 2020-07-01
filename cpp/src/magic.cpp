#include "magic.hpp"

static int CheckSquare(Matrix a_matrix);
static int CheckInput(Matrix a_matrix);
static size_t CalculateSum(Matrix a_matrix);
static int CheckDiagonals(Matrix a_matrix, size_t a_sum);
static int CheckRowsColumns(Matrix a_matrix, size_t a_sum);
static Matrix BuildMagicSquareOdd(int a_n);
static Matrix BuildMagicSquareEven(int a_n);

bool IsMagicSquare(Matrix a_matrix)
{
 	if ( CheckSquare( a_matrix ) == 0 )
 	{
 		return 0;
 	}
	
	if ( CheckInput( a_matrix ) == 0 )
	{
		return 0;
	}
	
	size_t sum = CalculateSum( a_matrix ) ;
	
	if ( CheckDiagonals( a_matrix , sum ) == 0 )
	{
		return 0 ;
	}
	
	if ( CheckRowsColumns( a_matrix , sum ) == 0 )
	{
		return 0 ;
	}
	
	return 1 ;
}

Matrix BuildMagicSquare(int a_n)
{	
	if ( a_n % 2 != 0 )
	{
		return BuildMagicSquareOdd(a_n);
	}
	
	return BuildMagicSquareEven(a_n);
}


static Matrix BuildMagicSquareOdd(int a_n)
{
	Matrix magicSquare(a_n);   
   
    int i = a_n/2;  
    int j = a_n-1;  
  
    for (int num = 1; num <= a_n*a_n; )  
    {  
        if (i == -1 && j == a_n)   
        {  
            j = a_n-2;  
            i = 0;  
        }  
        else
        {  
 
            if (j == a_n)  
                j = 0;  
  
 
            if (i < 0)  
                i = a_n - 1;  
        }  
        if (magicSquare.Get(i,j)) //2nd condition  
        {  
            j -= 2;  
            i++;  
            continue;  
        }  
        else
            magicSquare.Set(i,j,num++) ; 
  
        j++; i--; 
    }  
    
    return magicSquare;	
}

static Matrix BuildMagicSquareEven(int a_n)
{
    Matrix magicSquare(a_n);
    int i , j;
  
    for ( i = 0; i < a_n; i++) 
        for ( j = 0; j < a_n; j++) 
            magicSquare.Set(i,j,(a_n*i) + j + 1); 
       
    for ( i = 0; i < a_n/4; i++) 
        for ( j = 0; j < a_n/4; j++) 
            magicSquare.Set(i,j,(a_n*a_n + 1) - magicSquare.Get(i,j)); 
     
    for ( i = 0; i < a_n/4; i++) 
        for ( j = 3 * (a_n/4); j < a_n; j++) 
            magicSquare.Set(i,j,(a_n*a_n + 1) - magicSquare.Get(i,j));
      
    for ( i = 3 * a_n/4; i < a_n; i++) 
        for ( j = 0; j < a_n/4; j++) 
            magicSquare.Set(i,j,(a_n*a_n + 1) - magicSquare.Get(i,j));
     

    for ( i = 3 * a_n/4; i < a_n; i++) 
        for ( j = 3 * a_n/4; j < a_n; j++) 
            magicSquare.Set(i,j,(a_n*a_n + 1) - magicSquare.Get(i,j));
    
    for ( i = a_n/4; i < 3 * a_n/4; i++) 
    {
        for ( j = a_n/4; j < 3 * a_n/4; j++) 
        {
            magicSquare.Set(i,j,(a_n*a_n + 1) - magicSquare.Get(i,j));
        }    
	}
            
	return magicSquare;        
}

static int CheckSquare(Matrix a_matrix)
{
	Dimension dim = a_matrix.Dim();
	
	if ( dim.m_rows != dim.m_columns )
	{
		return 0;
	}
	
	return 1;	
}


static int CheckInput(Matrix a_matrix)
{
	Dimension dim = a_matrix.Dim();
	int *value = new int[dim.m_rows * dim.m_columns]() ;
	const size_t r = dim.m_rows;
	const size_t c = dim.m_columns;
	
	for ( size_t i = 0 ; i < r ; ++i )
	{
		for ( size_t j = 0 ; j < c ; ++j )
		{
			if ( a_matrix.Get(i,j) > 0 && a_matrix.Get(i,j) <= dim.m_rows * dim.m_columns )
			{
				int index = a_matrix.Get(i,j)-1;
				value[index] = 1 ; 
			}
			else
			{
				delete[] value;
				return 0 ;
			}
		}
	}
	
	size_t n = dim.m_rows * dim.m_columns ;
	
	while ( n-- > 0 )
	{
		if ( value[n] == 0 )
		{
			delete[] value;
			return 0;
		}
	}
	
	delete[] value;
	
	return 1;	
}


inline static size_t CalculateSum(Matrix a_matrix)
{
	Dimension dim = a_matrix.Dim();
	
	return dim.m_rows * ( 1 + dim.m_rows * dim.m_rows ) / 2 ;
}


static int CheckDiagonals(Matrix a_matrix, size_t a_sum)
{
	Dimension dim = a_matrix.Dim();
	const size_t rc = dim.m_rows;
	size_t sum = 0, n = rc;
	
	while (n-- > 0)
	{
		sum += a_matrix.Get(n,n) ;
	}
	if ( sum != a_sum )
	{
		return 0;
	}
	
	sum = 0;
	
	for ( size_t i = 0 , j = rc-1 ; i < rc ; ++i , --j )
	{
		sum += a_matrix.Get(i,j) ;
	}
	if ( sum != a_sum )
	{
		return 0;
	}	
	
	return 1;
}


static int CheckRowsColumns(Matrix a_matrix, size_t a_sum)
{
	Dimension dim = a_matrix.Dim();
	const size_t rc = dim.m_rows;
	
	for ( size_t i = 0 ; i < rc ; ++i )
	{
		size_t sumRow = 0 , sumColumn = 0 ;
		for ( size_t j = 0 ; j < rc ; ++j )
		{
			sumRow += a_matrix.Get(i,j);
			sumColumn += a_matrix.Get(j,i);
		}
		
		if ( sumRow != a_sum || sumColumn != a_sum )
		{
			return 0 ;
		}
		
	}
		
	return 1 ;
}
