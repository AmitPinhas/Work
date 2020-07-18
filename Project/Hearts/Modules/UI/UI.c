#include <stdio.h>  /* printf */
#include "UI.h" /* API statements */ 


#define SIZE_TABLE 4
#define NUMBER_PLAYERS 4

/* ========================================================== UI API ============================================================================== */

/* ------------------------------------------------------ - Print card ---------------------------------------------------------------------------- */
void PrintCard(const Card *_card)
{
	Suite suite;
	Rank rank;
	
	
	if ( _card != NULL )
	{
	  suite = GetSuite( _card );
	  rank = GetRank( _card );
	
		switch ( suite )
		{
			case HEART:
					 printf("♥");
					 break;
			case SPADES:
					 printf("♠");
					 break;
			case DIAMOND:
					 printf("♦");
					 break;
			case CLUB:
					 printf("♣");
					 break;
			   default:
			        	 break;					 					 					 
		}
		switch ( rank )
		{
			case TWO:
					 printf("2 ");
					 break;
			case THREE:
					 printf("3 ");
					 break;
			case FOUR:
					 printf("4 ");
					 break;
			case FIVE:
					 printf("5 ");
					 break;
			case SIX:
					 printf("6 ");
					 break;
			case SEVEN:
					 printf("7 ");
					 break;
			case EIGHT:
					 printf("8 ");
					 break;
			case NINE:
					 printf("9 ");
					 break;
			case TEN:
					 printf("10 ");
					 break;
			case JACK:
					 printf("J ");
					 break;
			case QUEEN:
					 printf("Q ");
					 break;
			case KING:
					 printf("K ");
					 break;
			case ACE:
					 printf("A ");
					 break;			 					 					 					 					 
			   default:
			        	 break;					 					 					 
		}		
	}
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
void PrintPlayer(Player *_player)
{
	char *name;
	name = GetName(_player);
	printf("name player: ");
	puts(name);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
void PrintTable(Table *_table)
{
	int index;
	Card *ptrCard;
	
	printf("\ntable: ");
	
	for ( index = 0 ; index < SIZE_TABLE ; index++ )
	{
		ptrCard = GetCardInTable(_table , index);
		if ( ptrCard != NULL )
		{
			PrintCard(ptrCard);
		}
	}
	putchar('\n');
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------ */
void PrintTrick(int _index)
{
	printf("trick %d :\n" , _index);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------ */
void GetNameScan(char *_name, int _index)
{
	printf("Please enter name player %d : " , _index);
	scanf("%s" , _name);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------ */
void PrintLosser(Player *_player)
{
	char *name;
	name = GetName(_player);
	printf("loser player: ");
	puts(name);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------ */
void PrintPoints(int _points , int _tricknum)
{
	printf("points trick %d : %d\n" , _tricknum , _points);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------ */
void PrintRound(int _numRound)
{
	printf("\nRound %d ----> \n\n" , _numRound);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------ */
void PrintScorePlayers(Player **_players)
{
	int index;
	char *name;
	
	for ( index = 0 ; index < NUMBER_PLAYERS ; index++ )
	{
		name = GetName(_players[index]);
		printf("%s : %d  " , name , GetPoints(_players[index])) ;
	}
	putchar('\n');
	printf("-----------------------------------------\n");	
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------ */
void PrintWinner(Player **_players)
{
	int minPoint=100 , tmpPoint=0;
	int index , indexWinner=0;
	char *name;
	
	for ( index = 0 ; index < NUMBER_PLAYERS ; index++ )
	{
		tmpPoint = GetPoints(_players[index]);
		
		if ( tmpPoint < minPoint )
		{
			minPoint = tmpPoint;
			indexWinner = index;
		}
	}
	
	name = GetName(_players[indexWinner]);
	printf("\nThe Winner is %s !!!!!!\n" , name);
	
}

