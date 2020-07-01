#ifndef __TRICK_H__  /* Avoiding a double statement */
#define __TRICK_H__

#include "player.h"

/* ========================================================== Trick typedef ======================================================================= */

  /*struct Trick */
typedef struct Trick Trick;

/* ========================================================== Trick API func ====================================================================== */
/*
	Description: make pointer to a new trick .
	      Input: no input .
 	     Output: new pointer to trick / NULL .
	      Error: new pointer to trick - pointer creation successfully completed .
	             NULL - allocation failed .
	 complexity: O(1) .     
*/
Trick* CreateTrick();
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
	Description: free trick .
	      Input: address of pointer to trick .
 	     Output: no output .
	      Error: no error.
*/
void DestroyTrick(Trick **_trick);
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
	Description: play trick .
	      Input: a) pointer to trick .
	             b) array of pointers of player .
 	     Output: no output .
	      Error: no error.
*/
int PlayTrick(Trick *_trick , Player **_players , int _indexStart  , int _tricknum );
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif /* __TRICK_H__ */
