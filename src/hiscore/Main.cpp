/*
Write a simple high score table class using arrays as storage.  
They are sorted by decending score.  

contains name (3 characters +1 null terminator) and score
	- const char *name;
	- int score
	*Does not have to be unique

Must do at least these functions:

cAllHighScoreTable
	CAiScore &GetScore( int position );
		- returns a reference to the object at n position

	AddScore(CAiScore);
		- adds the score object to the array

	RemoveScore(cAiScore)
		- 
		- removes the score object to the array

	operator<<(ostream& o, cALHighScoreTable);
		-  ouputs the contents of the entire table
			- iterate through each item and output name and score on same line

	SortScores()
		- calls qsort with the compare score

	CompareScores( const CAIScore *lhs, const CAIScore *lhs );
		- compare lhs->GetScore() and rhs->GetScore()

cAiScore
	int GetScore( CAIScore & );
		- returns the score of the object passed in
	const char *GetName( CAIScore & );
		- returns the name of the object passed in

cAiScore is the score calss
cAllHighScoreTable is the highscore table class (contains an array of cAIScores).  
*/

#include "HighScoreTable.h"
#include <ctime>
#include <string>

bool Menu( HighScoreTable &hsTable );
void GenName( std::string& name );

int main()
{
	// Set seed for rand()
	srand( time( NULL ) );

	HighScoreTable hsTable;
	for ( int i=0; i < 20; ++i )
	{
		// Generating 20 entries with a random name and score
		std::string name;
		GenName( name );
		hsTable.AddScore( Score( name, (rand() % 1000 + 1) ) );
	}
	hsTable.SortScores();

	while ( Menu( hsTable ) ) {}

	return 0;
}

// User menu used for testing the functionality
bool Menu( HighScoreTable &hsTable )
{
	std::string input;
	std::cout << "1 - Print Scores\n"
			<< "2 - Add Score\n"
			<< "3 - Remove Score\n"
			<< "/quit to quit\n";

	std::cin >> input;

	std::string name;
	int score = 0;
	unsigned int pos = 0;

	switch ( atoi( input.c_str() ) )
	{
	case 1:
		std::cout << hsTable;
		break;
	case 2:
		std::cout << "Input Name (3 characters, A-Z), and Score\n";
		std::cin >> name >> score;
		if ( hsTable.AddScore( Score( name, score ) ) )
		{
			hsTable.SortScores();
		}
		break;
	case 3:
		std::cout << "Input position of the score you wish to remove\n";
		std::cin >> pos;
		if ( !hsTable.RemoveScore( pos ) )
		{
			std::cout << "Invalid entry\n";
		}
		break;
	default:
		return false;
	}
	return true;
}

// Generates 3 random uppercase characters
void GenName( std::string& name )
{
	for ( int i=0; i < 3; ++i )
	{
		name.push_back( rand() % 25 + 65 );
	}
}