
#include "game.h"
#include "round.h"

/* ========================================================== Game API func ======================================================================== */

/*------------------------------------------------------------ Start Game ---------------------------------------------------------------------------*/
void StartGame()
{
	Round *ptrRound;
	
	ptrRound = CreateRound();
	
	PlayRound(ptrRound);
	
	DestroyRound(&ptrRound);
	
	return;
}
