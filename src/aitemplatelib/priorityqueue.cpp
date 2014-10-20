#include "priorityqueue.h"

int minChild(int a, int b)
{
	return (a < b) ? a : b;
}

void swap(std::vector<int>& v, int indexA, int indexB)
{
	if (indexA < v.size() && indexB < v.size())
	{
		int temp = v[indexA];
		v[indexA] = v[indexB];
		v[indexB] = temp;
	}
}

void PriorityQueue::EnQueue(int priority)
{
	// Add the entry to the end of the vector
	mPQ.push_back(priority);

	int index = mPQ.size() - 1;
	int parentIndex = (index - 1) / 2;

	// New node has a greater priority than its parent
	while (priority < mPQ.at(parentIndex))
	{
		// Swap the with the parent
		mPQ.at(index) = mPQ.at(parentIndex);
		mPQ.at(parentIndex) = priority;

		// Calculate the new index
		index = parentIndex;
		parentIndex = (index - 1) / 2;
	}
}
// ------------------------------------------------------------------------

void PriorityQueue::DeQueue()
{
	// swap first and last elements, then remove the back
	swap(mPQ, 0, (mPQ.size()-1));
	mPQ.pop_back();

	int priority = mPQ.at(0);
	int index = 0;
	int leftchild = (2 * index) + 1;
	int rightchild = (2 * index) + 2;

	while (leftchild < mPQ.size() || rightchild < mPQ.size())
	{
		// Check that both child nodes exist
		if (leftchild < mPQ.size() && rightchild < mPQ.size())
		{
			// Store the children priorities
			int lval = mPQ[leftchild];
			int rval = mPQ[rightchild];

			// lower value = higher priority
			if (priority > minChild(lval, rval))
			{
				// Left child is the smallest
				if (mPQ[leftchild] == minChild(lval, rval))
				{
					// Swap with left child
					swap(mPQ, index, leftchild);
					index = leftchild;
				}
				else
				{
					// Swap with right child
					swap(mPQ, index, rightchild);
					index = rightchild;
				}
			}
		}
		// Only left child exists
		else if (leftchild < mPQ.size())
		{
			int lval = mPQ[leftchild];
			if (priority > lval)
			{
				// Swap with left child
				swap(mPQ, index, leftchild);
				index = leftchild;
			}
			break;
		}
		else if (rightchild < mPQ.size())
		{
			int rval = mPQ[rightchild];
			if (priority > rval)
			{
				// Swap with left child
				swap(mPQ, index, rightchild);
				index = rightchild;
			}
			break;
		}
		leftchild = (2 * index) + 1;
		rightchild = (2 * index) + 2;
	}
}
// ------------------------------------------------------------------------

const int PriorityQueue::Front() const
{
	return (mPQ.at(0));
}