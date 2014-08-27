#ifndef INCLUDED_STACK_H
#define INCLUDED_STACK_H

#include "node.h"

template< typename T >
class Stack
{
public:
	Stack();
	~Stack();

	void Push(const T& val);
	void Pop();

	const T& Top() const;

private:
	Node<T>* mTop;
};

template< typename T >
Stack<T>::Stack()
	:	mTop( nullptr )
{
}

template< typename T >
Stack<T>::~Stack()
{
}


template< typename T >
void Stack<T>::Push(const T& val)
{
	if (mTop)
	{
		Node<T>* node = new Node<T>(val);
		node->mNext = mTop;
		mTop = node;
	}
	else
	{
		mTop = new Node<T>(val);
		mTop->mNext = nullptr;
	}
}

template< typename T >
void Stack<T>::Pop()
{
	if (mTop)
	{
		Node<T>* temp = mTop;
		mTop = mTop->mNext;
		delete temp;
		temp = nullptr;
	}
}

template< typename T >
const T& Stack<T>::Top() const
{
	return mTop->mData;
}

#endif