#include <stdlib.h> /* allocation */
#include "trick.h" /* API statements */
#include "table.h" 
#include "UI.h"

/* ------------------------------------------------------ define --------------------------------------------------------------------------------- */
#define NUM_PLAYERS 4
#define TRUE 1
#define FALSE 0

/* ------------------------------------------------------ struct --------------------------------------------------------------------------------- */

struct Trick
{
	Table *m_table;               
};


/* ------------------------------------------------------------ local func ------------------------------------------------------------------------ */

/* ========================================================== Trick API func ====================================================================== */

/* -------------------------------------------------------------Create Trick----------------------------------------------------------------------- */
Trick* CreateTrick()
{
	Trick *ptrNewTrick ;
	
	ptrNewTrick = (Trick*)malloc(sizeof(Trick));
	if ( NULL == ptrNewTrick )
	{
		return NULL ;
	}
	
	ptrNewTrick -> m_table = CreateTable();
	
	if ( NULL == ptrNewTrick -> m_table )
	{
		free ( ptrNewTrick );
		return NULL;
		
	}
	
	return ptrNewTrick;
}

/* ---------------------------------------------------------- Destroy Trick ------------------------------------------------------------------------ */
void DestroyTrick(Trick **_trick)
{
	if ( (_trick != NULL) && (*_trick != NULL) )
	{
		DestroyTable(&(*_trick) ->m_table);
		free(*_trick);
		*_trick = NULL;
	}	
	return;	
}

/* ---------------------------------------------------------- Play Trick --------------------------------------------------------------------------- */
int PlayTrick(Trick *_trick , Player **_players, int _indexStart , int _tricknum )
{
	int index , points , originalPoints;
	Card *ptrCard;
	
     PrintTrick(_tricknum);	
     
	for ( index = 0  ; index < NUM_PLAYERS ; index++ , _indexStart = (_indexStart+1) % NUM_PLAYERS )
	{
		PrintPlayer(_players[_indexStart]);
		ptrCard = PlayCard(_players[_indexStart] , _trick->m_table , index);
		PrintCard(ptrCard);
		SetCardInTable(_trick->m_table , ptrCard , index);
		PrintTable(_trick->m_table);
	}
	_indexStart = (GetLosserAndPoint(_trick->m_table , &points) + _indexStart) % NUM_PLAYERS ;
	PrintLosser(_players[_indexStart]);
	originalPoints = GetPoints(_players[_indexStart]);
	PrintPoints(points ,_tricknum );
	SetPoints(_players[_indexStart] , points+originalPoints);
	PrintScorePlayers(_players);
	CleanTable(_trick -> m_table);
	
	return _indexStart;
}


/* ========================================================== Local func ========================================================================== */




