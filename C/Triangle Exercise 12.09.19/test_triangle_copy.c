#include <stdio.h>
#include "triangle_copy.h"

int main()
{
  char ch;
  unsigned int height_width;


  ch=Input_Char();  

  height_width=Input_Height_Width();


  printf("1 --> \n");
  RightAngledTriangle1(ch , height_width);
  
  printf("2 --> \n");
  RightAngledTriangle2(ch , height_width);
  
  printf("3 --> \n");
  Triangle_Left3(ch , height_width); 
    
  printf("4 --> \n");
  AnIsoscelesTriangle4(ch , height_width);
  
  printf("5 --> \n");
  AnIsoscelesTriangle5(ch , height_width);
  
  printf("6 --> \n");
  Rhombus6(ch , height_width);
 
  return OK;
}

/* Name: Amit Pinhas */
