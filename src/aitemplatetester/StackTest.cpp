#include "Tests.h"
#include "stack.h"

bool testStack()
{
	Stack<int> myStack;
	myStack.Push(1);
	myStack.Push(2);
	myStack.Push(3);

	assert(myStack.Top() == 3);

	myStack.Pop();
	assert(myStack.Top() == 2);

	Stack<int> myStackcopy(myStack);
	assert(myStackcopy.Top() == 2);
	myStackcopy.Pop();
	assert(myStackcopy.Top() == 1);

	return true;
}