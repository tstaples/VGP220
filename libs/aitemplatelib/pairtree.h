#ifndef INCLUDED_PAIRTREE_H
#define INCLUDED_PAIRTREE_H

template<typename TVal>
class PairTree
{
	typedef unsigned long Key;
public:

	struct Node
	{
		Key mKey;
		TVal mData;
		Node* mLeft;
		Node* mRight;
	};

	PairTree();
	PairTree(const PairTree& rhs);
	~PairTree();

	void Clear();
	void Insert(const Key& key, const TVal& val);
	void Remove(const Key& key);
	const Node* Find(const Key& key);

	void PreOrder() const;
	void InOrder() const;
	void PostOrder() const;

	unsigned int Size() const;
	unsigned int Depth() const;

	PairTree& operator=(const PairTree& rhs);

private:

	void Clear(Node* node);

	void Insert(Node* node, const Key& key, const TVal& val);
	void Remove(Node* node, const Key& key);
	const Node* Find(Node* node, const Key& key);

	void PreOrder(Node* node) const;
	void InOrder(Node* node) const;
	void PostOrder(Node* node) const;

	unsigned int Size(Node* node) const;
	unsigned int Depth(Node* node) const;

	Node* Clone(Node* node);

private:
	Node* mRoot;
};


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------


template<typename TVal>
PairTree<TVal>::PairTree()
: mRoot(nullptr)
{
}
// ------------------------------------------------------------------------

template<typename TVal>
PairTree<TVal>::~PairTree()
{
}
// ------------------------------------------------------------------------

template<typename TVal>
PairTree<TVal>::PairTree(const PairTree& rhs)
{
}
// ------------------------------------------------------------------------

template<typename TVal>
PairTree<TVal>& PairTree<TVal>::operator=(const PairTree& rhs)
{
	if (this != &rhs)
	{
	}
	return *this;
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::Clear()
{
	Clear(mRoot);
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::Insert(const Key& key, const TVal& val)
{
	if (mRoot == nullptr)
	{
		mRoot = new Node();
		mRoot->mKey = key;
		mRoot->mData = val;
		mRoot->mRight = nullptr;
		mRoot->mLeft = nullptr;
	}
	else
	{
		Insert(mRoot, key, val);
	}
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::Remove(const Key& key)
{}

// ------------------------------------------------------------------------

template<typename TVal>
const typename PairTree<TVal>::Node* PairTree<TVal>::Find(const Key& key)
{
	return (Find(mRoot, key));
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::PreOrder() const
{
	PreOrder(mRoot);
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::InOrder() const
{
	InOrder(mRoot);
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::PostOrder() const
{
	PostOrder(mRoot);
}
// ------------------------------------------------------------------------

template<typename TVal>
unsigned int PairTree<TVal>::Size() const
{
	return Size(mRoot);
}
// ------------------------------------------------------------------------

template<typename TVal>
unsigned int PairTree<TVal>::Depth() const
{
	return (Depth(mRoot));
}
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// PRIVATE
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::Clear(Node* node)
{
	if (node != nullptr)
	{
		Clear(node->mLeft);
		Clear(node->mRight);
		delete node;
	}
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::Insert(Node* node, const Key& key, const TVal &val)
{
	if (key < node->mData)
	{
		if (node->mLeft != nullptr)
		{
			Insert(node->mLeft, key, val);
		}
		else
		{
			node->mLeft = new Node();
			node->mLeft->mKey = key;
			node->mLeft->mData = val;
			node->mLeft->mLeft = nullptr;
			node->mLeft->mRight = nullptr;
		}
	}
	else if (val >= node->mData)
	{
		if (node->mRight != nullptr)
		{
			Insert(node->mRight, key, val);
		}
		else
		{
			node->mRight = new Node();
			node->mRight->mKey = key;
			node->mRight->mData = val;
			node->mRight->mLeft = nullptr;
			node->mRight->mRight = nullptr;
		}
	}
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::Remove(Node* node, const Key& key)
{
	if (node)
	{
		if (val == node->mLeft->mData)
		{
			// has no children
			if (node->mLeft->mLeft == nullptr && node->mLeft->mRight == nullptr)
			{
				delete node->mLeft;
				node->mLeft = nullptr;
			}
			// Only has 1 child (right)
			else if (node->mLeft->mLeft == nullptr && node->mLeft->mRight != nullptr)
			{
				Node* temp = node->mRight;
				node->mRight = node->mLeft->mRight;
				delete temp;
			}
			// Only has 1 child (left)
			else if (node->mLeft->mLeft != nullptr && node->mLeft->mRight == nullptr)
			{
				Node* temp = node->mLeft;
				node->mLeft = node->mLeft->mLeft;
				delete temp;
			}
			// Has 2 children
			else
			{

			}
		}
		else if (val < node->mData)
		{
			Remove(node->mLeft, val);
		}
		else if (val > node->mData)
		{
			Remove(node->mRight, val);
		}
	}
}
// ------------------------------------------------------------------------

template<typename TVal>
const typename PairTree<TVal>::Node* PairTree<TVal>::Find(Node* node, const Key& key)
{
	if (node != nullptr)
	{
		if (node->mKey == key)
		{
			return node;
		}
		else if (key < node->mKey)
		{
			return Find(node->mLeft, key);
		}
		else if (key > node->mKey)
		{
			return Find(node->mRight, key);
		}
	}
	return nullptr;
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::PreOrder(Node* node) const
{
	if (node)
	{
		std::cout << node->mData << std::endl;
		PreOrder(node->mLeft);
		PreOrder(node->mRight);
	}
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::InOrder(Node* node) const
{
	if (node)
	{
		InOrder(node->mLeft);
		std::cout << node->mData << std::endl;
		InOrder(node->mRight);
	}
}
// ------------------------------------------------------------------------

template<typename TVal>
void PairTree<TVal>::PostOrder(Node* node) const
{
	if (node)
	{
		PostOrder(node->mLeft);
		PostOrder(node->mRight);
		std::cout << node->mData << std::endl;
	}
}
// ------------------------------------------------------------------------

template<typename TVal>
unsigned int PairTree<TVal>::Size(Node* node) const
{
	if (node != nullptr)
	{
		int sz = Size(node->mLeft) + Size(node->mRight);
		return sz + 1;
	}
	return 0;
}

// ------------------------------------------------------------------------

template<typename TVal>
unsigned int PairTree<TVal>::Depth(Node* node) const
{
	if (node != nullptr)
	{
		int left = Depth(node->mLeft);
		int right = Depth(node->mRight);
		return (left > right) ? left+1 : right+1;
	}
	return 0;
}

template<typename TVal>
typename PairTree<TVal>::Node* PairTree<TVal>::Clone(Node* node)
{
	return node;
}

#endif