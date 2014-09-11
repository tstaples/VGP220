#include "Tests.h"
#include "priorityqueue.h"

bool testPriorityQueue()
{
	PriorityQueue mypq;
	mypq.EnQueue(0);
	mypq.EnQueue(9);
	mypq.EnQueue(5);
	mypq.EnQueue(6);

	mypq.EnQueue(2);
	mypq.EnQueue(3);
	mypq.EnQueue(4);
	mypq.EnQueue(8);
	mypq.EnQueue(1);

	assert(mypq.Front() == 0);

	mypq.DeQueue();
	assert(mypq.Front() == 1);

	mypq.DeQueue();
	assert(mypq.Front() == 2);

	mypq.DeQueue();
	assert(mypq.Front() == 3);

	mypq.DeQueue();
	assert(mypq.Front() == 4);

	mypq.DeQueue();
	assert(mypq.Front() == 5);

	mypq.DeQueue();
	assert(mypq.Front() == 6);

	mypq.DeQueue();
	assert(mypq.Front() == 8);

	mypq.DeQueue();
	assert(mypq.Front() == 9);
	return true;
}