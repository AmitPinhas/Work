#define OK 0
#define MAX_SIZE 80
#define MIN_SIZE 1
#define MAX_CHAR '~'
#define MIN_CHAR '!'
#define ERROR_SIZE 2
#define ERROR_CHAR 3


int RightAngledTriangle1(char _ch , unsigned int _height_width);
/*
Description: Print right bottom triangle
$
$$
$$$
Input: Character and Height / Width
Output: OK \ ERROR_SIZE \ ERROR_CHAR
Error: ERROR_CHAR- Character > MAX_CHAR or Character < MIN_CHAR 
       ERROR_SIZE- Height / Width > MAX_SIZE or Height / Width < MIN_SIZE
*/

int RightAngledTriangle2(char _ch , unsigned int _height_width);
/*
Description: Print right-angled triangle
$$$
$$
$
Input: Character and Height / Width
Output: OK \ ERROR_SIZE \ ERROR_CHAR
Error: ERROR_CHAR- Character > MAX_CHAR or Character < MIN_CHAR 
       ERROR_SIZE- Height / Width > MAX_SIZE or Height / Width < MIN_SIZE
*/

int Triangle_Left3(char _ch , unsigned int _width);
/*
Description:Triangle printing with left base
$
$$
$$$
$$
$
Input:Character and  Width
Output: OK \ ERROR_SIZE \ ERROR_CHAR
Error: ERROR_CHAR- Character > MAX_CHAR or Character < MIN_CHAR 
       ERROR_SIZE-  Width > MAX_SIZE or  Width < MIN_SIZE
*/

int AnIsoscelesTriangle4(char _ch , unsigned int _height);
/*
Description:Triangular printing equals calves
  $
 $$$
$$$$$
Input: Character and Height 
Output: OK \ ERROR_SIZE \ ERROR_CHAR
Error: ERROR_CHAR- Character > MAX_CHAR or Character < MIN_CHAR 
       ERROR_SIZE- Height  > MAX_SIZE or Height  < MIN_SIZE
*/

int AnIsoscelesTriangle5(char _ch , unsigned int _height);
/*
Description:Triangular printing equals upper calves
$$$$$
 $$$
  $
Input: Character and Height 
Output: OK \ ERROR_SIZE \ ERROR_CHAR
Error: ERROR_CHAR- Character > MAX_CHAR or Character < MIN_CHAR 
       ERROR_SIZE- Height  > MAX_SIZE or Height < MIN_SIZE
*/

int Rhombus6(char _ch , unsigned int _width);
/*
Description:Rhombus printing
  &
 & &
& & &
 & &
  &
Input:Character and Width
Output: OK \ ERROR_SIZE \ ERROR_CHAR
Error: ERROR_CHAR- Character > MAX_CHAR or Character < MIN_CHAR 
       ERROR_SIZE- Width > MAX_SIZE or  Width < MIN_SIZE
*/


