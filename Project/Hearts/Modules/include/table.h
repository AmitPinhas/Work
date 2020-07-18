#ifndef __TABLE_H__  
#define __TABLE_H__

#include "card.h" 

/* ========================================================== Table typedef ======================================================================= */

  /*struct Table */
typedef struct Table Table;

/* ========================================================== Table API ============================================================================ */
/*
	Description: make pointer to a new table .
	      Input: no input .
 	     Output: new pointer to table / NULL .
	      Error: new pointer to table - pointer creation successfully completed .
	             NULL - allocation failed .
	 complexity: O(1) .     
*/
Table* CreateTable();
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
	Description: free table .
	      Input: address of pointer to table .
	     Output: no output .
	      Error: no error .
	 complexity: O(1) .    
*/
void DestroyTable(Table **_table);
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
	Description: get top suite from the table .
	      Input: pointer to table .
	     Output: suite .
	      Error: no error .
	 complexity: O(1) .    
*/
Suite GetTopSuite(Table *_table); /* for player desicion */
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
	Description: get losser trick and point .
	      Input: a) pointer to table .
	             b) pointer to int variable .
	     Output: index losser player .
	      Error: no error .
	 complexity: O(1) .    
*/
int GetLosserAndPoint(Table *_table , int *_points); /* for trick */
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
	Description: set card in table .
	      Input: a) pointer to table .
	             b) pointer to card .
	             c) index .
	     Output: no output .
	      Error: no error .
	 complexity: O(1) .    
*/
void SetCardInTable(Table *_table , Card *_card , int _index);
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
	Description: get card in table .
	      Input: a) pointer to table .
	             b) index .
	     Output: card .
	      Error: no error .
	 complexity: O(1) .    
*/
Card* GetCardInTable(Table *_table , int _index);
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

void CleanTable(Table *_table);

#endif /* __TABLE_H__ */
