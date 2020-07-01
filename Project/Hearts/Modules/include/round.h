#ifndef __ROUND_H__  /* Avoiding a double statement */
#define __ROUND_H__ 

/* ========================================================= Round typedef ========================================================================= */

  /*struct Round */
typedef struct Round Round;

/* ========================================================== Round API ============================================================================ */
/*
	Description: Create pointer to round .
	      Input: no input .
 	     Output: pointer to round / null .
	      Error: pointer to round - the create ended successfully .
	             null - allocation failed .
*/
Round* CreateRound();
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: free round .
	      Input: address to pointer to round .
 	     Output: no output .
	      Error: no error .
*/
void DestroyRound(Round **_round);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
/*
	Description: play round .
	      Input: pointer to round .
 	     Output: no output .
	      Error: no error .
*/
void PlayRound(Round *_round);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */


#endif /* __ROUND_H__ */
