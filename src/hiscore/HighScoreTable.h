#ifndef _HIGHHighScoreTableTABLE_H
#define _HIGHHighScoreTableTABLE_H
#pragma once

#include <iostream>
#include <vector>
#include "Score.h"

class HighScoreTable
{
	// Overloaded ostream for printing all the score data
	friend std::ostream& operator<<( std::ostream& lhs, const HighScoreTable& rhs );
public:
	HighScoreTable();
	~HighScoreTable();

	bool AddScore( Score& );				// Add a new score to the table
	bool RemoveScore( const Score& );		// Remove a score from the list
	bool RemoveScore( unsigned int pos );	// Remove a score from the list
	void SortScores();						// Sort the scores in descending order

private:

	// Used by std::sort in SortScore()
	static bool CompareScores( const Score& lhs, const Score& rhs );

	// Holds the table of scores
	std::vector< Score > mScoreTable;
};


#endif