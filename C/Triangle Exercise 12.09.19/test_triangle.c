#include <stdio.h>
#include "triangle.h"

int main()
{
  char ch;
  int height_width;


  ch=Input_Char();  

  height_width=Input_Height_Width();


  
  RightAngledTriangle1(ch , height_width);

  RightAngledTriangle2(ch , height_width);

  Triangle_Left3(ch , height_width); 

  AnIsoscelesTriangle4(ch , height_width);

  AnIsoscelesTriangle5(ch , height_width);

  Rhombus6(ch , height_width);
 
  return 0;
}

/* Name: Amit Pinhas */
