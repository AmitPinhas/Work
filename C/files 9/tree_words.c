#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */
#include "ADTDefs.h"
#include "tree_words.h"

#define MAGIC_NUM 28011993
#define SIZE_WORD 50
#define TRUE 1
#define FALSE 0

struct TreeWords
{
     Word* m_root;
     int m_magicNum;
};

struct Word 
{
     char word[SIZE_WORD];
     int m_count;
     Word* m_right;
     Word* m_left;
     Word* m_father;
};

void TreeWordsDestroyRec(Word* _word);
Word* TreeIswordFoundAndIncOrLocation(TreeWords* _tree , char *_word , Word *_ptrWordPrev);
Word* FindLocation(Word *_ptrCurr, Word *_ptrPrev , char *_word );
Word* CreatWord(char *_word);
void TreePrint(TreeWords* _tree , TreeTravers _traverseMode);
void PreOrderRec(Word *_word);
void InOrderRec(Word *_word);
void PostOrderRec(Word *_word);
ADTErr BootRoot(TreeWords *_treeWords , Word *_ptrNewWord, char *_word );


ADTErr CalculateFreqOfWords(char *_nameFile)
{
     TreeWords *treeWords ;
     FILE *ptrFile ;
     char word[SIZE_WORD];
     int result ;
     Word  *ptrWordprev , *ptrNewWord ;
     
     
     if ( NULL == _nameFile )
     {
         return ERR_NOT_INITIALIZED;
     }     
     
     treeWords = TreeWordsCreate();
     
     if ( NULL ==  treeWords )
     {
         return ERR_ALLOCATION_FAILED ; 
     }  
     
     ptrFile = fopen(_nameFile , "r");
     if ( NULL == ptrFile )
     {
        return ERR_GENERAL ;
     }
     
     fscanf(ptrFile , "%49s" , word);
     ptrNewWord = CreatWord(word);
     
     BootRoot(treeWords , ptrNewWord , word);
      
     fscanf(ptrFile , "%49s" , word);      
     
     while (!feof(ptrFile))
     {
          if ( (ptrWordprev = TreeIswordFoundAndIncOrLocation(treeWords , word  , ptrWordprev)) != NULL )
          {
               ptrNewWord = CreatWord(word);               
               ptrNewWord->m_father = ptrWordprev;
               if (strcmp(ptrWordprev->word , word) < 0)
               {
                  ptrWordprev -> m_right = ptrNewWord;  
               }
               else
               {
                  ptrWordprev -> m_left = ptrNewWord;  
               }
          } 
          
        fscanf(ptrFile , "%49s" , word);      
     } 
          
     fclose(ptrFile);
     
     TreePrint(treeWords , PRE_ORDER); 
     
     TreeWordsDestroy(treeWords);   
              
     return ERR_OK;
}


TreeWords* TreeWordsCreate()
{
     TreeWords *ptrTree ;
     
     if( (ptrTree = (TreeWords*)malloc(sizeof(TreeWords))) == NULL )
     {
          return NULL ;
     }
     
     ptrTree->m_root = NULL ;
     ptrTree->m_magicNum = MAGIC_NUM ;
     return ptrTree;     
}

void TreeWordsDestroy(TreeWords* _tree)
{
     if ( NULL == _tree || (_tree->m_magicNum != MAGIC_NUM) )
     {
          return;
     }
     
     _tree->m_magicNum = 0 ;    
     TreeWordsDestroyRec(_tree-> m_root);    
     free(_tree);
}

void TreeWordsDestroyRec(Word* _word)
{
     if ( _word == NULL)
     {
          return;
     }    
     TreeWordsDestroyRec( _word -> m_right );
     TreeWordsDestroyRec( _word -> m_left );    
     free( _word );
}

Word* TreeIswordFoundAndIncOrLocation(TreeWords* _tree , char *_word , Word *_ptrWordPrev)
{
     ADTErr result ;
     
     if ( NULL == _tree || NULL == _word )
     {
          return NULL ;
     }
     
     _ptrWordPrev = _tree->m_root;
     
     if ( (_ptrWordPrev=FindLocation(_tree->m_root ,_ptrWordPrev , _word )) != NULL ) 
     {
          return _ptrWordPrev ;
     }

        return NULL ;   
     
}

Word* FindLocation(Word *_ptrCurr, Word *_ptrPrev , char *_word )
{ 
     int check=0 ;
          
     while ( _ptrCurr != NULL )
     {
          _ptrPrev =  _ptrCurr ;
          check = strcmp(_ptrCurr->word , _word) ;    
          
          if ( check == 0 )
          {
               _ptrCurr->m_count ++ ;
               return NULL;
          }
               
          if ( check > 0 )
          {
             _ptrCurr = _ptrCurr->m_left ;
          } 
          else
          {
             _ptrCurr = _ptrCurr->m_right ;
          }
     }
     
     return _ptrPrev ; 
}

Word* CreatWord(char *_word)
{
     Word *ptrWord;
     
     if ( NULL == _word )
     {
          return NULL ;
     } 
     
     ptrWord = (Word*)malloc(sizeof(Word));
     if ( NULL == ptrWord )
     {
         return NULL ;
     } 
     
     strcpy(ptrWord->word , _word);
     ptrWord -> m_count = 1 ;
     ptrWord -> m_right = NULL ;
     ptrWord -> m_left = NULL ;      
     ptrWord -> m_father = NULL ;
     
     return ptrWord ;
}

void TreePrint(TreeWords* _tree , TreeTravers _traverseMode)
{
     if ( NULL == _tree )
     {
          return ;
     }
     
     switch(_traverseMode)
     {
          case PRE_ORDER:
                       PreOrderRec(_tree->m_root);
                       putchar('\n');
                       break;
                       
          case IN_ORDER:
                       InOrderRec(_tree->m_root);
                       putchar('\n');
                       break;
                         
          case POST_ORDER:
                       PostOrderRec(_tree->m_root);
                       putchar('\n');
                       break;
                         
          default:
                  break;                                             
     }
}

void PreOrderRec(Word *_word)
{
     if ( NULL == _word )
     {
          return;
     }
     
     printf("%-10s " , _word->word);
     printf ("%d" , _word->m_count);
     putchar('\n');
     
     PreOrderRec(_word->m_left);
     PreOrderRec(_word->m_right);
}
void InOrderRec(Word *_word)
{
     if ( NULL == _word )
     {
          return;
     }
          
     PreOrderRec(_word->m_left);
     
     printf("%-10s " , _word->word);
     printf ("%d" , _word->m_count);
     putchar('\n');
         
     PreOrderRec(_word->m_right);
}
void PostOrderRec(Word *_word)
{
     if ( NULL == _word )
     {
          return;
     }
          
     PreOrderRec(_word->m_left);
         
     PreOrderRec(_word->m_right);
     
     printf("%-10s " , _word->word);
     printf ("%d" , _word->m_count);
     putchar('\n');
}

ADTErr BootRoot(TreeWords *_treeWords , Word *_ptrNewWord, char *_word )
{
     if ( _treeWords -> m_root == NULL)
      {
        strcpy(_ptrNewWord->word ,_word) ;
        _ptrNewWord -> m_count = 1;
        _ptrNewWord->m_right = NULL;  
        _ptrNewWord->m_left = NULL; 
        _ptrNewWord->m_father = _treeWords -> m_root ;
        _treeWords -> m_root = _ptrNewWord ;
      } 
      
      return ERR_OK;
}

