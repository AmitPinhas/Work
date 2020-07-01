#ifndef __FILES_H__
#define __FILES_H__


typedef enum { OK , ERR_PTR , ERR_FILE_READ , ERR_FILE_WRITE , ERR_REMOVE , ERR_RENAME }STATUS ;              


/*
    Description: Turns textual text into Texas without spaces .    
    Input : 1) string of the name file .  
            2) string of the name temp file .           
    Output : OK / ERR_PTR / ERR_FILE_READ / ERR_FILE_WRITE / ERR_REMOVE / ERR_RENAME .       
    Error : OK - The file was successfully updated .
            ERR_PTR - One or both of the strings is null .
            ERR_FILE_READ - Failed to open file for read .  
            ERR_FILE_WRITE - Failed to open file for write .
            ERR_REMOVE - Failed to remove old file . 
            ERR_RENAME - Failed to rename new file .      
    Warning : If the temporary file already exists it will be reset and the information in it will be lost,
              it is recommended to give a temporary file that does not exist. 
    Complexity : O(n)                     
*/
STATUS SkipSpaces(char *_NameFile , char *_TempFile);


/*
    Description: Reads a text file as input
                 and calculates the frequencies of the letters that appear in the input .    
    Input : 1) string of the name file .            
    Output : OK / ERR_PTR / ERR_FILE_READ / ERR_FILE_WRITE / ERR_REMOVE / ERR_RENAME .       
    Error : OK - The calculation was successful,
                 printed to a table screen with all the letters that appeared and how many times each appeared .
            ERR_PTR - the string is null .
            ERR_FILE_READ - Failed to open file for read .  
    Complexity : O(n)                      
*/
STATUS CalculatesFrequenciesLetters(const char *_fileLetters);


#endif /* __FILES_H__ */
