#include "Tests.h"
#include "binarytree.h"

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

	return true;
}