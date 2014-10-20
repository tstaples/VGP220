#include "Tests.h"
#include "array.h"

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