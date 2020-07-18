#include <stdlib.h> /* allocation */
#include "round.h" /* API statements */
#include "deck.h"
#include "player.h" 
#include "hand.h"
#include "trick.h"
#include "UI.h"

/* ------------------ define --------------- */

#define NUMBER_PLAYERS 4
#define HAND_SIZE 13
#define NUM_OF_TRICKS 13
#define TRUE 1

/* ----------------- struct ---------------- */

struct Round
{
	Player **m_arrayPlayers;             
};


/* ------------ local functions ------------ */
void DestroyPlayers(Player **_arrayPlayers);
static void RoundCreatePlayers(Round *_round);
static void DealCards(Round *_round , Deck *_ptrFullDeck);
static int PlayTricks(Round *_round , int _numberRound);
static int TrickFirstLead(  Player **_players);

/* =========== Round API func =============== */

/* ------------Create Round------------------ */
Round* CreateRound()
{
	Round *ptrRound ;

	ptrRound = (Round*)malloc(sizeof(Round));
	if ( NULL == ptrRound )
	{
		return NULL;
	}
	
	ptrRound -> m_arrayPlayers = (Player**)malloc(NUMBER_PLAYERS * sizeof(Player*));
	if ( NULL == ptrRound -> m_arrayPlayers )
	{
		free(ptrRound);
		return NULL;
	}
	
	return ptrRound;
}

/* --------------- Destroy Round ----------- */
void DestroyRound(Round **_round)
{
	if ( (_round != NULL) && (*_round != NULL) )
	{
		DestroyPlayers((*_round)->m_arrayPlayers);
		free(*_round);
		*_round = NULL;
	}
	return;
}

/* --------------- Play round --------------- */
void PlayRound(Round *_round)
{
	Deck *ptrFullDeck;
	int maxPoints=0;
	int numberRound=1;

	RoundCreatePlayers(_round);
	
	while ( maxPoints < 100 )
	{
	ptrFullDeck = CreateDeck();
	
	ShuffleDeck(ptrFullDeck);

	DealCards(_round , ptrFullDeck);	

     maxPoints = PlayTricks(_round , numberRound);	
	
	DestroyDeck(&ptrFullDeck);
	
	numberRound++;
	}
	
	PrintWinner(_round->m_arrayPlayers);
	
     DestroyDeck(&ptrFullDeck);
	
	return;
}


/* ================ local functions ======== */
void DestroyPlayers(Player **_arrayPlayers)
{
	int index ;
	
	for ( index = 0 ; index < NUMBER_PLAYERS ; index++ )
	{
		DestroyPlayer(&_arrayPlayers[index]);
	}
}

/* ------------------------------------------- */
static void RoundCreatePlayers(Round *_round)
{
	int indexPlayer ;
	char name[50];
	
	for ( indexPlayer = 0 ; indexPlayer < NUMBER_PLAYERS ; indexPlayer++ )
	{
		GetNameScan(name ,indexPlayer+1 );
		_round->m_arrayPlayers[indexPlayer] = CreatePlayer(name , COMPUTER);
	}
}

/* ------------------------------------------- */
static void DealCards(Round *_round , Deck *_ptrFullDeck)
{
	int indexPlayer , indexCards=0 , indextmp ;
	
	for ( indexPlayer = 0 ; indexPlayer < NUMBER_PLAYERS ; indexPlayer++ )
	{
	  for ( indextmp= 0 ; indextmp < HAND_SIZE ; indexCards++ , indextmp++ )
	  {
		PlayerSetCardInHand( _round->m_arrayPlayers[indexPlayer] ,indextmp ,GetCardFromDeck(_ptrFullDeck , indexCards));
	  }
	 /* PlayerSortHand(_round->m_arrayPlayers[indexPlayer]); */
	}  	

}

/* ------------------------------------------- */
static int PlayTricks(Round *_round, int _numberRound)
{
	Trick *ptrTrick;
	int trick , indexStart , indexPlayers , maxPoints=0 , pointTmp;
	
	ptrTrick = CreateTrick();
	
     indexStart = TrickFirstLead( _round->m_arrayPlayers);
     
     PrintRound(_numberRound);
	for ( trick=1 ; trick <= NUM_OF_TRICKS ; trick++ )
	{
		indexStart = PlayTrick(ptrTrick , _round->m_arrayPlayers , indexStart  , trick  );
	}
	
	for ( indexPlayers = 0 ; indexPlayers < NUMBER_PLAYERS ; indexPlayers++)
	{
		pointTmp = GetPoints(_round->m_arrayPlayers[indexPlayers]);
		if ( pointTmp > maxPoints )
		{
			maxPoints = pointTmp;
		}
	}
	
	
	DestroyTrick(&ptrTrick);
	
	return maxPoints;
}

/* ------------------------------------------- */
static int TrickFirstLead(Player **_players)
{
	int index ;
	
	for ( index = 0 ; index < NUMBER_PLAYERS ; index++)
	{
		if ( CheckExistTwoClub(_players[index]) == TRUE )
		{
			return index ;
		}
	}	
	
	return index;
}


