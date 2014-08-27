#include "Score.h"
#include <string.h>

Score::Score( std::string& name, int score )
	:	mName( name )
	,	mScore( score )
{
}

// ----------------------------------------------------------------------

Score::~Score()
{
}