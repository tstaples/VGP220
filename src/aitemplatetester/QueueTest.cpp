#include "Tests.h"
#include "queue.h"

bool testQueue()
{
	Queue<int> myQ;
	myQ.Enqueue(1);
	myQ.Enqueue(2);
	myQ.Enqueue(3);

	assert(myQ.Front() == 1);

	myQ.Dequeue();
	assert(myQ.Front() == 2);

	Queue<int> myQcopy(myQ);
	assert(myQcopy.Front() == 2);
	myQcopy.Dequeue();
	assert(myQcopy.Front() == 3);

	return true;
}