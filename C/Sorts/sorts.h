#ifndef __SORTS_H__   /* Avoid duplicate statements */ 
#define __SORTS_H__

/* (Vector *_vec) */
#include "../vector/vector.h"  


/* ================================================== API =========================================================== */

/*
	   Description : Sorting a vector with bubble sort .
	         Input : pointer to the vector .
	        Output : ERR_OK / ERR_NOT_INITIALIZED .
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	    Complexity : Worst case - O(N^2) .
	                 Typical case - O(N^2) .
	                 Best case - O(N) .
   Place complexity : inplace .  
	     Stability : yes .           
*/
ADTErr BubbleSort(Vector *_vec);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with shake sort .
	         Input : pointer to the vector .
	        Output : ERR_OK / ERR_NOT_INITIALIZED .
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	    Complexity : Worst case - O(N^2) .
	                 Typical case - O(N^2) .
	                 Best case - O(N) .
   Place complexity : inplace .  
	     Stability : yes .           
*/
ADTErr ShakeSort(Vector *_vec);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with Insertion Sort .
	         Input : pointer to the vector .
	        Output : ERR_OK / ERR_NOT_INITIALIZED .
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	    Complexity : Worst case - O(N^2) .
	                 Typical case - O(N^2) .
	                 Best case - O(N) .
   Place complexity : inplace .  
	     Stability : yes .           
*/
ADTErr InsertionSort(Vector *_vec);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with Selection Sort .
	         Input : pointer to the vector .
	        Output : ERR_OK / ERR_NOT_INITIALIZED .
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	    Complexity : Worst case - O(N^2) .
	                 Typical case - O(N^2) .
	                 Best case - O(N^2).
   Place complexity : inplace .  
	     Stability : yes .           
*/
ADTErr SelectionSort (Vector *_vec);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with Shell Sort .
	         Input : pointer to the vector .
	        Output : ERR_OK / ERR_NOT_INITIALIZED .
       	    Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	    Complexity : Worst case - O(N^2) .
	                 Typical case - O(N^4/3) .
	                 Best case - O(N).
   Place complexity : inplace .  
	     Stability : no .           
*/
ADTErr ShellSort (Vector *_vec);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with Quick Sort .
	         Input : pointer to the vector .
         	   Output : ERR_OK / ERR_NOT_INITIALIZED .
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	    Complexity : Worst case - O(N^2) .
	                 Typical case - O(n log n) .
	                 Best case - O(n log n) .
   Place complexity : inplace .  
	     Stability : no .           
*/
ADTErr QuickSort (Vector *_vec);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with Quick Sort .
	         Input : pointer to the vector .
         	   Output : ERR_OK / ERR_NOT_INITIALIZED .
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	    Complexity : Worst case - O(N^2) .
	                 Typical case - O(n log n) .
	                 Best case - O(n log n) .
   Place complexity : inplace .  
	     Stability : no .           
*/
ADTErr QuickSortIterative (Vector *_vec);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with Merge Sort .
	         Input : pointer to the vector .
	        Output : ERR_OK / ERR_NOT_INITIALIZED / ERR_GENERAL / ERR_ALLOCATION_FAILED .
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	    Complexity : Worst case - O(n log n) .
	                 Typical case - O(n log n) .
	                 Best case - O(n log n) .
   Place complexity : O(N) .   
	     Stability : yes .           
*/
ADTErr MergeSort (Vector *_vec);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with Merge Sort .
	         Input : pointer to the vector .
	        Output : ERR_OK / ERR_NOT_INITIALIZED / ERR_GENERAL / ERR_ALLOCATION_FAILED .
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	    Complexity : Worst case - O(n log n) .
	                 Typical case - O(n log n) .
	                 Best case - O(n log n) .
   Place complexity : O(N) .   
	     Stability : yes .           
*/
ADTErr MergeSortIterative (Vector *_vec);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with Counting Sort .
	         Input : a) pointer to the vector .
	                 b) min value.
	                 c) max value.
	        Output : ERR_OK / ERR_NOT_INITIALIZED / ERR_GENERAL / ERR_ALLOCATION_FAILED .
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	                 ERR_GENERAL - if min value big than max value .
	                 ERR_ALLOCATION_FAILED - allocation failed .
	    Complexity : Worst case - O(N) .
	                 Typical case - O(N) .
	                 Best case - O(N) .
   Place complexity : O(N) .   
	     Stability : yes .           
*/
ADTErr CountingSort (Vector *_vec , int _minValue , int _maxValue);
/*-----------------------------------------------------------------------*/

/*
	   Description : Sorting a vector with Counting Sort .
	         Input : a) pointer to the vector .
	                 b) number digits of the max value in the vector .          
	        Output : ERR_OK / ERR_NOT_INITIALIZED / ERR_GENERAL / ERR_ALLOCATION_FAILED .  
	         Error : ERR_OK - the function sorts the vector successfully .
	                 ERR_NOT_INITIALIZED - pointer to the vector is null .
	                 ERR_ALLOCATION_FAILED - allocation failed .
	                 ERR_GENERAL - number of digit is nagitive number .	              
	    Complexity : Worst case - O(N) .
	                 Typical case - O(N) .
	                 Best case - O(N) .	              
   Place complexity : O(N) .   
	     Stability : yes .           
*/
ADTErr RadixSort (Vector *_vec , int _nDigits);
/*-----------------------------------------------------------------------*/


#endif /* __SORTS_H__ */

