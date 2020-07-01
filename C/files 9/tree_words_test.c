#include <stdio.h>
#include "ADTDefs.h"
#include "tree_words.h"

void PositiveTreeWordsCreate();
void NullTreeWordsDestroy();
void DoubleFreeTreeWordsDestroy();

char pass[]="pass";
char failed[]="failed";

int main()
{
     PositiveTreeWordsCreate();
     NullTreeWordsDestroy(); 
     DoubleFreeTreeWordsDestroy();
     CalculateFreqOfWords("alice in wonderland.txt");
     return 1;
}

void PositiveTreeWordsCreate()
{
     TreeWords *ptrTree ;
     
     ptrTree = TreeWordsCreate();
     
     if ( NULL != ptrTree )
     {
          puts(pass);
     }
     else
     {
          puts(failed);
     }
     
     TreeWordsDestroy(ptrTree);
}

void NullTreeWordsDestroy()
{
    TreeWordsDestroy(NULL); 
    
    puts(pass);
}

void DoubleFreeTreeWordsDestroy()
{
     TreeWords *ptrTree ;
     
     ptrTree = TreeWordsCreate();
     
     TreeWordsDestroy(ptrTree);  
     TreeWordsDestroy(ptrTree);  
     
     puts(pass); 
}

