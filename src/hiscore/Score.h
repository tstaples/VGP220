#ifndef _SCORE_H
#define _SCORE_H
#pragma once

#include <string>

class Score
{
public:
	Score( std::string& name, int score )
		:	mName( name ) ,	mScore( score ) {}
	~Score() {}

	inline int GetScore() const { return mScore; }
	inline std::string GetName() const { return mName; }

private:

	std::string mName;	// Player name
	int mScore;			// Player score. (signed because negative scores may be desireable)
};

#endif