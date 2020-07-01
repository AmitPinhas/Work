#include <stdlib.h> /* allocation */
#include "../include/hand.h" /* API statements */


/* ------------------------------------------------------------ define ---------------------------------------------------------------------------- */
#define SIZE_HAND 13
#define TRUE 1
#define FALSE 0
/* ------------------------------------------------------------- struct --------------------------------------------------------------------------- */
struct Hand
{
	Card **m_hand;               
};

/* =========================================================== Hand API func ======================================================================= */

/*----------------------------------------------------------- Create Hand ---------------------------------------------------------------------------*/
Hand* CreateHand()
{
	Hand *ptrHand;

	ptrHand = (Hand*)malloc(sizeof(Hand));
	if( NULL == ptrHand )
	{
		return NULL ;
	}
	
	ptrHand->m_hand= (Card**)malloc(SIZE_HAND * sizeof(Card*));
	if ( NULL == ptrHand->m_hand )
	{
		free ( ptrHand );
		return NULL;
	}
	
	return ptrHand;
}

/*----------------------------------------------------------- Destroy Hand --------------------------------------------------------------------------*/
void DestroyHand(Hand **_hand)
{
	if ( (_hand != NULL) && (*_hand != NULL) )
	{
		free(*_hand);
	}
	
	*_hand = NULL;
}

/*-----------------------------------------------------Get High Card From Suite---------------------------------------------------------------------*/
int GetHighCardFromSuite(Suite _suite , Hand *_hand)
{
	Suite tmpSuite;
	int index;
	int indexCard=-1 ;
	
	for ( index = 0 ; index < SIZE_HAND ; index++ )
	{
		if ( _hand->m_hand[index] != NULL )
		{
			tmpSuite = GetSuite( _hand->m_hand[index] );
			if ( tmpSuite == _suite )
			{
				indexCard = index;
			}
		}
	}
	
	return indexCard;
}

/* -------------------------------------------------------- Set Card To Hand ---------------------------------------------------------------------- */
void SetCardToHand(Hand *_hand , int _index , Card *_card)
{
	_hand->m_hand[_index] = _card;
	return;
}

/*-----------------------------------------------------Get High Card From Hand-----------------------------------------------------------------------*/
int GetHighCardFromHand( Hand *_hand)
{
	Rank maxRank=0 , tmpRank;
	int index;
	int indexCard=0 ;
	
	for ( index = 0 ; index < SIZE_HAND ; index++ )
	{
		if ( _hand->m_hand[index] != NULL )
		{
			tmpRank = GetRank(_hand->m_hand[index]);
			if ( tmpRank >= maxRank )
			{
				indexCard = index;
			}
		}
	}
	
	return indexCard;
}
/* ----------------------------------------------- Check Hand If Two Club ------------------------------------------------------------------------- */
int CheckHandIfTwoClub(Hand *_hand)
{
	int index;
	Rank rank;
	Suite suite;
	
	for ( index = 0 ; index < SIZE_HAND ; index++ )
	{
		suite = GetSuite( _hand->m_hand[index] );
		rank = GetRank( _hand->m_hand[index] );
		
		if ( (suite == CLUB) && (rank == TWO) )
		{
			return TRUE;
		}
	}
	return FALSE;
}

/* ----------------------------------------------------------Sort Deck----------------------------------------------------------------------------- */
int SortHand(Hand *_hand , int _minValue , int _maxValue)
{
	int *countArray , sizeCountArray = _maxValue - _minValue + 1  ;
	register int index ;
	int indexNew ;
	Card **tmpArray ;
	Suite suite;
	Rank rank;
	int indexindex;
	
	if ( (countArray = (int*)calloc( sizeCountArray , sizeof(int) )) == NULL )
	{
		return -1 ;
	}
	if ( (tmpArray = (Card**)calloc( SIZE_HAND , sizeof(Card*) ) ) == NULL )
	{
		free(countArray) ;
		return -1 ;
	}	
	
	for ( index = 0 ; index < SIZE_HAND ; index++ )
	{
		suite = GetSuite(_hand->m_hand[index]);
		rank = GetRank(_hand->m_hand[index]);
		indexindex = (suite*SIZE_HAND)+rank ;
		countArray[indexindex] +=1;
	}	
	
	for ( index = 1 ; index < SIZE_HAND ; index++ )
	{
		countArray[index] = countArray[index] + countArray[index-1] ;
	}
	
	for ( index = 12 ; index >=0 ; index-- )
	{
		suite = GetSuite(_hand->m_hand[index] );
		rank = GetRank(_hand->m_hand[index]);
		indexNew = countArray[(suite*13)+rank] ;
		countArray[(suite*13)+rank] -=1;
		tmpArray[indexNew-1] = _hand->m_hand[index] ; 
	}		
	

	_hand->m_hand = tmpArray;
	
	free(countArray);

	
	return 1;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------ */
Card* GetCardFromHand(Hand *_hand , int _index)
{
	Card *ptrCard;
	
	ptrCard = _hand->m_hand[_index];
	
	_hand->m_hand[_index] = NULL;
	
	return ptrCard;
}


