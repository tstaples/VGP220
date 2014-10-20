#include "ReversePolish.h"


void ReversePolish::AddNumber(int number)
{
	mStack.Push(number);
}

void ReversePolish::AddSymbol(char symbol)
{
	// Get first two values
	float a = mStack.Top();
	mStack.Pop();
	float b = mStack.Top();
	mStack.Pop();

	switch (symbol)
	{
	case '+':
		mStack.Push(a + b);
		break;
	case '-':
		// a is on right side since it is the value we want to subtract by
		mStack.Push(b - a);
		break;
	case '*':
		mStack.Push(a * b);
		break;
	case '/':
		// a is on right side since it is the value we want to divide by
		mStack.Push(b / a);
		break;
	}
}
	
float ReversePolish::GetResult()
{
	return (mStack.Top());
}