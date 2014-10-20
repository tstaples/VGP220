#ifndef INCLUDED_NODE_H
#define INCLUDED_NODE_H

template< typename T >
class Node
{
public:
	Node(const T& data) : mData(data), mNext(nullptr) {}

	T mData;
	Node* mNext;
};

#endif