#include <stdio.h>
#include <stdlib.h> /* size_t */
#include "ADTDefs.h" /* error enum */
#include "bit.h" 


void PositiveBitCountNumBigThen0(int _num);
void PositiveBitCountNum0(int _num);
void PositiveBitCountCountBigThen1(int _num);
void BitCountNull(int _num);
void InverstBitsNumBigThen0(int _num);
void InverstBitsNum0(int _num);
void InverstBitsNull(int _num);
void RotatesToTheRightMoves0(int _num , int _numMoves);
void RotatesToTheRightMoves0Two(int _num , int _numMoves);
void RotatesToTheRightMovesNormal(int _num , int _numMoves);
void RotatesToTheRightMovesBigSize(int _num , int _numMoves);
void SetBitsNormal();
void SetBitsNumOfBit0();
void SetBitsNumOfBitBigThenPosition();
void SetBitsPositionBigThenSize();
void SetBitsNumOfBitBigThenSize();
void MultipliesPositive();
void MultipliesPositive2();
void MultipliesPositive3();
void MultipliesNull();
void SetBitsTwoPositive();
void SetBitsTwoPositive2();
void SetBitsTwoNegative();
void SetBitsTwoNegative2();
void SetBitsTwoNegative3();
void SetBitsTwoNegative4();
void CompressStringPositive();
void CompressStringNegative();


char pass[] = "PASS" ;
char failed[] = "FAILED" ;


int main(int argc , char *argv[])
{       
     
     PositiveBitCountNumBigThen0(atoi(argv[1]));                    /* argv[1] == 2 */
     PositiveBitCountNum0(atoi(argv[2]));                           /* argv[2] == 0 */
     PositiveBitCountCountBigThen1(atoi(argv[3]));                  /* argv[3] == 57 */
     BitCountNull(atoi(argv[3]));                                   /* argv[3] == 57 */
     InverstBitsNumBigThen0(atoi(argv[4]));                         /* argv[4] == 79 */
     InverstBitsNum0(atoi(argv[2]));                                /* argv[2] == 0 */
     InverstBitsNull(atoi(argv[4]));                                /* argv[4] == 79 */
     RotatesToTheRightMoves0(atoi(argv[4]) , atoi(argv[2]));        /* argv[4] == 79 , argv[2] == 0  */
     RotatesToTheRightMoves0Two(atoi(argv[4]) , atoi(argv[5]));     /* argv[4] == 79 , argv[5] == 8 */ 
     RotatesToTheRightMovesNormal(atoi(argv[4]) , atoi(argv[1]));   /* argv[4] == 79 , argv[1] == 2 */
     RotatesToTheRightMovesBigSize(atoi(argv[4]) , atoi(argv[6]) ); /* argv[4] == 79 , argv[6] == 9 */
     SetBitsNormal();
     SetBitsNumOfBit0();
     SetBitsNumOfBitBigThenPosition();
     SetBitsPositionBigThenSize();
     SetBitsNumOfBitBigThenSize();
     MultipliesPositive();
     MultipliesPositive2();
     MultipliesPositive3();
     MultipliesNull();
     SetBitsTwoPositive();
     SetBitsTwoPositive2();
     SetBitsTwoNegative();
     SetBitsTwoNegative2();
     SetBitsTwoNegative3();
     SetBitsTwoNegative4();
     CompressStringPositive();
   /*  CompressStringNegative(); */

     return 1;
}


void PositiveBitCountNumBigThen0(int _num)
{
      size_t count;
      ADTErr result;
           
      result = BitCount(_num , &count); 
           
      if ( result == ERR_OK && count == 1)
      {
          puts(pass);
      }
      else
      {
          puts(failed);
      }      
}

void PositiveBitCountNum0(int _num)
{
      size_t count;
      ADTErr result;
           
      result = BitCount(_num , &count); 
           
      if ( result == ERR_OK && count == 0)
      {
          puts(pass);
      }
      else
      {
          puts(failed);
      }      
}

void PositiveBitCountCountBigThen1(int _num)
{
      size_t count;
      ADTErr result;
           
      result = BitCount(_num , &count);
           
      if ( result == ERR_OK && count == 4)
      {
          puts(pass);
      }
      else
      {
          puts(failed);
      }
}

void BitCountNull(int _num)
{
      ADTErr result;
           
      result = BitCount(_num , NULL);
           
      if ( result == ERR_NOT_INITIALIZED )
      {
          puts(pass);
      }
      else
      {
          puts(failed);
      }
}

void InverstBitsNumBigThen0(int _num)
{
     unsigned char NewBinaryNum;
     ADTErr result;
     
     if ( ( result = InverstBits(_num , &NewBinaryNum) ) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);
     }
}

void InverstBitsNum0(int _num)
{
     unsigned char NewBinaryNum;
     ADTErr result;
     
     if ( ( result = InverstBits(_num , &NewBinaryNum) ) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);
     }
}

void InverstBitsNull(int _num)
{
     ADTErr result;
     
     if ( ( result = InverstBits(_num , NULL) ) == ERR_NOT_INITIALIZED )
     {
          puts(pass);
     }
     else
     {
          puts(failed);
     }
}

void RotatesToTheRightMoves0(int _num , int _numMoves)
{
    ADTErr result; 
    
     if( (result = RotatesToTheRight(_num , _numMoves)) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void RotatesToTheRightMoves0Two(int _num , int _numMoves)
{
    ADTErr result; 
    
     if( (result = RotatesToTheRight(_num , _numMoves)) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void RotatesToTheRightMovesNormal(int _num , int _numMoves)
{
    ADTErr result; 
    
     if( (result = RotatesToTheRight(_num , _numMoves)) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void RotatesToTheRightMovesBigSize(int _num , int _numMoves)
{
    ADTErr result; 
    
     if( (result = RotatesToTheRight(_num , _numMoves)) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void SetBitsNormal()
{
    ADTErr result; 
    
     if ( (result = SetBits(170 , 6 , 3 ,167)) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void SetBitsNumOfBit0()
{
    ADTErr result; 
    
     if ( (result = SetBits(170 , 6 , 0 ,167)) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void SetBitsNumOfBitBigThenPosition()
{
    ADTErr result; 
    
     if ( (result = SetBits(170 , 1 , 3 ,167)) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void SetBitsPositionBigThenSize()
{
    ADTErr result; 
    
     if ( (result = SetBits(170 , 9 , 3 ,167)) == ERR_WORNG_INDEX )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void SetBitsNumOfBitBigThenSize()
{
    ADTErr result; 
    
     if ( (result = SetBits(170 , 1 , 9 ,167)) == ERR_WORNG_INDEX )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void MultipliesPositive()
{
     double result;
     ADTErr resultError;        
     
     if ((resultError = Multiplies(6 , 36 , &result)) == ERR_OK && (result == 216) )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }      
}

void MultipliesPositive2()
{
     double result;
     ADTErr resultError;        
     
     if ((resultError = Multiplies(0 , 36 , &result)) == ERR_OK && (result == 0) )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }      
}

void MultipliesPositive3()
{
     double result;
     ADTErr resultError;        
     
     if ((resultError = Multiplies(6 , 0 , &result)) == ERR_OK && (result == 0) )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }      
}

void MultipliesNull()
{
     ADTErr resultError;        
     
     if ((resultError = Multiplies(6 , 0 , NULL)) == ERR_NOT_INITIALIZED )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }      
}

void SetBitsTwoPositive()
{
     unsigned int num=0 ;  
     ADTErr result ;
     
     if (((result=SetBitsTwo(&num , 1 , 1 , 1)) == ERR_OK) && (num == 1))
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }     
}

void SetBitsTwoPositive2()
{
     unsigned int num=0 ;  
     ADTErr result ;
     
     if (((result=SetBitsTwo(&num , 2 , 1 , 1)) == ERR_OK) && (num == 3))
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     } 
}

void SetBitsTwoNegative()
{ 
     ADTErr result ;
     
     if ((result=SetBitsTwo(NULL , 2 , 1 , 1)) == ERR_NOT_INITIALIZED )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void SetBitsTwoNegative2()
{
     unsigned int num=0 ;  
     ADTErr result ;
     
     if ( (result=SetBitsTwo(&num , 1 , 2 , 1)) == ERR_WORNG_INDEX )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     } 
}

void SetBitsTwoNegative3()
{
     unsigned int num=0 ;  
     ADTErr result ;
     
     if ( (result=SetBitsTwo(&num , 9 , 2 , 1)) == ERR_WORNG_INDEX )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void SetBitsTwoNegative4()
{
     unsigned int num=0 ;  
     ADTErr result ;
     
     if ( (result=SetBitsTwo(&num , 7 , 2 , 5)) == ERR_WORNG_INDEX )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void CompressStringPositive()
{
     ADTErr result ;
     char str[]="da";
     
     if ( (result = CompressString(str)) == ERR_OK )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

void CompressStringNegative()
{
     ADTErr result ;
     char str[]="dr";
     
     if ( (result = CompressString(str)) == ERR_GENERAL )
     {
          puts(pass);
     }
     else
     {
          puts(failed);         
     }
}

