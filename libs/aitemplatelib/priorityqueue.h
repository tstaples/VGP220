#ifndef INCLUDED_PriorityQueue_H
#define INCLUDED_PriorityQueue_H

#include <vector>

class PriorityQueue
{
public:
	void EnQueue(int priority);
	void DeQueue();

	const int Front() const;

private:
	typedef std::vector<int> PQ_vec;
	PQ_vec mPQ;
};

#endif