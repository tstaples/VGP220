#ifndef INCLUDED_QUEUE_H
#define INCLUDED_QUEUE_H

#include "node.h"

template< typename T >
class Queue
{
public:
	Queue();
	~Queue();
	Queue(const Queue& rhs);
	Queue& operator=(const Queue& rhs);

	void Enqueue(const T& val);
	void Dequeue();

	const T& Front() const;

private:
	Node<T>* mFront;
};

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------


template< typename T >
Queue<T>::Queue()
	:	mFront( nullptr )
{
}
// ------------------------------------------------------------------------

template< typename T >
Queue<T>::~Queue()
{
}
// ------------------------------------------------------------------------

template< typename T >
Queue<T>::Queue(const Queue& rhs)
	:	mFront(nullptr)
{
	*this = rhs;
}
// ------------------------------------------------------------------------

template< typename T >
Queue<T>& Queue<T>::operator=(const Queue& rhs)
{
	if (this != &rhs)
	{
		Node<T>* temp = rhs.mFront;
		while (temp)
		{
			// Traverse source Queue and push the values to the local Q.
			Enqueue(temp->mData);
			temp = temp->mNext;
		}
	}
	return *this;
}
// ------------------------------------------------------------------------

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
// ------------------------------------------------------------------------

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
// ------------------------------------------------------------------------

template< typename T >
const T& Queue<T>::Front() const
{
	return mFront->mData;
}

#endif