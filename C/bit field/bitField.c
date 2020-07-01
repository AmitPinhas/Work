#include <stdio.h>

#define BITS 8
#define SIZE(type) (sizeof(type) * BITS)

struct Compress
{
     unsigned char m_right:4;
     unsigned char m_left:4;     
};

union Compre
{
    struct Compress m_a;
    unsigned char m_result; 
};


static void PrintBinaryNum( unsigned char _binaryNum)
{
    size_t size=SIZE(_binaryNum) ;
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

int CompressString(char _str[])
{
     int index=0;
     union Compre compress ;
     
     if ( NULL == _str )
     {
          return 0;
     }
     
     while (  _str[index*2] && _str[index*2 + 1] )
     {
          compress.m_a.m_left = (_str[index*2] - 'a' + 1) ; 
          compress.m_a.m_right = (_str[index*2 + 1] - 'a' + 1) ;
          _str[index] = compress.m_result ;
          index++;
     }
     
     if ( _str[index*2] != '\0')
     {
       compress.m_a.m_left = (_str[index*2] - 'a' + 1) ; 
       compress.m_a.m_right = 0 ;
       _str[index] = compress.m_result;
       index++;
     }
      _str[index] = '\0'; 
    
      return 1;
}

int main()
{
     char str[]="aba";
     int index;
     CompressString(str);
     
     for ( index = 0 ; str[index] != 0 ; index++)
     {
       PrintBinaryNum( str[index]);   
     }

     return 1;
}
