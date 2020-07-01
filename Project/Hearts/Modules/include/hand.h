#ifndef __HAND_H__  /* Avoiding a double statement */
#define __HAND_H__

#include "card.h" 

/* ======================================================== Hand typedef =========================================================================== */

  /*struct Hand */
typedef struct Hand Hand;

/* ========================================================== Hand API ============================================================================= */
/*
	Description: make pointer to a new hand .
	      Input: no input .
 	     Output: new pointer to hand / NULL .
	      Error: new pointer to hand - pointer creation successfully completed .
	             NULL - allocation failed .
	 complexity: O(1) .     
*/
Hand* CreateHand();
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: free hand .
	      Input: address to pointer to hand .
 	     Output: no output .
	      Error: no error .
*/
void DestroyHand(Hand **_hand);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */

int GetHighCardFromSuite(Suite _suite , Hand *_hand);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
int GetHighCardFromHand( Hand *_hand);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: sort the hand .
	      Input: a) pointer to hand .
	             b) min value of the hand .
	             c) max value of the hand .
 	     Output: no output .
	      Error: no error .
*/
int SortHand(Hand *_hand , int _minValue , int _maxValue);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: set card in the hand .
	      Input: a) pointer to hand .
	             b) index .
	             c) pointer to card .
 	     Output: no output .
	      Error: no error .
	 complexity: O(1) .    	      
*/
void SetCardToHand(Hand *_hand , int _index , Card *_card);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: check is there is card of two club in the hand .
	      Input: pointer to hand .
 	     Output: True / False .
	      Error: True - there is this card in the hand .
	             False - this card not exist in this hand .
*/
int CheckHandIfTwoClub(Hand *_hand);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
Card* GetCardFromHand(Hand *_hand , int _index);

#endif /* __HAND_H__ */
