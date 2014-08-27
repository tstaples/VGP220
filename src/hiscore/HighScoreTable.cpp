#include "HighScoreTable.h"
#include <algorithm>
#include <iterator>
#include <string>

HighScoreTable::HighScoreTable()
{
}
// ----------------------------------------------------------------------

HighScoreTable::~HighScoreTable()
{
}
// ----------------------------------------------------------------------

bool HighScoreTable::AddScore( Score& score )
{
	// Create a local copy since you cannot iteratre over a const string
	std::string name = score.GetName();

	// Only 3 Uppercase letters from A-Z are valid
	if ( name.size() == 3 &&
		 std::find_if( name.begin(), name.end(), ::isupper ) != name.end() )
	{
		mScoreTable.push_back( score );
		return true;
	}
	return false;
}
// ----------------------------------------------------------------------

bool HighScoreTable::RemoveScore( const Score& score )
{
	for ( std::vector< Score >::const_iterator iter = mScoreTable.begin();
		  iter != mScoreTable.end(); ++iter )
	{
		// Compare the adress of the object iter points to, and the object passed in
		if ( &(*iter) == &score )
		{
			// Remove that element
			mScoreTable.erase( iter );
			return true;
		}
	}
	return false;
}
// ----------------------------------------------------------------------

bool HighScoreTable::RemoveScore( unsigned int pos )
{
	if ( pos > 0 && pos < mScoreTable.size() )
	{
		// Pos is decremented by 1 to avoid off by 1 errors,
		mScoreTable.erase( mScoreTable.begin() + (pos-1) );
		return true;
	}
	return false;
}
// ----------------------------------------------------------------------

void HighScoreTable::SortScores()
{
	std::sort( mScoreTable.begin(), mScoreTable.end(), &HighScoreTable::CompareScores );
}
// ----------------------------------------------------------------------

bool HighScoreTable::CompareScores( const Score& lhs, const Score& rhs )
{
	return ( lhs.GetScore() > rhs.GetScore() );
}
// ----------------------------------------------------------------------

std::ostream &operator<<( std::ostream& lhs, const HighScoreTable& rhs )
{
	lhs << "Rank\tName\tScore\n";

	int pos = 1;	// Score position/rank
	for ( auto it : rhs.mScoreTable )
	{
		// Output position, name and score
		lhs << pos++ << '\t' << it.GetName() << '\t' << it.GetScore() << std::endl;
	}
	return lhs;
}