#include <stdlib.h>  /* allocation */
#include "card.h" /* API statements */

/* ------------------- define -------------- */ 
#define POINT_HEART_CARD 1
#define POINT_SPADES_QUEEN_CARD 13
#define POINT_REGULAR_CARD 0

/* ------------------- struct --------------- */

struct Card
{
	Rank m_rank;
	Suite m_suite;
	int m_point;
};

/* --------------- local func --------------- */
static int GetPointCard(Suite _suite ,Rank _rank);


/* ============ Card API func ============== */

/* -------------Create Card----------------- */
Card* CreateCard(Suite _suite ,Rank _rank)
{
	Card *ptrNewCard ;
		 
	ptrNewCard = (Card*)malloc( sizeof(Card) ) ;
	if ( NULL == ptrNewCard )
	{
		return NULL ;
	}

     ptrNewCard -> m_point = GetPointCard( _suite , _rank);	
	ptrNewCard -> m_suite = _suite ;
	ptrNewCard -> m_rank = _rank ;
	
	return ptrNewCard ;
}
/* ------------------Destroy Card------------ */
void DestroyCard(Card **_card)
{
	if ( (_card != NULL) && (*_card != NULL) )
	{
		free(*_card) ;		
	}
	
	*_card = NULL;
}
/* ------------------Get Suite--------------- */

Suite GetSuite( const Card *_card )
{
	if ( _card != NULL )
	{
	  return _card -> m_suite ;
	}
	return -1;	
}
/* ------------------Get Rank---------------- */

Rank GetRank ( const Card *_card )
{
	if ( _card != NULL )
	{
	  return _card -> m_rank ;
	}
	return -1;	 
}
/* ----------------Get Point----------------- */
int GetPoint(const Card *_card)
{
	return _card->m_point ;                         
}

/* ============== local func ================= */

/* ----------- Get point card ----------------- */
static int GetPointCard(Suite _suite ,Rank _rank)
{	
	if ( HEART == _suite )
	{
		return POINT_HEART_CARD ;
	}
	if ( (SPADES == _suite) && (QUEEN == _rank) )
	{
		return POINT_SPADES_QUEEN_CARD ;
	}
	
	return POINT_REGULAR_CARD ;
}
