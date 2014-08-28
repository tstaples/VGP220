#ifndef INCLUDED_REVERSEPOLISH_H
#define INCLUDED_REVERSEPOLISH_H

#include "stack.h"

class ReversePolish
{
public:

	void AddNumber(int number);
	void AddSymbol(char symbol);	
	
	// Returns the top of the stack
	float GetResult();

private:
	Stack<float> mStack;
};

#endif