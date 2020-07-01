#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strlen */

#define TRUE 1
#define FALSE 0
#define PTR_ERROR -1000

int MaxInArray(int _arr[] , int _n);
int MaxInArrayRec(int _arr[] , int _n);
float AverageInArray(int _arr[] , int _n);
float AverageInArrayRec(int _arr[] , int _n);
double FiboRec(int _n);
double FiboIte(int _n);
int ReversString(char *_str , size_t _size);
void ReversStringRec(char *_str , size_t _size);
void swap_ch(char *_ch , char *_ch2);
int IsPlindrome(char *_str , size_t _size);
int IsPlindromeRec(char *_str , size_t _size);
int StrCmp(char *_str1 , char *_str2);
int StrCmpRec(char *_str1 , char *_str2);
void PrintMultiplicationTable(int _size);
void PrintMultiplicationTableRec(int _size , int _row , int _column);
void Hanoi(int _n , char _from , char _to , char _via);
void Permuetazia(char _str[] , int _index , int _size);


int main()
{
     int arrMax[]={43, 423,9} , max , sizeMax ;
     int arrAvr[]={3, 10, 2} , sizeAvr ;     
     int sizeRve , sizePali , pali , cmp , sizePer;
     float average ;
     double fiboIte , fiboRec;
     char strRve[]="abcbab" , strPali[]="abcvfew" , str1[]="abcvfd" , str2[]="abcvfd" , strPer[]="abc";

     
     sizeMax = sizeof(arrMax) / sizeof(arrMax[0]) ;     
     max = MaxInArray(arrMax , sizeMax);    
     printf("max %d\n" , max);


     sizeAvr = sizeof(arrAvr) / sizeof(arrAvr[0]) ;    
     average = AverageInArray(arrAvr , sizeAvr);    
     printf("average %.2f\n" , average);
        
     
     fiboRec = FiboRec(30);     
     printf("FiboRec %.0f\n" , fiboRec);
   
     
     fiboIte = FiboIte(30);     
     printf("FiboIte %.0f\n" , fiboIte);     
    
     printf("revers: ");
     puts(strRve); 
     sizeRve = strlen(strRve);    
     ReversString(strRve , sizeRve);  
     puts(strRve); 
   
     
     sizePali = strlen(strPali);      
     pali = IsPlindrome(strPali , sizePali);    
     printf("Plindrome --> %d\n" , pali);
 
     
     cmp = StrCmp(str1 , str2);    
     printf("cmp -- > %d\n" , cmp);
     putchar('\n');
     
     
     PrintMultiplicationTable(10);
     putchar('\n');    
     Hanoi(2 , 'a' , 'b' , 'c');
     
     sizePer = strlen(strPer);
     Permuetazia(strPer , 0 , sizePer-1);
     
     return 1;
}

int MaxInArray(int _arr[] , int _n)
{
     if ( NULL == _arr || _n <= 0)
     {
          return 0;
     }
     
     MaxInArrayRec( _arr , _n);
}

int MaxInArrayRec(int _arr[] , int _n)
{
     if ( 1 == _n )
     {
          return _arr[_n-1];
     }
     
   return MaxInArray(_arr , _n-1) > _arr[_n-1] ? MaxInArray(_arr , _n-1)  : _arr[_n-1] ;
}

float AverageInArray(int _arr[] , int _n)
{
     if ( NULL == _arr || _n <= 0)
     {
          return 0;
     }
     
   return AverageInArrayRec( _arr , _n);
}

float AverageInArrayRec(int _arr[] , int _n)
{       
     if ( 1 == _n )
     {
          return _arr[_n-1];
     }
          
     return (AverageInArrayRec(_arr , _n-1)*(_n-1)+_arr[_n-1]) / (_n) ;
}


double FiboRec(int _n)
{
     if( _n <= 0)
     {
          return 0;
     }
     
     if ( 1 == _n )
     {
          return 1;
     }
     
     return FiboRec(_n-2) + FiboRec(_n-1) ;
}

double FiboIte(int _n)
{
     int index ;
     double res , a ,b ;

     if( _n <= 0)
     {
          return 0;
     }
     
     if ( 1 == _n )
     {
          return 1;
     }
     
     a=0 ;
     b=1 ;
     
     for(index = 2 ; index<=_n ; index++)
     {
          res = a + b ;
          
          a = b ;
          b = res ;
     }
     
     return res;
}

int ReversString(char *_str , size_t _size)
{
     if ( NULL == _str )
     {
          return 0;
     }
     else
     {
          ReversStringRec(_str , _size);
     }
}

void ReversStringRec(char *_str , size_t _size)
{       
     if ( _size < 2 )
     {
          return;
     }     
    swap_ch(&_str[_size-1] , _str);    
    ReversString(_str+1 , _size - 2) ;       
}

int IsPlindrome(char *_str , size_t _size)
{
     if ( NULL == _str )
     {
          return 0;
     }
     else
     {
        return IsPlindromeRec(_str , _size);
     }
}

int IsPlindromeRec(char *_str , size_t _size)
{
     
     if ( _size < 2 )
     {
          return TRUE;
     }
     

     if (_str[_size-1] != *_str) 
     {
          return FALSE ;
     }
         
    return ReversString(_str+1 , _size - 2) ;   
}

int StrCmp(char *_str1 , char *_str2)
{
     if ( NULL == _str1 || NULL == _str2)
     {
          return PTR_ERROR;
     }
     
     return StrCmpRec(_str1 , _str2);
}

int StrCmpRec(char *_str1 , char *_str2)
{
     if( (*_str1 == '\0') && (*_str2 == '\0') )
     {
          return 0;
     }  
     if( *_str1 != *_str2)
     {
          return *_str1 - *_str2 ;
     }         
     
   return StrCmpRec(_str1+1 , _str2+1)  ;
}

void PrintMultiplicationTable(int _size)
{
     if( _size <=0 )
     {
          return;
     }
     
     PrintMultiplicationTableRec(_size , 1  , 1);
}

void PrintMultiplicationTableRec(int _size , int _row , int _column)
{
     if( _column <= _size)
     {
          printf("%4d", _row * _column);
          PrintMultiplicationTableRec(_size , _row , _column+1);
     }
     else if ( _row < _size )
     {
         putchar('\n');
         PrintMultiplicationTableRec(_size , _row+1 , 1);
     }
    
     return;
}

/* from = a  , to = b , via = c */
void Hanoi(int _n , char _from , char _to , char _via)
{
     if ( 0 >= _n )
     {
        return;
     }
     else
     {
      Hanoi(_n -1 , _from ,  _via ,  _to) ; 
      printf ("move %d from %c to %c via %c\n" , _n , _from , _to , _via);
      Hanoi(_n -1 , _via ,  _to ,  _from) ;
     }
}

void Permuetazia(char _str[] , int _index , int _size)
{
     int i;
     
     if ( _index == _size)
     {
          puts(_str);
     }
     
     for ( i = _index ; i <= _size ; i++)
     {
          swap_ch(&_str[_index] , &_str[i]);
          
          Permuetazia(_str , _index+1 , _size);
          
          swap_ch(&_str[_index] , &_str[i]); 
          
     }
}

void swap_ch(char *_ch , char *_ch2)
{
     char tmp;
     
     tmp = *_ch;
     *_ch = *_ch2;
     *_ch2 = tmp;
}

