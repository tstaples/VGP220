#ifndef INCLUDED_QUEUE_H
#define INCLUDED_QUEUE_H

#include "node.h"

template< typename T >
class Queue
{
public:
	Queue();
	~Queue();

	void Enqueue(const T& val);
	void Dequeue();

	const T& Front() const;

private:
	Node<T>* mFront;
};

template< typename T >
Queue<T>::Queue()
	:	mFront( nullptr )
{
}

template< typename T >
Queue<T>::~Queue()
{
}


template< typename T >
void Queue<T>::Enqueue(const T& val)
{
	if (mFront)
	{
		Node<T>* node = mFront;
		while (node->mNext)
		{
			node = node->mNext;
		}
		Node<T>* back = new Node<T>(val);
		node->mNext = back;
	}
	else
	{
		mFront = new Node<T>(val);
	}
}

template< typename T >
void Queue<T>::Dequeue()
{
	if (mFront)
	{
		Node<T>* temp = mFront;
		mFront = mFront->mNext;
		delete temp;
		temp = nullptr;
	}
}

template< typename T >
const T& Queue<T>::Front() const
{
	return mFront->mData;
}

#endif