#include <stdlib.h> /* allocation */
#include "../include/table.h" /* API statements */
#include "card.h" 


/* ------------------------------------------------------------ define ----------------------------------------------------------------------------- */
#define SIZE_TABLE 4

/* ------------------------------------------------------------- struct ---------------------------------------------------------------------------- */
struct Table
{
	Card **m_table;               
};

/* =========================================================== Table API func ====================================================================== */

/* ----------------------------------------------------------- Create Table ------------------------------------------------------------------------ */

Table* CreateTable()
{
	Table *ptrNewTable;
	
	ptrNewTable = (Table*)malloc(sizeof(Table));
	if ( NULL == ptrNewTable )
	{
		return NULL;
	}
	
	ptrNewTable->m_table = (Card**)malloc(SIZE_TABLE*sizeof(Card*));
	if ( NULL == ptrNewTable->m_table )
	{
		free( ptrNewTable );
		return NULL;
	}
	
	
	return ptrNewTable;
}

/* ----------------------------------------------------------- Destroy Table ----------------------------------------------------------------------- */

void DestroyTable(Table **_table)
{
	if ( (_table != NULL) && (*_table != NULL) )
	{
		if ( (*_table) -> m_table != NULL )
		{
			free ( (*_table) -> m_table ) ;
		}
		
		free ( *_table );
		*_table = NULL ;
	}
	
	return;
}
/* ----------------------------------------------------------Get Top Suite ----------------------------------------------------------------------- */
Suite GetTopSuite(Table *_table)
{
	Suite tmpSuite;
	tmpSuite = GetSuite( (_table->m_table[0]) );
	return tmpSuite;
}

/*------------------------------------------------------Get Losser And Point-----------------------------------------------------------------------*/ 
int GetLosserAndPoint(Table *_table , int *_points)
{
	int index;
	Suite leadSuite , tmpSuite;
	Rank leadRank , tmpRank;
	int indexLosser=0;
	
	leadSuite = GetSuite( (_table->m_table[0]) );
	leadRank = GetRank( (_table->m_table[0]) );
	*_points=0;
	
	for ( index = 0 ; index < SIZE_TABLE ; index++ )
	{
		*_points += GetPoint(_table->m_table[index]);
	}
	
	for ( index = 1 ; index < SIZE_TABLE ; index++ )
	{
		tmpSuite = GetSuite( (_table->m_table[index]) );
		if ( tmpSuite == leadSuite )
		{
			tmpRank = GetRank( (_table->m_table[index]) );
			if ( tmpRank > leadRank )
			{
				leadRank = tmpRank ;
				indexLosser = index;
			}
		}
	}	
	
	return indexLosser ;
	
}


/* --------------------------------------------------- Set Card In Table ------------------------------------------------------------------------- */
void SetCardInTable(Table *_table , Card *_card , int _index)
{
	_table->m_table[_index] = _card ;
	return;
}

/* --------------------------------------------------- Get Card In Table ------------------------------------------------------------------------- */
Card* GetCardInTable(Table *_table , int _index)
{
	return _table->m_table[_index] ;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void	CleanTable(Table *_table)
{
	int index ;
	for ( index = 0 ; index < SIZE_TABLE ; index++ )
	{
		DestroyCard(&_table->m_table[index]);
	}
}
