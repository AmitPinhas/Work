#ifndef __TREE_WORDS_H__
#define __TREE_WORDS_H__

typedef struct TreeWords TreeWords;
typedef struct Word Word;

typedef enum
{
     PRE_ORDER,
     IN_ORDER,
     POST_ORDER
     
}TreeTravers;


/*
     Description : make pointer to new binary search tree words .
     Complications : O(1) .
     Input : no input .
     Output : the pointer to the new tree words / NULL .
     ERROR : NULL - pointer is null if allocation failed . 
*/
TreeWords* TreeWordsCreate();

/*
     Description : free the binary search tree words .
     Complications : O(n) .
     Input : 1)pointer to the tree words .
     Output : no output.
     ERROR : no error . 
*/
void TreeWordsDestroy(TreeWords* _tree);

/*
     Description : Reads a text file as input
                   and calculate the frequency of the file's words.
     Complications : O(n) .
     Input : 1) string of the file name .
     Output : ERR_OK / ERR_NOT_INITIALIZED / ERR_ALLOCATION_FAILED / ERR_GENERAL
     ERROR : ERR_OK - The calculation is completed successfully, the result will be printed on the screen .
             ERR_NOT_INITIALIZED - String is null .
             ERR_ALLOCATION_FAILED - Allocation failed .
             ERR_GENERAL - Failed read the file .
*/
ADTErr CalculateFreqOfWords(char *_nameFile);


#endif /* __TREE_WORDS_H__ */
