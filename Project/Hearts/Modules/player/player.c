#include <stdlib.h> /* allocation */
#include <string.h> /* strcpy */
#include "player.h" /* API statements */
#include "decision.h"


/* ------------------------------------------------------ define --------------------------------------------------------------------------------- */
#define SIZE_NAME 50
#define SIZE_DECK_PLAYER 13
#define MIN_VALUE 0
#define MAX_VALUE 51

/* ------------------------------------------------------ struct --------------------------------------------------------------------------------- */
struct Player
{
	char m_name[SIZE_NAME];
	int m_points;
	TypePlayer m_type;
	Hand *m_hand;
};

/* ---------------------------------------------------------- Private ----------------------------------------------------------------------------- */


/* ========================================================== public ============================================================================== */

/* ------------------------------------------------------ Create Player --------------------------------------------------------------------------- */

Player* CreatePlayer(char *_name , TypePlayer _type )
{
	Player *ptrNewPlayer ;
	
	ptrNewPlayer = (Player*)malloc(sizeof(Player) ) ;
	
	if ( NULL == ptrNewPlayer )
	{
		return NULL ;
	}
	
	ptrNewPlayer->m_hand = CreateHand();
	
	if ( NULL == ptrNewPlayer->m_hand  )
	{
		free(ptrNewPlayer);
		return NULL;
	}
	
	ptrNewPlayer->m_points=0;
	strcpy(ptrNewPlayer->m_name , _name);
	ptrNewPlayer -> m_type = _type ;
	
	return ptrNewPlayer;
}


/* ------------------------------------------------------ Destroy Player -------------------------------------------------------------------------- */

void DestroyPlayer(Player **_player)
{
	if ( (_player != NULL) && (*_player != NULL) )
	{
		free(*_player);
	}
	
	*_player=NULL ;
	
	return;
}


/* ------------------------------------------------------ Set Points ------------------------------------------------------------------------------ */
void SetPoints(Player *_player , int _point)
{
	_player -> m_points = _point ;
}

/* ------------------------------------------------------ Get Points ------------------------------------------------------------------------------ */
int GetPoints(Player *_player)
{
	return _player->m_points ;
}

/* ------------------------------------------------------ Player Set Card In Hand ----------------------------------------------------------------- */
void PlayerSetCardInHand( Player *_player ,int _index , Card *_card)
{
	SetCardToHand( _player->m_hand ,  _index , _card);
	return;
}

/* ------------------------------------------------------ Get Hand -------------------------------------------------------------------------------- */
Hand* GetHand(Player *_player)
{
	return _player -> m_hand ;
}

/* --------------------------------------------------  Play Card   -------------------------------------------------------------------------------- */
Card* PlayCard(Player *_player , Table *_table , int _index)
{
	int index ;
	Card *ptrCard;
	index = PlayerDesicion(_player->m_hand , _table ,_index );
	
	ptrCard = GetCardFromHand(_player->m_hand , index);
	
	return ptrCard;
}

/* ---------------------------------------------- Check Exist Two Club ---------------------------------------------------------------------------- */
int CheckExistTwoClub(Player *_player)
{
	return CheckHandIfTwoClub(_player->m_hand);
}

/* ------------------------------------------------- Player Sort Hand ----------------------------------------------------------------------------- */
void PlayerSortHand(Player *_player)
{
	SortHand(_player->m_hand , MIN_VALUE , MAX_VALUE);
}


/* ------------------------------------------------------------------------------------------------------------------------------------------------ */
char* GetName(Player *_player)
{
	return _player->m_name ;
}

/* ========================================================== local func ========================================================================== */


