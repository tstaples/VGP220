#ifndef INCLUDED_STACK_H
#define INCLUDED_STACK_H

#include "node.h"
#include <assert.h>
#include <vector>

template< typename T >
class Stack
{
public:
	Stack() : mTop( nullptr ) {}
	~Stack() {}
	Stack(const Stack& rhs);
	Stack& operator=(const Stack& rhs);

	void Push(const T& val);
	void Pop();

	// Returns value on the top of the stack. (0 
	const T& Top() const;

private:
	Node<T>* mTop;
};

// ========================================================================
// Stack definitions
// ========================================================================

template< typename T >
Stack<T>::Stack(const Stack& rhs)
{
	*this = rhs;
}
// ------------------------------------------------------------------------

template< typename T >
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	if (this != &rhs)
	{
		std::vector<T> kSourceVals;

		Node<T>* temp = rhs.mTop;
		while (temp)
		{
			// Traverse source stack and save all the values.
			kSourceVals.push_back(temp->mData);
			temp = temp->mNext;
		}

		// Starting from the end of the list, push the values on to our stack
		auto rit = kSourceVals.end();
		while (rit != kSourceVals.begin())
		{
			--rit;
			Push(*rit);
		}
	}
	return *this;
}
// ------------------------------------------------------------------------

template< typename T >
void Stack<T>::Push(const T& val)
{
	if (mTop)
	{
		Node<T>* node = new Node<T>(val);

		// Link to current top, then assign the new Top of the stack
		node->mNext = mTop;
		mTop = node;
	}
	else
	{
		// Stack is empty
		mTop = new Node<T>(val);
		mTop->mNext = nullptr;
	}
}
// ------------------------------------------------------------------------

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
// ------------------------------------------------------------------------

template< typename T >
const T& Stack<T>::Top() const
{
	// Assert top of stack is invalid
	assert(mTop);
	return mTop->mData;
}

#endif