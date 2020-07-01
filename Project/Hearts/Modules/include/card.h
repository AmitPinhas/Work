#ifndef __CARD_H__  /* Avoiding a double statement */
#define __CARD_H__

/* ========================================================== Card typedef ======================================================================== */ 

  /* rank card */
typedef enum { TWO , THREE , FOUR , FIVE , SIX , SEVEN , EIGHT , NINE , TEN , JACK , QUEEN , KING , ACE } Rank ;

  /* suite card */
typedef enum { HEART , SPADES , DIAMOND , CLUB } Suite ;

  /*struct card */
typedef struct Card Card;


/* ========================================================== Card API ============================================================================ */ 
/*
	Description: make pointer to a new card .
	      Input: a) suite .
	             b) rank .
	     Output: new pointer to card / NULL .
	      Error: new pointer to card - pointer creation successfully completed .
	             NULL - allocation failed .
	 complexity: O(1) .     
*/
Card* CreateCard(Suite _suite ,Rank _rank);

/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: free pointer card and null this pointer .
	      Input: address of pointer to card .
	     Output: no output .
	      Error: no error .
	 complexity: O(1) . (destroy one card)    
*/
void DestroyCard(Card **_card);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: get suite card .
	      Input: a) pointer to card .
	     Output: suite  .
	      Error: no error  .	             
	 complexity: O(1) .     
*/
Suite GetSuite( const Card *_card );
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: get rank card .
	      Input: a) pointer to card .
	     Output: rank  .
	      Error: no error  .	             
	 complexity: O(1) .     
*/
Rank GetRank( const Card *_card );
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: get point card .
	      Input: a) pointer to card .
	     Output: int point  .
	      Error: no error  .	             
	 complexity: O(1) .     
*/
int GetPoint(const Card *_card);



#endif /* __CARD_H__ */
