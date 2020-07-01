#include <stdio.h>

char Input_Char()
{ 
  char ch;
  
  printf("Please enter character --> ");
  ch=getchar();  
  
  return ch;
}

int Input_Height_Width()
{
   int height_width;
   
    printf("Please enter the height_width --> ");
    scanf("%d" , &height_width);  
    
    printf("\n");
    
    return height_width;
}

/*
1
$
$$
$$$
*/

int RightAngledTriangle1(char _ch , int _height_width)
{
  int rows , columns;
  
  printf("1 --> \n\n");

  for (rows=0 ; rows<_height_width ; rows++ , printf("\n") )
  {
    for(columns=0 ; columns<=rows ; columns++)
    {
      putchar(_ch);
    }
  }

  printf("\n");
  return 0;
}

/*
2
$$$
$$
$
*/

int RightAngledTriangle2(char _ch , int _height_width)
{
  int rows , columns;
  
   printf("2 --> \n\n");
 
for(columns=_height_width ; columns>0 ; columns-- , printf("\n"))
{
  for (rows=0 ; rows<columns ; rows++)
  {
      putchar(_ch);
  }
}

  printf("\n");
  return 0;
}

/*
3
$
$$
$$$
$$
$
*/

int Triangle_Left3(char _ch , int _width)
{
  int rows , columns , flag ;
  
  printf("3 --> \n\n");
  
for(rows=0 , flag=0 ; rows>=0 ; flag?rows--:rows++ , printf("\n"))
  { 
    for(columns=0 ; columns<=rows ; columns++)
    { 
     putchar(_ch);
    }
    
    if(rows/(_width-1) == 1)
    { 
      flag=1;
    }
  }

  printf("\n");
  return 0;
}

/*
4
  $
 $$$
$$$$$
*/

int AnIsoscelesTriangle4(char _ch , int _height)
{
  int rows , columns , print_ch ,space ;
  
  printf("4 --> \n\n");
  
    for(rows=0 , print_ch=1 , space=_height-1 ; rows<_height ; rows++ , space-- , print_ch +=2 ,  printf("\n"))
    {
      for(columns=0 ; columns<space ; columns++)
      {
        printf(" ");
      }
      
      for(columns=0 ; columns<print_ch ; columns++)
      { 
       putchar(_ch);
      }
    
    } 

   printf("\n");
   return 0;
}

/*
5
$$$$$
 $$$
  $
*/

int AnIsoscelesTriangle5(char _ch , int _height)
{
  int rows , columns , print_ch , max_ch ;
  
  printf("5 --> \n\n");

  max_ch=1+(2*(_height-1));
  
    for(rows=0 , print_ch=max_ch ; rows<_height ; rows++ , print_ch -=2 ,  printf("\n"))
    {
      for(columns=0 ; columns<rows ; columns++)
      {
        printf(" ");
      } 
      
      for(columns=0 ; columns<print_ch ; columns++)
      { 
       putchar(_ch);
      }      
    }

  printf("\n");
  return 0;
}

/*
6
  &
 & &
& & &
 & &
  &
*/

int Rhombus6(char _ch , int _width)
{
  int rows , columns , print_ch ,space , flag ;
  
  printf("6 --> \n\n");
  
    for(rows=0 , space=_width-1 , print_ch=1 , flag=0 ; print_ch>0 ; rows++ , flag?space++:space-- , flag?print_ch--:print_ch++ , printf("\n"))
    {
    
      for(columns=0 ; columns<space ; columns++)
      {
        printf(" ");
      }
      
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

  printf("\n");
  return 0;
}



