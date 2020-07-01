#include <stdio.h>
#include <string.h>
#include "e_string.h"
#include <ctype.h>

int Swap_ch(char *_ch1 , char *_ch2);
int Skipping_Space(char *_str ,int *_index);
int First_Checks(char *_str ,int *_index, int *_negative ,int *_result);
int Reverse_num(int *_num_tmp ,int _number);
int Pow(int _base , int _pow);
int Convert_To_Bin(char _str[] , char *_bin_result);
int Convert_To_Dec(char _str[] , char *_dec_result);
int Convert_Num(char *_bin_result,int *_number);


int Reverse_String(char *_str)
{	
    int index_first , index_last;    
    
	if( _str == NULL )
	{
	    return ERROR_POINTER;
	}
	
	for(index_first=0 , index_last=strlen(_str)-1 ;  index_first<index_last ; index_first++ , index_last--)
	{
	    Swap_ch(&_str[index_first] , &_str[index_last]);
	}
	
	return OK;
}


int Is_Palindrome(char *_str)
{   
    int index_first , index_last;    
    
	if( _str == NULL )
	{
	    return ERROR_POINTER;
	}
	
	for(index_first=0 , index_last=strlen(_str)-1 ;  index_first<index_last ; index_first++ , index_last--)
	{
	    if(_str[index_first] != _str[index_last])
	    {
	       printf("no palindrome\n");
	       return NO_PALINDROME;
	    }
	}
	
       printf("palindrome\n");
       return OK;
}


int My_Atoi(char *_str ,int *_result)
{
    int index=0, result_check , negative=0 , count_digits;
    double result_check2=0;    
    
	if( (result_check=First_Checks(_str , &index , &negative , _result)) != OK )
	{
	      return result_check;
	}
			
	for(; _str[index] != '\0' ; index++ )
	{	
    
   	    if(_str[index]-'0' >= MIN_DIGIT && _str[index]-'0' <= MAX_DIGIT)
	    {       
	        result_check2 *=BASE;
	        result_check2 +=_str[index] - '0';
	    }
	    else 
	    {
             break;
	    }
	}
		

	
     *_result=(int)result_check2;
     
     if(negative)
     {
      *_result *=-1;
     } 
    
	return OK;
	
}

int My_Itoa(char *_str_result ,int _number)
{
    int num_tmp=0 , index=0 ; 
    
    
        if( _str_result == NULL )
       	{
	       return ERROR_POINTER;
	    }
	    
	    if(_number == 0)
	    {
	      _str_result[index++] = '0';
	      
	      _str_result[index] = '\0';
	
		return OK;
	    }
	
        if(_number<0)
        {
           _str_result[index] = '-';
           index++;
           _number = -_number;
        }
        
        Reverse_num(&num_tmp , _number);             
	
    	for( ; num_tmp%10 != 0  ; index++ ,  num_tmp/=10 )
    	{
    	    _str_result[index] =  (num_tmp%10) + '0';
	    }
	
    	_str_result[index] = '\0';
	
	
	return OK;
}

int Convert_Bin_Dec(char _ch, char _number[]  , char _num_result[])
{
     if(_ch == 'd')
     {
          Convert_To_Bin(_number ,_num_result);
     }
     
     if(_ch == 'b')
     {
          Convert_To_Dec(_number , _num_result);    
     }
     
     return OK;
}

int Swap_ch(char *_ch1 , char *_ch2)
{
    char tmp;
    
    tmp=*_ch1;
    *_ch1 = *_ch2;
    *_ch2= tmp;
    
    return OK;
}

int Skipping_Space(char *_str ,int *_index)
{
    
   for( ; _str[*_index] != '\0' ; *_index+=1)
    {
      if(_str[*_index] != ' ')
      {
            return OK;
      }
    }

    return ALL_SPACE; 
    
}

int First_Checks(char *_str ,int *_index , int *_negative,int *_result)
{
    int result_space ;
    
      if( _str == NULL || _result == NULL )
	{
	    return ERROR_POINTER;
	}
     
      else if ( (result_space=Skipping_Space(_str , _index)) != OK )
	{
	    return result_space;
	} 
	
      else if(_str[*_index] == '+')
	{
	    
	    *_index+=1;
	    return OK;
	}
	
	else if(_str[*_index] == '-')
	{

	    *_negative=1;
	    *_index+=1;
	    return OK;
	}
	
     else if(isalpha(_str[*_index]))
	{
	    return ERROR_FIRST_ALPHA;
	}

	return OK;
}

int Reverse_num(int *_num_tmp ,int _number)
{
    while(_number%10 > 0)
    {   
        *_num_tmp *=BASE;
        *_num_tmp +=_number%10;
        _number /=10;
    }
    
    return OK;
}

int Pow(int _base , int _pow)
{
     int number=1 , index=0;
     
     for(;index<_pow;index++)
     {
      number *=_base;
     }
     return number;
}

int Convert_To_Bin(char _str[] , char *_bin_result)
{
        int number=0 , index=0 ;
     
          My_Atoi(_str ,&number);
          
          if( number < 0)
          {
               return ERROR_NEGATIVE;
          }
          
          if( 0 == number)
          {
               _bin_result[index++] = '0';
                _bin_result[index] = '\0';
               return OK;
          }
          
          Convert_Num(_bin_result, &number);


          return OK;
          
}

int Convert_To_Dec(char _str[] , char *_dec_result)
{
     int index , pow , num_tmp , number=0 ;
     
     
          for(index=0 , num_tmp=0 , pow=strlen(_str)-1  ; _str[index] != '\0' ; index++ , pow--)
          {
               if(_str[index] == '1')
               {
               num_tmp= Pow(2,pow);
               number +=num_tmp; 
               }
          }
                   
          My_Itoa(_dec_result ,number);
     
     return OK;
}

int Convert_Num(char *_bin_result,int *_number)
{
     int index=0;
     
          while(*_number != 0)
          {
               if(*_number%2 == 0)
               {
                    _bin_result[index] = '0';
                    index++;
                    *_number/=2;
               }
               else 
               {
                    _bin_result[index] = '1';
                    index++;
                    *_number/=2;
               }
          }
          
          _bin_result[index] = '\0';
          
          Reverse_String(_bin_result);
          
          return OK;
}

