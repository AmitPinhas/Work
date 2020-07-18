#ifndef __DECK_H__  /* Avoiding a double statement */
#define __DECK_H__

#include "card.h" /* Card API statements */

/* =============== Deck typedef ============= */

  /*struct Deck */
typedef struct Deck Deck;

/* ================ Deck API =============== */
/*
	Description: make pointer to a new deck .
	      Input: no input .
 	     Output: new pointer to deck / NULL .
	      Error: new pointer to deck - pointer creation successfully completed .
	             NULL - allocation failed .
	 complexity: O(1) .     
*/
Deck* CreateDeck();
/* ------------------------------------------ */
/*
	Description: free deck .
	      Input: address of pointer to deck .
	     Output: no output .
	      Error: no error .
	 complexity: O(1) .    
*/
void DestroyDeck(Deck **_deck);
/* ----------------------------------------- */
/*
	Description: delete card in the index recive from the deck .
	      Input: a)pointer to deck .
	             b)index .
	     Output: pointer to the the card .
	      Error: no error .
	 complexity: O(1) .    
*/
Card* GetCardFromDeck(Deck *_deck , int _index);
/* ------------------------------------------- */
/*
	Description: set card to deck .
	      Input: a)pointer to deck .
	             b)index .
	             c) pointer to card .
	     Output: no output .
	      Error: no error .
	 complexity: O(1) .    
*/
void SetCardToDeck(Deck *_deck , int _index , Card *_card);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: shuffle the deck .
	      Input: a)pointer to deck .
	     Output: no output .
	      Error: no error .
	 complexity: O(n) .    
*/
void ShuffleDeck(Deck *_deck);

#endif /* __DECK_H__ */
