#include <iostream>

template< typename T >
class BinaryTree
{
public:
	struct Node
	{
		T mData;
		Node* mLeft;
		Node* mRight;
	};

	BinaryTree();
	BinaryTree(const BinaryTree& rhs);
	~BinaryTree();

	void Clear();
	void Insert(const T& val);
	void Remove(const T& val);
	const Node* Find(const T& val);

	void PreOrder() const;
	void InOrder() const;
	void PostOrder() const;

	unsigned int Size() const;
	unsigned int Depth() const;

	BinaryTree& operator=(const BinaryTree& rhs);

private:

	void Clear(Node* node);

	void Insert(Node* node, const T& val);
	void Remove(Node* node, const T& val);
	const Node* Find(Node* node, const T& val);

	void PreOrder(Node* node) const;
	void InOrder(Node* node) const;
	void PostOrder(Node* node) const;

	unsigned int Size(Node* node) const;
	unsigned int Depth(Node* node) const;

	T Min(Node* node);

	Node* Clone(Node* node);

private:
	Node* mRoot;
};


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------


template< typename T >
BinaryTree<T>::BinaryTree()
: mRoot(nullptr)
{
}
// ------------------------------------------------------------------------

template< typename T >
BinaryTree<T>::~BinaryTree()
{
}
// ------------------------------------------------------------------------

template< typename T >
BinaryTree<T>::BinaryTree(const BinaryTree& rhs)
{
	this = &rhs;
}
// ------------------------------------------------------------------------

template< typename T >
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& rhs)
{
	if (this != &rhs)
	{
		Insert(rhs.PreOrder());
	}
	return *this;
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::Clear()
{
	Clear(mRoot);
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::Insert(const T& val)
{
	if (mRoot == nullptr)
	{
		mRoot = new Node();
		mRoot->mData = val;
		mRoot->mRight = nullptr;
		mRoot->mLeft = nullptr;
	}
	else
	{
		Insert(mRoot, val);
	}
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::Remove(const T& val)
{
	if (mRoot)
	{
		Remove(mRoot, val);
	}
	else
	{
		if (val == mRoot->mData)
		{
			delete mRoot;
			mRoot = nullptr;
		}
	}
}

// ------------------------------------------------------------------------

template< typename T >
const typename BinaryTree<T>::Node* BinaryTree<T>::Find(const T& val)
{
	return (Find(mRoot, val));
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::PreOrder() const
{
	PreOrder(mRoot);
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::InOrder() const
{
	InOrder(mRoot);
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::PostOrder() const
{
	PostOrder(mRoot);
}
// ------------------------------------------------------------------------

template< typename T >
unsigned int BinaryTree<T>::Size() const
{
	return Size(mRoot);
}
// ------------------------------------------------------------------------

template< typename T >
unsigned int BinaryTree<T>::Depth() const
{
	return (Depth(mRoot));
}
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// PRIVATE
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::Clear(Node* node)
{
	if (node != nullptr)
	{
		Clear(node->mLeft);
		Clear(node->mRight);
		delete node;
	}
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::Insert(Node* node, const T& val)
{
	if (val < node->mData)
	{
		if (node->mLeft != nullptr)
		{
			Insert(node->mLeft, val);
		}
		else
		{
			node->mLeft = new Node();
			node->mLeft->mData = val;
			node->mLeft->mLeft = nullptr;
			node->mLeft->mRight = nullptr;
		}
	}
	else if (val >= node->mData)
	{
		if (node->mRight != nullptr)
		{
			Insert(node->mRight, val);
		}
		else
		{
			node->mRight = new Node();
			node->mRight->mData = val;
			node->mRight->mLeft = nullptr;
			node->mRight->mRight = nullptr;
		}
	}
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::Remove(Node* node, const T& val)
{
	if (node)
	{
		if (val == node->mData)
		{
			// has no children
			if (node->mLeft == nullptr && node->mRight == nullptr)
			{
				delete node;
				node = nullptr;
			}
			// Only has 1 child (right)
			else if (node->mLeft == nullptr && node->mRight != nullptr)
			{
				Node* temp = node;
				node = node->mRight;
				delete temp;
			}
			// Only has 1 child (left)
			else if (node->mLeft != nullptr && node->mRight == nullptr)
			{
				Node* temp = node;
				node = node->mLeft;
				delete temp;
			}
			// Has 2 children
			else
			{
				node->mData = Min(node->mRight);
				Remove(node->mRight, node->mData);
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

template< typename T >
T BinaryTree<T>::Min(Node* node)
{
	if (node)
	{
		return Min(node->mLeft);
	}
	return 0;
}

template< typename T >
const typename BinaryTree<T>::Node* BinaryTree<T>::Find(typename BinaryTree<T>::Node* node, const T& val)
{
	if (node != nullptr)
	{
		if (node->mData == val)
		{
			return node;
		}
		else if (val < node->mData)
		{
			return Find(node->mLeft, val);
		}
		else if (val > node->mData)
		{
			return Find(node->mRight, val);
		}
	}
	return nullptr;
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::PreOrder(Node* node) const
{
	if (node)
	{
		std::cout << node->mData << std::endl;
		PreOrder(node->mLeft);
		PreOrder(node->mRight);
	}
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::InOrder(Node* node) const
{
	if (node)
	{
		InOrder(node->mLeft);
		std::cout << node->mData << std::endl;
		InOrder(node->mRight);
	}
}
// ------------------------------------------------------------------------

template< typename T >
void BinaryTree<T>::PostOrder(Node* node) const
{
	if (node)
	{
		PostOrder(node->mLeft);
		PostOrder(node->mRight);
		std::cout << node->mData << std::endl;
	}
}
// ------------------------------------------------------------------------

template< typename T >
unsigned int BinaryTree<T>::Size(Node* node) const
{
	if (node != nullptr)
	{
		int sz = Size(node->mLeft) + Size(node->mRight);
		return sz + 1;
	}
	return 0;
}

// ------------------------------------------------------------------------

template< typename T >
unsigned int BinaryTree<T>::Depth(Node* node) const
{
	if (node != nullptr)
	{
		int left = Depth(node->mLeft);
		int right = Depth(node->mRight);
		return (left > right) ? left+1 : right+1;
	}
	return 0;
}

template< typename T >
typename BinaryTree<T>::Node* BinaryTree<T>::Clone(Node* node)
{
	if (node)
	{
		return Clone(node->mLeft);
	}
	return node;
}

bool testBinaryTree();

int main()
{


	std::cout << "Testing BinaryTree...\n";
	if (testBinaryTree())
	{
		std::cout << "Test sucessful!\n";
	}
	else
	{
		std::cout << "Test failed\n";
	}

	return 0;
}

bool testBinaryTree()
{
	BinaryTree<int> mybtree;
	mybtree.Insert(2);
	mybtree.Insert(4);
	mybtree.Insert(5);
	mybtree.Insert(3);
	mybtree.Insert(6);

	std::cout << "Found: " << mybtree.Find(4)->mData << std::endl;
	std::cout << "Depth: " << mybtree.Depth() << std::endl;
	std::cout << "Size: " << mybtree.Size() << std::endl;

	std::cout << "PreOrder\n";
	mybtree.PreOrder();

	std::cout << "InOrder\n";
	mybtree.InOrder();

	std::cout << "PostOrder\n";
	mybtree.PostOrder();

	BinaryTree<int> mybtreecopy(mybtree);
	std::cout << "mybtreecopy PreOrder\n";
	mybtreecopy.PreOrder();


	return true;
}