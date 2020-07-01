#ifndef __UI_H__  /* Avoiding a double statement */
#define __UI_H__

#include "card.h" 
#include "player.h"
#include "table.h"

/* ========================================================== UI API =============================================================================== */
/*
	Description: print card , print the rank and the suite .
	      Input: a) pointer to card .
	     Output: print card / no print .
	      Error: no print - pointer card null .          
	 complexity: O(1) .     
*/
void PrintCard(const Card *_card);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
void PrintPlayer(Player *_player);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
void PrintTable(Table *_table);
/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
void PrintTrick(int _index);

void GetNameScan(char *_name, int _index);

void PrintLosser(Player *_player);

void PrintPoints(int _points, int _tricknum);

void PrintRound(int _numRound);

void PrintScorePlayers(Player **_players);

void PrintWinner(Player **_players);

#endif /* __UI_H__ */
