#include <stdio.h>
#include <ctype.h> /* isalpha */
#include "files.h"

void TestPositiveSkipSpaces();
void TestNegitiveSkipSpacesNullPtrLeft();
void TestNegitiveSkipSpacesNullPtrRight();
void TestNegitiveSkipSpacesNullPtrBoth();
void TestNegitiveSkipSpacesFileReadNotExist();
void TestPositiveCalculatesFrequenciesLetters();
void TestNegitiveCalculatesFrequenciesLettersStringNull();
void TestNegitiveCalculatesFrequenciesLettersFileNotExist();

char pass[]="Pass";
char failed[]="Failed";

int main()
{
     TestPositiveSkipSpaces();
     TestNegitiveSkipSpacesNullPtrLeft();
     TestNegitiveSkipSpacesNullPtrRight();
     TestNegitiveSkipSpacesNullPtrBoth();
     TestNegitiveSkipSpacesFileReadNotExist();
     TestPositiveCalculatesFrequenciesLetters();
     TestNegitiveCalculatesFrequenciesLettersStringNull();
     TestNegitiveCalculatesFrequenciesLettersFileNotExist();
         
     return 1;
}

void TestPositiveSkipSpaces()
{
    STATUS result;
    
    if ( (result=SkipSpaces("space.txt" , "temp.txt")) == OK )
    {
       puts(pass);
    }
    else
    {
       puts(failed);
    }   
}

void TestNegitiveSkipSpacesNullPtrLeft()
{
    STATUS result;
    
    if ( (result=SkipSpaces(NULL , "temp.txt")) == ERR_PTR )
    {
       puts(pass);
    }
    else
    {
       puts(failed);
    }  
}

void TestNegitiveSkipSpacesNullPtrRight()
{
    STATUS result;
    
    if ( (result=SkipSpaces("space.txt" , NULL)) == ERR_PTR )
    {
       puts(pass);
    }
    else
    {
       puts(failed);
    } 
}

void TestNegitiveSkipSpacesNullPtrBoth()
{
    STATUS result;
    
    if ( (result=SkipSpaces(NULL , NULL)) == ERR_PTR )
    {
       puts(pass);
    }
    else
    {
       puts(failed);
    } 
}

void TestNegitiveSkipSpacesFileReadNotExist()
{
    STATUS result;
    
    if ( (result=SkipSpaces("notexist.txt" , "temp.txt")) == ERR_FILE_READ )
    {
       puts(pass);
    }
    else
    {
       puts(failed);
    } 
}

void TestPositiveCalculatesFrequenciesLetters()
{
    STATUS result;
    
    if( (result=CalculatesFrequenciesLetters("letters.txt")) == OK )
    {
       puts(pass);
    }
    else
    {
       puts(failed);
    }     
}

void TestNegitiveCalculatesFrequenciesLettersStringNull()
{
    STATUS result;
    
    if( (result=CalculatesFrequenciesLetters(NULL)) == ERR_PTR )
    {
       puts(pass);
    }
    else
    {
       puts(failed);
    } 
}

void TestNegitiveCalculatesFrequenciesLettersFileNotExist()
{
    STATUS result;
    
    if( (result=CalculatesFrequenciesLetters("notExist.txt")) == ERR_FILE_READ )
    {
       puts(pass);
    }
    else
    {
       puts(failed);
    }
}



