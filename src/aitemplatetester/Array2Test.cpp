#include "Tests.h"
#include "array2.h"

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