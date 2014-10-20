#ifndef _ARRAY_H
#define _ARRAY_H

#include <assert.h>

template< class T >
class Array
{
public:
	Array();
	~Array();

	// Resizes the array specified and sets new values to the defaultVal
	void Resize( unsigned int size, T defaultVal );

	// deletes the array and resets size
	void Clear();
	
	// Returns the number of elements in the array
	unsigned int Size() const;

	// Overloaded accessor operator to set values at a specified index.
	// Tests if the subscript is within range
	T& operator[]( unsigned int index );

	// Overloaded accessor operator to get values at a specified index.
	// Tests if the subscript is within range
	const T& operator[]( unsigned int index ) const;

private:
	T* mData;				// Pointer to the array of data
	unsigned int mSize;		// Number of elements in mData
};
// ------------------------------------------------------------------------


template< class T >
Array<T>::Array()
	:	mSize( 0 )
	,	mData( nullptr )
{
}
// ------------------------------------------------------------------------

template< class T >
Array<T>::~Array()
{
	// There is data in the array
	if ( mSize )
	{
		// Free the memory allocated for mData
		Clear();
	}
}
// ------------------------------------------------------------------------

template< class T >
void Array<T>::Resize( unsigned int size, T defaultVal )
{
	// Allocate a new array of the  specified size
	T* newArr = new T[size];

	for ( unsigned int i=0; i < size; ++i )
	{
		// If there is existing data at the i'th element of mData
		if ( i < mSize )
		{
			// Assign it to that element of the new array
			newArr[i] = mData[i];
		}
		else
		{
			// Otherwise assign the default value
			newArr[i] = defaultVal;
		}
	}
	// Clear current array
	Clear();

	// Set mData to the address of the new arary
	mData = newArr;

	// Set newArr to null to prevent dangling pointers
	newArr = nullptr;

	// Set the size of the array to the new size
	mSize = size;
}
// ------------------------------------------------------------------------

template< class T >
void Array<T>::Clear()
{
	// Delete all the data in the array
	delete [] mData;

	// Set the pointer to null
	mData = nullptr;

	// Set the size of the array to 0
	mSize = 0;
}
// ------------------------------------------------------------------------

template< class T >
unsigned int Array<T>::Size() const
{
	// Return the number of elements in mData
	return mSize;
}
// ------------------------------------------------------------------------

template< class T >
T& Array<T>::operator[]( unsigned int index )
{
	// Test if the subscript is within range
	assert( index < mSize );

	// Assign a pointer to the start of mData
	T* aPtr = mData;

	// Increment the pointer to the specified index and return that value
	return *(aPtr + index);
}
// ------------------------------------------------------------------------

template< class T >
const T& Array<T>::operator[]( unsigned int index ) const
{
	// Test if the subscript is within range
	assert( index < mSize );

	// Assign a pointer to the start of mData
	T* aPtr = mData;

	// Increment the pointer to the specified index and return that value
	return *(aPtr + index);
}

#endif