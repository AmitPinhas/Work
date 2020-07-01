
#include "decision.h"


int PlayerDesicion(Hand *_hand ,Table *_table , int _index)
{
	Suite tmpSuite=0;
	int index ;
	
	if ( _index != 0 )
	{
	  tmpSuite = GetTopSuite(_table);
	}
	
	index = GetHighCardFromSuite(tmpSuite , _hand );
	
	if ( index == -1 )
	{
		return GetHighCardFromHand( _hand);
	}
	
	return index;	
}
