#include <stdlib.h> /* allocation */
#include <time.h> /* srand for shuffle */
#include "deck.h" /* API statements */

/* --------------- define --------------------- */

 /* in deck there is 52 cards */
#define FULL_DECK_SIZE 52

 /* there is 4 suite */
#define SIZE_SUITE 4

 /* the rank is 13 */
#define SIZE_RANK 13

/* --------------- struct ----------------- */

struct Deck
{
	Card **m_arrayCards;
	size_t m_originalSize;  /* original allocated space for items */
	size_t m_nCards;        /* actual number of cards */          
};

/* ----------- local function -------------- */

 /* destroy all the cards in the deck */
static void DestroyCards(Deck *_deck);

 /* swap between card one and card two */
static void SwapCard(Deck *_deck , int _indexOne , int _indexTwo );

static void InitDeck(Deck *_newDeck);	

/* =========== Card API func =============== */

/* ------------Create Deck------------------ */

Deck* CreateDeck()
{
	Deck *newDeck;
	
	newDeck = (Deck*)calloc(1 , sizeof(Deck)) ;
	
	if ( NULL == newDeck )
	{
		return NULL;
	}
	
	newDeck -> m_arrayCards = (Card**)calloc(FULL_DECK_SIZE , sizeof(Card*) ) ;
	
	if ( NULL == newDeck -> m_arrayCards )
	{
		free(newDeck);
		return NULL ;
	}

     InitDeck(newDeck);		
	
	return newDeck ;
}

/* -------------Destroy Deck------------------ */

void DestroyDeck(Deck **_deck)
{
	if ( NULL != *_deck )
	{
		DestroyCards( *_deck );
		free ( *_deck ) ;
		*_deck = NULL ;
	}
}

/* --------Delete Card From Deck-------------- */

Card* GetCardFromDeck(Deck *_deck , int _index)
{
	Card *tmpPtrCard ;
	
	tmpPtrCard = _deck -> m_arrayCards[_index] ;
	_deck -> m_arrayCards[_index] = NULL ;
	return tmpPtrCard;
}

/* -----------Set Card To Deck-------------- */
void SetCardToDeck(Deck *_deck , int _index , Card *_card)
{
	free(_deck -> m_arrayCards[_index]);
	_deck -> m_arrayCards[_index] = _card ;
	_deck -> m_nCards++;
}



/* -------------Shuffle Deck---------------- */

void ShuffleDeck(Deck *_deck)
{
	int shuffle , cardIndexOne , cardIndexTwo;
	
	srand(time(0)); 
	
	for ( shuffle = 50 ; shuffle > 0 ; shuffle-- )
	{
	     cardIndexOne = ( rand() % _deck->m_nCards ) ;
	     cardIndexTwo = ( rand() % _deck->m_nCards ) ;
          SwapCard(_deck , cardIndexOne ,cardIndexTwo); 	     	
	} 
}

/* ----------- local function --------------- */

static void DestroyCards(Deck *_deck)
{
	int index ;
	
	for ( index = 0 ; index < _deck -> m_nCards ; index++ )
	{
	   DestroyCard( &_deck->m_arrayCards[index] );
	   _deck->m_arrayCards[index] = NULL ;
	}
		free ( _deck->m_arrayCards ) ;		
}

/* ------------------------------------------ */

static void SwapCard(Deck *_deck , int _indexOne , int _indexTwo )
{
	Card *ptrTmpCard;
	
     ptrTmpCard =  _deck -> m_arrayCards[_indexOne];
	 _deck -> m_arrayCards[_indexOne] =  _deck -> m_arrayCards[_indexTwo];
	_deck -> m_arrayCards[_indexTwo] = ptrTmpCard ;	
	
}

/* ---------------------------------------- */
static void InitDeck(Deck *_newDeck)
{
	int suite , rank ;
	
     for ( suite = 0 ; suite < SIZE_SUITE ; suite++ )
     {
	    for ( rank = 0 ; rank < SIZE_RANK ; rank++)
	    {
	  	  _newDeck -> m_arrayCards[(suite*(SIZE_RANK))+rank] = CreateCard(suite , rank) ;
	    }
     } 
     _newDeck -> m_nCards = FULL_DECK_SIZE ;
     _newDeck -> m_originalSize = FULL_DECK_SIZE;
     
     return;
}
