#include <stdio.h>
#include "triangle_copy.h"

int Check_Input(char _ch , unsigned int _height_width);

int Print_Line(char _ch , unsigned int _height_width);

char Input_Char();

unsigned int Input_Height_Width();


int RightAngledTriangle1(char _ch , unsigned int _height_width)
{
  int rows, result;
  
  if( (result=Check_Input(_ch , _height_width)) != OK)
  {
        return result;
  }
  
  for (rows=0 ; rows<_height_width ; rows++ , putchar('\n') )
  {
    Print_Line(_ch , rows);
  }

  return OK;
}

int RightAngledTriangle2(char _ch , unsigned int _height_width)
{
  int  columns , result;
  
    if( (result=Check_Input(_ch , _height_width)) != OK)
  {
        return result;
  }
   
   for(columns=_height_width ; columns>0 ; columns-- , putchar('\n'))
   {
      Print_Line(_ch , columns-1);
   }

  return OK;
}


int Triangle_Left3(char _ch , unsigned int _width)
{
  int result ;
  
  
  if( (result=RightAngledTriangle1( _ch , _width)) != OK)
  {
        return result;
  }
  
  else if (_width-1 >= MIN_SIZE)
  {
        return RightAngledTriangle2( _ch , _width-1);
  }
  
  
  return OK;


}


int AnIsoscelesTriangle4(char _ch , unsigned int _height)
{
  int rows  , print_ch , space , result ;
  
    if( (result=Check_Input(_ch , _height)) != OK)
  {
        return result;
  }
  
    for(rows=0 , print_ch=1 , space=_height-1 ; rows<_height ; rows++ , space-- , print_ch +=2 ,  putchar('\n'))
    {
      Print_Line(' ' , space);
      
      Print_Line(_ch , print_ch-1);
    
    } 

   return OK;
}


int AnIsoscelesTriangle5(char _ch , unsigned int _height)
{
  int rows , print_ch , max_ch , result ;
  
    if( (result=Check_Input(_ch , _height)) != OK)
  {
        return result;
  }
  
  max_ch=1+(2*(_height-1));
  
    for(rows=0 , print_ch=max_ch ; rows<_height ; rows++ , print_ch -=2 ,  putchar('\n'))
    {
      Print_Line(' ' , rows);
      
      Print_Line(_ch , print_ch-1);      
    }

  return OK;
}


int Rhombus6(char _ch , unsigned int _width)
{
  int rows , columns , print_ch ,space , flag , result ;
  
    if( (result=Check_Input(_ch , _width)) != OK)
  {
        return result;
  }
   
    for(rows=0 , space=_width-1 , print_ch=1 , flag=0 ; print_ch>0 ; rows++ , flag?space++:space-- , flag?print_ch--:print_ch++ , putchar('\n'))
    {
    
      Print_Line(' ' , space);
      
      for(columns=1 ; columns<=print_ch ; columns++)
      { 
       putchar(_ch);
       printf(" ");
      }
      
    if(rows/(_width-1) == 1)
    { 
      flag=1;
    }
   }

  return OK;
}

int Check_Input(char _ch , unsigned int _height_width)
{
        if( _height_width < MIN_SIZE || _height_width > MAX_SIZE )
        {
                return ERROR_SIZE ;
        }
        
        else if( _ch < MIN_CHAR || _ch > MAX_CHAR)
        {
                return ERROR_CHAR;
        }
        
        return OK;
}

int Print_Line(char _ch , unsigned int _height_width)
{
     int columns;     
        
         for(columns=0 ; columns<=_height_width ; columns++)
         {
              putchar(_ch);
         }
         
         return OK;
} 

char Input_Char()
{ 
  char ch;
  
  printf("Please enter character --> ");
  ch=getchar();  
  
  return ch;
}


unsigned int Input_Height_Width()
{
   unsigned int height_width;
   
    printf("Please enter the height_width --> ");
    scanf("%u" , &height_width);  
    
    putchar('\n');
    
    return height_width;
}


