#include <stdio.h>
#include <ctype.h> /* isalpha , islower */
#include "files.h"


#define A_B_C_DOUBLE_SIZE 52
#define ASCII_A_BIG 65
#define ASCII_A_SMALL 97
#define A_B_C_SIZE 26
 
  
STATUS PutCharInNewFileWithoutSpace(FILE *_oldFile , FILE *_TempFile); 
STATUS RemoveOldFileAndRenameTempFile(char *_NameFile , char *_TempFile);  
STATUS CountLetters(int *_array , FILE *_fileLetters);
void PrintArray(const int *_array);


STATUS SkipSpaces(char *_NameFile , char *_TempFile)
{
     FILE *fileOld , *fileTemp ;
     STATUS result ;  
        
     if ( NULL == _NameFile || NULL == _TempFile)
     {
          return ERR_PTR ;
     }     
     
     fileOld = fopen(_NameFile , "r");     
          
     if ( NULL == fileOld )
     {
          return ERR_FILE_READ ;
     }
     
     fileTemp = fopen(_TempFile , "w");   
     
     if ( NULL == fileTemp )
     {
          return ERR_FILE_WRITE ;
     }     

     PutCharInNewFileWithoutSpace(fileOld , fileTemp);  

     result = RemoveOldFileAndRenameTempFile(_NameFile , _TempFile);
     
     if ( result != OK ) 
     {
          return result;
     }
              
     return OK;
}


STATUS CalculatesFrequenciesLetters(const char *_fileLetters)
{
     FILE *fileLetters ;
     int array[A_B_C_DOUBLE_SIZE]={0};
    
     if ( NULL == _fileLetters )
     {
          return ERR_PTR ;
     }
     
     fileLetters = fopen(_fileLetters , "r");
     
     if ( NULL == fileLetters )
     {
          return ERR_FILE_READ ;
     }
     
     CountLetters(array , fileLetters);
     PrintArray(array);    
     return OK; 
}


STATUS PutCharInNewFileWithoutSpace(FILE *_oldFile , FILE *_TempFile)
{
     char ch ;
     
     ch=fgetc(_oldFile);
     
     while (!feof(_oldFile))
     {
          if (ch != ' ')
          {
               fputc(ch , _TempFile);
          }
          
          ch=fgetc(_oldFile);
     }
     
     fclose(_oldFile);
     fclose(_TempFile);
     return OK;
}


STATUS RemoveOldFileAndRenameTempFile(char *_NameFile , char *_TempFile)
{
     STATUS result1 , result2;
      
     result1=remove(_NameFile); 
     if ( 0 != result1)
     {
          return ERR_REMOVE;
     }

     result2 = rename(_TempFile , _NameFile);
     if ( 0 != result2)
     {
          return ERR_RENAME;
     } 
                      
     return OK;  
}


STATUS CountLetters(int *_array , FILE *_fileLetters)
{
     char ch ;
     
     ch=fgetc(_fileLetters);
     
     while (!feof(_fileLetters))
     {
          if (isalpha(ch))
          {
               if (islower(ch))
               {
                   _array[ch - ASCII_A_SMALL + A_B_C_SIZE] ++ ;
               }
               else
               {
                   _array[ch - ASCII_A_BIG] ++ ;
               }
          }          
          ch=fgetc(_fileLetters);
     }         
     fclose(_fileLetters);
     return OK;
}


void PrintArray(const int *_array)
{
     int index;
     
     for(index=0 ; index<A_B_C_DOUBLE_SIZE ; index++)
     {
          if ( _array[index] != 0 && index<=A_B_C_SIZE-1)
          {
               printf("%c  %d\n" , index+ASCII_A_BIG , _array[index]) ;
          }
          
          if ( _array[index] != 0 && index>A_B_C_SIZE-1)
          {
               printf("%c  %d\n" , index+ASCII_A_SMALL-A_B_C_SIZE , _array[index]) ;
          }                   
     }
}

