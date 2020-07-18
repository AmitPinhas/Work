#ifndef __PLAYER_H__  /* Avoiding a double statement */
#define __PLAYER_H__

#include "hand.h" 
#include "card.h" 
#include "table.h" 


#define TRUE 1
#define FALSE 0

/* ========================================================== Card typedef ======================================================================== */ 

 /* type of the player or human or computer automatic */
typedef enum { HUMAN , COMPUTER }TypePlayer ;

  /*struct player */
typedef struct Player Player;


/* ========================================================== Card API ============================================================================= */
/*
	Description: create new player .
	      Input: a)name .
	             b)type - HUMAN/COMPUTER .
 	     Output: new pointer to player / NULL .
	      Error: new pointer to player - pointer creation successfully completed .
	             NULL - allocation failed .   
*/
Player* CreatePlayer(char *_name , TypePlayer _type);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: free player .
	      Input: address of pointer to player .
 	     Output: no output .
	      Error: no error .
*/
void DestroyPlayer(Player **_player);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: set points to the player .
	      Input: a) pointer to player .
	             b) points .
 	     Output: no output .
	      Error: no error .
*/
void SetPoints(Player *_player , int _point);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: get points of the player .
	      Input: a) pointer to player .
 	     Output: points .
	      Error: no error .
*/
int GetPoints(Player *_player);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
void PlayerSetCardInHand(Player *_player ,int _index , Card *_card);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
Hand* GetHand(Player *_player);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
Card* PlayCard(Player *_player , Table *_table , int _index);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: check if player have the card two club .
	      Input: pointer to player .
 	     Output: TRUE / FALSE .
	      Error: TRUE - have the card two club .
	             FALSE - dont have the card two club .
*/
int CheckExistTwoClub(Player *_player);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: sort hand of the player .
	      Input: pointer to player .
 	     Output: name .
	      Error: no error .
*/
void PlayerSortHand(Player *_player);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: get name of the player .
	      Input: pointer to player .
 	     Output: name .
	      Error: no error .
*/
char* GetName(Player *_player);

#endif /* __PLAYER_H__ */
