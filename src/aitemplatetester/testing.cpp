#include "aitl.h"
#include "ReversePolish.h"

#include <iostream>

bool testArray();
bool testArray2();
bool testBinaryTree();
bool testBitVector();
bool testStack();
bool testQueue();

bool testReversePolish();

//int main()
//{
//
//
//	// TODO: have main take cmd line args which determine which tests to run.
//	// This way we can create a toolbar button which runs a bat file calling this
//	// with the appropriate args.
//
//
//	std::cout << "Testing Array...\n";
//	if (testArray())
//	{
//		std::cout << "Test sucessful!\n";
//	}
//	else
//	{
//		std::cout << "Test failed\n";
//	}
//
//	std::cout << "Testing Array2...\n";
//	if (testArray2())
//	{
//		std::cout << "Test sucessful!\n";
//	}
//	else
//	{
//		std::cout << "Test failed\n";
//	}
//
//	//std::cout << "Testing BitVector...\n";
//	//if (testBitVector())
//	//{
//	//	std::cout << "Test sucessful!\n";
//	//}
//	//else
//	//{
//	//	std::cout << "Test failed\n";
//	//}
//
//	std::cout << "Testing BinaryTree...\n";
//	if (testBinaryTree())
//	{
//		std::cout << "Test sucessful!\n";
//	}
//	else
//	{
//		std::cout << "Test failed\n";
//	}
//
//	std::cout << "Testing Stack...\n";
//	if (testStack())
//	{
//		std::cout << "Test sucessful!\n";
//	}
//	else
//	{
//		std::cout << "Test failed\n";
//	}
//
//	std::cout << "Testing Queue...\n";
//	if (testQueue())
//	{
//		std::cout << "Test sucessful!\n";
//	}
//	else
//	{
//		std::cout << "Test failed\n";
//	}
//
//	std::cout << "Testing ReversePolish...\n";
//	if (testReversePolish())
//	{
//		std::cout << "Test sucessful!\n";
//	}
//	else
//	{
//		std::cout << "Test failed\n";
//	}
//
//
//	return 0;
//}

bool testArray()
{
	Array< int > myArray;
	
	// Test initial size is 0
	assert( myArray.Size() == 0 );
	
	// Resize the array to 5 elements
	myArray.Resize( 5, 0 );
	// Test the size of the array is 5
	assert( myArray.Size() == 5 );
	
	// Assign the value 6 to the second 3 element
	myArray[2] = 6;
	assert( myArray[2] == 6 );
	
	// Resize the array to 10 elements
	myArray.Resize( 10, 3 );
	// Test the size of the array is 10
	assert( myArray.Size() == 10 );
	// Test the value of the third element is still 6
	assert( myArray[2] == 6 );
	// Test the value of the 8th element is the default value
	assert( myArray[7] == 3 );
	
	// Resize the array down to 3
	myArray.Resize( 3, 0 );
	// Test the size is 3
	assert( myArray.Size() == 3 );
	// Test the third element's value is still 6
	assert( myArray[2] == 6 );
	
	// Clear the array
	myArray.Clear();
	// Test that the size of the array is 0
	assert( myArray.Size() == 0 );
	return true;

}

bool testArray2()
{
	Array2< int > myArray2(2, 3, 0);

	// Testing intitial values were set
	assert(myArray2.Get(1, 0) == 0);
	assert(myArray2.Width() == 2);
	assert(myArray2.Height() == 3);

	// Overloaded accessor operator
	myArray2[1][2] = 1;
	assert(myArray2.Get(1, 2) == 1);

	// Testing Set()
	myArray2.Set(1, 1, 14);
	assert(myArray2.Get(1, 1) == 14);

	// Resize the array and test new values
	myArray2.Resize(4, 5, 1);
	assert(myArray2.Width() == 4);
	assert(myArray2.Height() == 5);
	assert(myArray2.Get(3, 2) == 1);

	// Previous values persisted
	assert(myArray2.Get(1, 2) == 1);
	assert(myArray2.Get(0, 2) == 0);
	assert(myArray2[1][1] == 14);

	// Testing copy constructor
	Array2< int > myArray2Copy(myArray2);
	assert(myArray2Copy.Width() == 4);
	assert(myArray2Copy.Height() == 5);
	assert(myArray2Copy.Get(3, 2) == 1);

	// Testing that myArray2Copy isn't pointing to myArray2
	myArray2.Set(3, 1, 10);
	assert(myArray2.Get(3, 1) == 10);
	assert(myArray2Copy.Get(3, 1) != 10);

	// Data was cleared
	myArray2.Clear();
	assert(myArray2.Width() == 0);
	assert(myArray2.Height() == 0);

	// Assignment operator
	myArray2 = myArray2Copy;
	assert(myArray2.Width() == myArray2Copy.Width());
	assert(myArray2.Height() == myArray2Copy.Height());

	return true;
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

	return true;
}

bool testBitVector()
{
	BitVector bv(64);

	// Testing initial values
	assert(bv.Size() == 64);
	assert(bv.Get(12) == 0);

	// Testing Set
	bv.Set(24, 1);
	assert(bv.Get(24) == 1);

	bv.Set(36, 1);
	assert(bv.Get(36) == 1);

	bv.Set(30, 0);
	assert(bv.Get(30) == 0);

	// Testing resize
	bv.Resize(72);
	assert(bv.Size() == 72);
	assert(bv.Get(12) == 0);
	assert(bv.Get(24) == 1);

	// Testing copy constructor and assignment operator
	BitVector bv2(bv);
	assert(bv.Size() == 72);
	assert(bv.Get(12) == 0);

	// Testing bv's values aren't altered by bv2
	bv2.Set(60, 1);
	assert(bv2.Get(60) == 1);
	assert(bv.Get(60) == 1);

	// Testing clear and set
	bv.ClearAll();
	assert(bv.Get(11) == 0);
	bv.SetAll();
	assert(bv.Get(11) == 1);

	bv.Clear();
	bv2.Clear();

	return true;
}

bool testStack()
{
	Stack<int> myStack;
	myStack.Push(1);
	myStack.Push(2);
	myStack.Push(3);

	assert(myStack.Top() == 3);

	myStack.Pop();
	assert(myStack.Top() == 2);

	Stack<int> myStackcopy(myStack);
	assert(myStackcopy.Top() == 2);
	myStackcopy.Pop();
	assert(myStackcopy.Top() == 1);

	return true;
}

bool testQueue()
{
	Queue<int> myQ;
	myQ.Enqueue(1);
	myQ.Enqueue(2);
	myQ.Enqueue(3);

	assert(myQ.Front() == 1);

	myQ.Dequeue();
	assert(myQ.Front() == 2);

	Queue<int> myQcopy(myQ);
	assert(myQcopy.Front() == 2);
	myQcopy.Dequeue();
	assert(myQcopy.Front() == 3);

	return true;
}

bool testReversePolish()
{
	ReversePolish myrp;

	// 5, 1, 2, +, 4, ×, +, 3, –			( 5 + ( ( 1 + 2 ) * 4 ) – 3
	std::cout << "Running equation: ( 5 + ( ( 1 + 2 ) * 4 ) – 3\n";
	myrp.AddNumber(5);
	myrp.AddNumber(1);
	myrp.AddNumber(2);
	myrp.AddSymbol('+');
	myrp.AddNumber(4);
	myrp.AddSymbol('*');
	myrp.AddSymbol('+');
	myrp.AddNumber(3);
	myrp.AddSymbol('-');
	assert(myrp.GetResult() == 14.0f);
	std::cout << "Test passed\n";

	// 4, 13, 5, /, +				( 4 + ( 13 / 5 ) )
	std::cout << "Running equation: ( 4 + ( 13 / 5 ) )\n";
	myrp.AddNumber(4);
	myrp.AddNumber(13);
	myrp.AddNumber(5);
	myrp.AddSymbol('/');
	myrp.AddSymbol('+');
	assert(myrp.GetResult() == 6.6f);
	std::cout << "Test passed\n";

	// 3, 4, +, 5, 6, +, *			( ( 3 + 4 ) * ( 5 + 6 ) )
	std::cout << "Running equation: ( ( 3 + 4 ) * ( 5 + 6 ) )\n";
	myrp.AddNumber(3);
	myrp.AddNumber(4);
	myrp.AddSymbol('+');
	myrp.AddNumber(5);
	myrp.AddNumber(6);
	myrp.AddSymbol('+');
	myrp.AddSymbol('*');
	assert(myrp.GetResult() == 77.0f);
	std::cout << "Test passed\n";

	return true;
}