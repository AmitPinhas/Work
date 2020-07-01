#define OK 111
#define BASE 10
#define ERROR_POINTER -1
#define NO_PALINDROME -2
#define ALL_SPACE -3
#define ERROR_FIRST_ALPHA -4
#define ERROR_SIZE_INT -6
#define MAX_DIGIT_INT 10
#define MIN_DIGIT 0
#define MAX_DIGIT 9
#define ERROR_NEGATIVE -12
/*
    Description: Gets a string and returns its Revers string.
                 example - str:abc , reverse str: cba.
	Input: A string of characters.
    Output: OK / ERROR_POINTER.
    Error: OK - The string was successfully changed  
           ERROR_POINTER - str == NULL
*/
int Reverse_String(char *_str);

/*
    Description: Gets a string and returns if the string is palindrome.
                 example - str:abcba --> 1 (palindrome) , str: abc --> 0 (not palindrome) .
    Input: A string of characters.
    Output: OK / ERROR_POINTER / NO_PALINDROME.
    Error: OK - The string is palindrome.
           NO_PALINDROME - The string is not palindrome.
           ERROR_POINTER - str == NULL.
*/
int Is_Palindrome(char *_str);

/*
      Description: Convert string to an integer value
      Input: A string of characters and numbers.
      Output: OK / ERROR_POINTER / ALL_SPACE /  ERROR_FIRST_ALPHA / ERROR_SIZE_INT. 
      Error: OK - return result with the number.
             ERROR_POINTER - str == NULL.
             ALL_SPACE - all the stirng is ' ' only.
             ERROR_FIRST_ALPHA - string start with alpha.
             ERROR_SIZE_INT - the string exceeds the boundraies of an integer.
      Warning: Max value int is 2,147,483,647 , Min value int is -2,147,483,647

*/
int My_Atoi(char *_str ,int *_result);

/*
      Description: Convert integer value to an string.
      Input: integer value.
      Output: OK / ERROR_POINTER . 
      Error: OK - Conversion completed successfully.
             ERROR_POINTER - str == NULL.
     
*/
int My_Itoa(char *_str_result ,int _number);

/*
      Description: the function get input from keyboard any decimal/binary numbers and converts them into binary/decimal numbers and prints out the result.
      Input: char d (decimal) or b (binary) and a string with the decimal/binary number.
      Output: OK / ERROR_POINTER . 
      Error: OK - Conversion completed successfully.
             ERROR_POINTER - str == NULL.    
*/
int Convert_Bin_Dec(char _ch , char _number[] , char _num_result[]);

int Squeeze(char _s1[] , char _s2[]);

