#include <stdio.h> /* printf */
#include <stdlib.h> /* size_t */
#include <string.h> /* strlen */
#include "ADTDefs.h" /* error enum */
#include "bit.h"

#define SIZE_FOUR_BITS 4
#define NUM_BITS 8
#define MAX_VALUE_FOUR_BITS 15
#define SIZE(type) (sizeof(type) * NUM_BITS)

static ADTErr CountBits(unsigned int _number, size_t *_count);
static void PrintBinaryNum(unsigned char _binaryNum); 
static void InverstBinaryNum(unsigned char _binaryNum , unsigned char *_NewBinaryNum);  
static void RotatesBinaryNum(unsigned char *_binaryNum , size_t _numberOfMoves);
static void LocalSetBits(unsigned char *_binaryNum , unsigned int _position , unsigned int _numOfBit , unsigned char _binaryNumTwo);
static ADTErr LocalMultiplies( unsigned short _num1 ,  unsigned short _num2 , double *_result); 
static void ClearBit(unsigned char *_NewBinaryNum ,int _index);
static void SetBit(unsigned char *_NewBinaryNum ,int _index);
static void LocalSetBitsTwo(unsigned int *_num1 , int _from , int _to , int _value);   
static void ClearBitInt(unsigned int *_NewBinaryNum ,int _index);
static void SetBitInt(unsigned int *_NewBinaryNum ,int _index);
static void ChangeBits(int _index , char *_str , int _index3 , int _inc); 
static ADTErr CheckAndChangeBits(char *_str); 


ADTErr BitCount(unsigned int _number, size_t *_count)
{
    if ( NULL == _count )
    {
      return ERR_NOT_INITIALIZED ; 
    }

   return CountBits (_number, _count);
}


ADTErr InverstBits(unsigned char _binaryNum , unsigned char *_NewBinaryNum)
{
    if ( NULL == _NewBinaryNum )
    {
       return ERR_NOT_INITIALIZED;
    }
     
    printf("Binary Num = "); 
     
    PrintBinaryNum(_binaryNum);    
    
    InverstBinaryNum(_binaryNum ,_NewBinaryNum);
        
    printf("inverted Binary Num= ");  
    
    PrintBinaryNum(*_NewBinaryNum);        
    
    return ERR_OK;
}

ADTErr RotatesToTheRight(unsigned char _binaryNum , size_t _numberOfMoves)
{
    size_t size = SIZE(_binaryNum);
    size_t tempNumberOfMoves;
    
    tempNumberOfMoves = _numberOfMoves%size ;    
    
    if ( 0 == tempNumberOfMoves )
    {
        printf("binary num = ");
        PrintBinaryNum(_binaryNum); 
        printf("rotated binary num by %ld = " ,_numberOfMoves ); 
        PrintBinaryNum(_binaryNum); 
        return ERR_OK ;                      
    }

    printf("binary num = ");
    PrintBinaryNum(_binaryNum);      

    RotatesBinaryNum(&_binaryNum ,tempNumberOfMoves);
           
    printf("rotated binary num by %ld = " ,_numberOfMoves ); 
    PrintBinaryNum(_binaryNum);     
    
    return ERR_OK ;       
}

ADTErr SetBits(unsigned char _binaryNum , unsigned int _position , unsigned int _numOfBit , unsigned char _binaryNumTwo)
{
     size_t size=sizeof(unsigned char) * NUM_BITS ;

     if ( (_position > size) ||  (_numOfBit>size) || 0 == _position )
     {
        return ERR_WORNG_INDEX;
     } 
     
    printf("binary num = ");
    PrintBinaryNum(_binaryNum);  

    printf("binary num two = ");
    PrintBinaryNum(_binaryNumTwo);      
 
    LocalSetBits(&_binaryNum , _position , _numOfBit , _binaryNumTwo);
     
    printf("setbits num of bit = %d , position = %d gives binary num = " , _numOfBit , _position );
    PrintBinaryNum(_binaryNum); 
    
    return ERR_OK;        
}

ADTErr Multiplies(unsigned short _num1 , unsigned short _num2 , double *_result)
{
      if ( NULL == _result )
      {
         return ERR_NOT_INITIALIZED;
      }

     return LocalMultiplies(_num1 , _num2 , _result);        
}

ADTErr SetBitsTwo(unsigned int *_num1 , int _from , int _to , int _value)
{
     size_t size=sizeof(unsigned char) * NUM_BITS ;
     
     if ( NULL == _num1)
     {
          return ERR_NOT_INITIALIZED;
     }
     
     if ( (_from < _to) || (_from > size) || ((_value != 0) && (_value != 1)) )
     {
          return ERR_WORNG_INDEX;
     } 
     
    LocalSetBitsTwo(_num1 , _from , _to , _value);   
    
    return ERR_OK ;       
}

ADTErr CompressString(char *_str)
{
     int size = strlen(_str) ;
     ADTErr result;
          
     if ( NULL == _str )
     {
          return ERR_NOT_INITIALIZED;
     }
     
     if ( (result = CheckAndChangeBits(_str)) != ERR_OK ) 
     {
          return result ;
     }
     
     if ( size%2 == 0 )
     { 
     _str[size/2] = '\0' ;
     }
     else
     {
     _str[(size/2)+1] = '\0' ;     
     }
     
     return ERR_OK ;
}

static ADTErr CountBits(unsigned int _number, size_t *_count)
{   
    while(_number)
    {
         if (_number & 1)
         {
            *_count +=1 ;
         }
         
         _number >>=1;
    }
    
    return ERR_OK;    
}

static void PrintBinaryNum( unsigned char _binaryNum)
{
    size_t size = SIZE(_binaryNum);
    int index;
    int msb;
    msb = 1<<(size-1);   
     
    for ( index = 0 ; index<size ; index++)
    {
         if ( _binaryNum&msb)
         {
          putchar('1');
         }
         else
         {
          putchar('0');
         }
         msb >>=1;
    }
    putchar('\n');
}

static void InverstBinaryNum(const unsigned char _binaryNum , unsigned char *_NewBinaryNum)
{
    size_t size = sizeof(unsigned char) * NUM_BITS;
    int index;
    
    for ( index = 0 , *_NewBinaryNum=0 ; index < size ; index++)
    {
         if ( _binaryNum&(1<<index))
         {
          ClearBit(_NewBinaryNum , index);
         }
         else
         {
          SetBit(_NewBinaryNum , index);
         }
    }
}

static void RotatesBinaryNum(unsigned char *_binaryNum , size_t _numberOfMoves)
{
    size_t size=sizeof(unsigned char) * NUM_BITS ;
    int index;
    int msb , msbTemp;
    unsigned char tempBinaryNum ;    

    msb = 1<<(_numberOfMoves-1);
    
    for ( index=0 , tempBinaryNum=0 , msbTemp=size-1 ; index< _numberOfMoves ; index++ , msbTemp-- )
    {
          if ( *_binaryNum & msb )
          {
           SetBit(&tempBinaryNum , msbTemp);
          }
          else
          {
           ClearBit(&tempBinaryNum , msbTemp);
          }
          msb >>=1;
    }
    
    msb = 1<<(size-1);
    
    for (index =0 ; index<size-_numberOfMoves ; index++  , msbTemp--)
    {
          if (*_binaryNum&msb)
          {
           SetBit(&tempBinaryNum , msbTemp);
          }
          else
          {
           ClearBit(&tempBinaryNum , msbTemp);
          }
          msb >>=1;     
    }      
    
    *_binaryNum = tempBinaryNum ;
}

static void LocalSetBits(unsigned char *_binaryNum , unsigned int _position , unsigned int _numOfBit ,unsigned char _binaryNumTwo)
{
     size_t size=sizeof(unsigned char) * NUM_BITS ;
     int index ;
     int numOfBitTemp;
     
     for ( index=0 , numOfBitTemp=_numOfBit ; index< numOfBitTemp ; index++ , _numOfBit-- , _position>1?_position--:(_position=size) )
     {          
          if ( _binaryNumTwo&(1<<(_numOfBit-1)))
          {
            SetBit(_binaryNum , _position-1);          
          }
          else
          {
            ClearBit(_binaryNum , _position-1);
          }
     }          
}

static ADTErr LocalMultiplies( unsigned short _num1 ,  unsigned short _num2 , double *_result)
{
      size_t size=sizeof(unsigned short) * NUM_BITS ;
      int index ;
      
      for(index =0 , *_result=0 ; index<size ; index++)
      {
          if ( _num2 & (1<<index) )
          {
               *_result +=(_num1<<index);
          }
      }    

      return ERR_OK;      
}

static void LocalSetBitsTwo(unsigned int *_num1 , int _from , int _to , int _value)
{
     int index;
     
     if (_value)
     {
           for ( index=_from-1 ; index>= _to-1 ; index--)
           {
            SetBitInt(_num1 , index);      
           }
     }
     else
     {
           for ( index=_from-1 ; index>= _to-1 ; index--)
           {
            ClearBitInt(_num1 , index);     
           }    
     }
}

static void ChangeBits(int _index , char *_str, int _index3 , int _inc)
{
     int num , index2 ;
     
          num = _str[_index] - 'a' + 1 ;
          
          for ( index2 = 0 ; index2 < SIZE_FOUR_BITS ; index2++)
          {
               if ( num&(1<<index2))
               {
                _str[_index3] |= (1<<(index2+_inc));  
               }
               else
               {
               _str[_index3] &= ~(1<<(index2+_inc)); 
               }
          }
}

static ADTErr CheckAndChangeBits(char *_str)
{
     int index , index2 ;
     
     for ( index = 0 , index2=0 ; _str[index] != '\0' ; index +=2 , index2++ )
     {

             ChangeBits(index , _str , index2 , SIZE_FOUR_BITS );         
          
             if ( _str[index+1] != '\0' )
             {
                  if ( _str[index+1] - 'a' + 1 > MAX_VALUE_FOUR_BITS )
                  {
                      return ERR_GENERAL ;
                  }
                  ChangeBits(index+1 , _str , index2 , 0 );                     
             }
             else
             {
               break ;
             }                  
                  
     }
     
     return ERR_OK ;
}

static void ClearBit(unsigned char *_NewBinaryNum ,int _index)
{
   *_NewBinaryNum &=~(1<<_index);
}

static void SetBit(unsigned char *_NewBinaryNum ,int _index)
{
   *_NewBinaryNum |=(1<<_index);
}

static void ClearBitInt(unsigned int *_NewBinaryNum ,int _index)
{
   *_NewBinaryNum &=~(1<<_index);
}

static void SetBitInt(unsigned int *_NewBinaryNum ,int _index)
{
   *_NewBinaryNum |=(1<<_index);
}




