#ifndef __BIT_H__
#define __BIT_H__


/*
     Description : a function Bitcount , that counts bits set to 1 in an unsigned int number .
     Input : 1) unsigned int number .
             2) address of size_t count variable .
     Output : ERR_OK / ERR_NOT_INITIALIZED . 
     Error : ERR_OK - the bit count has ended successfully,
                      the count result is in the count variable passed to the function . 
             ERR_NOT_INITIALIZED - The count variable address passed to the function is null .
     Complexity : O(1) .
*/
ADTErr BitCount(unsigned int _number , size_t *_count);


/*
     Description : a function that inverts the bits of an unsigned char binary num
                   and stores answer in new unsigned char binary num .
     Input : 1) unsigned char number .
             2) address of unsigned char new binary num variable .
     Output : ERR_OK / ERR_NOT_INITIALIZED . 
     Error : ERR_OK - the inverst was successful, the results are printed to the screen
                      and the result is stored in the new variable sent to the function .
             ERR_NOT_INITIALIZED - the new binary num variable address passed to the function is null .
     Complexity : O(1) .
*/
ADTErr InverstBits(unsigned char _binaryNum , unsigned char *_NewBinaryNum);


/*
     Description : a function that rotates to the right by number of moves bit positions
                   the bits of an unsigned char binary num , no bits are lost in this process .
     Input : 1) unsigned char number .
             2) number of moves (only positive number) .
     Output : ERR_OK . 
     Error : ERR_OK - the sliding was performed successfully,
                      in addition to the number before sliding and after followed by a screen print .
     Complexity : O(1) .
*/
ADTErr RotatesToTheRight(unsigned char _binaryNum , size_t _numberOfMoves);


/*
     Description : a function setbits that returns binary num with the num of bit from
                   binary num two that begin at position set to the rightmost num of bit of an
                   unsigned char variable binary num two . 
     Input : 1) unsigned char number .
             2) unsigned char number two .
             3) position .
             4) num of bit .
     Output : ERR_OK / ERR_WORNG_INDEX . 
     Error : ERR_OK - the set bits was performed successfully,
                      in addition to the number before and after set bits followed by a screen print .
             ERR_WORNG_INDEX - num of bit > size bits , position > size bits , position == 0 .      
     Complexity : O(1) .
*/
ADTErr SetBits(unsigned char _binaryNum , unsigned int _position , unsigned int _numOfBit , unsigned char _binaryNumTwo);


/*
     Description : a function that multiplies two unsigned short .
     Input : 1) unsigned short number 1 .
             2) unsigned short number 2 .
             3) Address of a double type variable in which we will store the result . 
     Output : ERR_OK / ERR_NOT_INITIALIZED .
     Error : ERR_OK - the calculation is done successfully, the result is stored in the variable sent .
             ERR_NOT_INITIALIZED - the result variable address passed to the function is null .     
     Complexity : O(1) .
*/
ADTErr Multiplies(unsigned short _num1 ,unsigned short _num2 , double *_result); 


/*
     Description : a function that setbits that sets the bits from index to index to given value ( 0 or 1 ) .
     Input : 1) unsigned char number pointer .
             2) index from .
             3) index to .
             4) value . 
     Output : ERR_OK / ERR_WORNG_INDEX / ERR_NOT_INITIALIZED .
     Error : ERR_OK - the set bits is done successfully .
             ERR_WORNG_INDEX -  to > from , from > size bits , value != 0 && value != 1 . 
             ERR_NOT_INITIALIZED - pointer null .    
     Complexity : O(1) .
*/
ADTErr SetBitsTwo(unsigned int *_num1 , int _from , int _to , int _value);

/*
     Description : a function that recieves as a parameter 'C' string 
                   and compresses it in a way that each letter takes
                   only 4 bits .
     Input : 1) string (only from 15 letters : a-o ) .
     Output : ERR_OK / ERR_GENERAL / ERR_NOT_INITIALIZED .
     Error : ERR_OK - the change done successfully . 
             ERR_NOT_INITIALIZED - pointer null .    
     Complexity : O(n) .
*/
ADTErr CompressString(char *_str);

#endif /* __BIT_H__ */
