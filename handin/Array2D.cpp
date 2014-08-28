#include <assert.h>
#include <iostream>
#include <type_traits>
#include "aicore/aidebug.h"


// Proxy class is for enabling the use of the '[][]' operation.
template< class T >
class Proxy
{
public:
	Proxy( T* data, unsigned int width, unsigned int height ) 
		: pData( data ), mWidth( width ), mHeight( height ) {}
	~Proxy() {}

	T& operator[]( unsigned int index )
	{
		// Index is the 'y' value.
		AIAssertMsg( index < mHeight, "Array subscript out of range" );

		// pData is a pointer to Array2's mData array + the 'x' offset.
		// The 'y' offset is added to get the desired element which is returned
		return *(pData + (index * mWidth));
	}
	const T& operator[]( unsigned int index ) const
	{
		AIAssertMsg( index < mHeight, "Array subscript out of range" );
		return *(pData + (index * mWidth));
	}

private:
	T* pData;
	unsigned int mWidth;
	unsigned int mHeight;
};
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

template< class T >
class Array2
{
public:
	Array2();
	Array2( unsigned int width, unsigned int height, T defVal );
	Array2( const Array2& rhs );
	~Array2();

	// Resizes the array specified and sets new values to the defaultVal
	void Resize( unsigned int width, unsigned int height, T defVal );

	// deletes the array and resets size
	void Clear();
	
	unsigned int Width() const;
	unsigned int Height() const;

	Array2& operator=( const Array2& rhs );

	// Return a Proxy object to enable the use of '[][]'
	Proxy<T> operator[]( unsigned int index );
	const Proxy<T> operator[]( unsigned int index ) const;

	void Set( unsigned int x, unsigned int y, const T& value );
	const T& Get( unsigned int x, unsigned int y ) const;

private:
	T* mData;
	unsigned int mWidth;
	unsigned int mHeight;
};

// ------------------------------------------------------------------------
// Array2 Definitions
// ------------------------------------------------------------------------

template< class T >
Array2<T>::Array2()
	:	mData( nullptr )
	,	mWidth( 0 )
	,	mHeight( 0 )
{
	// Disallow pointers because I'm too lazy to make exceptions for them.
	// ie. deleting
	AIAssertMsg( !std::is_pointer<T>::value, "Pointer to type not allowed" );
}
// ------------------------------------------------------------------------

template< class T >
Array2<T>::Array2( unsigned int width, unsigned int height, T defVal )
	:	mData( nullptr )
	,	mWidth( width )
	,	mHeight( height )
{
	AIAssertMsg( !std::is_pointer<T>::value, "Pointer to type not allowed" );
	AIAssertMsg( width > 0 && height > 0, "Invalid dimensions" );

	unsigned int dim = width * height;
	mData = new T[dim];
	for ( unsigned int i=0; i < dim; ++i )
	{
		mData[i] = defVal;
	}
}
// ------------------------------------------------------------------------

template< class T >
Array2<T>::Array2( const Array2& rhs )
{
	// = operator is overloaded to do the same thing.
	*this = rhs;
}
// ------------------------------------------------------------------------

template< class T >
Array2<T>::~Array2()
{
	// Cleanup before destroying
	Clear();
}
// ------------------------------------------------------------------------

template< class T >
void Array2<T>::Resize( unsigned int width, unsigned int height, T defVal )
{
	const unsigned int dimension = width * height;
	T* temp = new T[dimension];

	// Nested loops to make offset calculation much easier
	for ( unsigned int y=0; y < height; ++y )
	{
		for ( unsigned int x=0; x < width; ++x )
		{
			// Manually calculate offset since we're treating a 1D array as 2D
			const unsigned int index = x + (y * width);
			if ( x < mWidth && y < mHeight )
			{
				// copy over values from existing array.
				// Existing values retain position in new array unless they exist
				// beyond the new dimensions.
				temp[index] = Get( x, y );
			}
			else
			{
				temp[index] = defVal;
			}
		}
	}
	// Cleanup and assign
	Clear();
	mData = temp;
	temp = nullptr;
	mWidth = width;
	mHeight = height;
}
// ------------------------------------------------------------------------

template< class T >
void Array2<T>::Clear()
{
	if ( mWidth > 0 || mHeight > 0 )
	{
		delete [] mData;
		mData = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}
// ------------------------------------------------------------------------

template< class T >
unsigned int Array2<T>::Width() const
{
	return mWidth;
}
// ------------------------------------------------------------------------

template< class T >
unsigned int Array2<T>::Height() const
{
	return mHeight;
}
// ------------------------------------------------------------------------

template< class T >
Array2<T>& Array2<T>::operator=( const Array2& rhs )
{
	// Self assignment check. Absolutely necessary for objects with heap allocated members.
	if ( this != &rhs )
	{
		if ( rhs.mWidth > 0 || rhs.mHeight > 0 )
		{
			unsigned int dim = rhs.mWidth * rhs.mHeight;
			mData = new T[dim];
			for ( unsigned int i=0; i < dim; ++i )
			{
				mData[i] = rhs.mData[i];
			}
		}
		else
		{
			mData = nullptr;
		}
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;
	}
	return *this;
}
// ------------------------------------------------------------------------

template< class T >
void Array2<T>::Set( unsigned int x, unsigned int y, const T& value )	
{
	AIAssertMsg( x < mWidth && y < mHeight, "Array subscript out of range" );
	*(mData + (x + (mWidth * y))) = value;
}
// ------------------------------------------------------------------------

template< class T >
const T& Array2<T>::Get( unsigned int x, unsigned int y ) const
{
	AIAssertMsg( x < mWidth && y < mHeight, "Array subscript out of range" );
	return (*(mData + (x + (mWidth * y))));
}
// ------------------------------------------------------------------------

template< class T >
Proxy<T> Array2<T>::operator[]( unsigned int index )
{
	AIAssertMsg( index < mWidth, "Array subscript out of range" );

	// Proxy acts as our proxy to allow the use of the [][] operator.
	// The index passed into this operator is the 'x' position.
	// Proxy's [] operator will return the desired element located at 
	// the y + the x offset.
	Proxy<T> Proxy( mData + (index), mWidth, mHeight );

	return (Proxy);
}
// ------------------------------------------------------------------------

template< class T >
const Proxy<T> Array2<T>::operator[]( unsigned int index ) const
{
	AIAssertMsg( index < mWidth, "Array subscript out of range" );

	Proxy<T> Proxy( mData + (index), mWidth, mHeight );

	return (Proxy);
}

// ------------------------------------------------------------------------
// Driver code
// ------------------------------------------------------------------------

int main()
{
	Array2< int > myArray2( 2, 3, 0 );
	
	// Testing intitial values were set
	assert( myArray2.Get( 1, 0 ) == 0 );
	assert( myArray2.Width() == 2 );
	assert( myArray2.Height() == 3 );

	// Overloaded accessor operator
	myArray2[1][2] = 1;
	assert( myArray2.Get( 1, 2 ) == 1 );

	// Testing Set()
	myArray2.Set( 1, 1, 14 );
	assert( myArray2.Get( 1, 1 ) == 14 );

	// Resize the array and test new values
	myArray2.Resize( 4, 5, 1 );
	assert( myArray2.Width() == 4 );
	assert( myArray2.Height() == 5 );
	assert( myArray2.Get( 3, 2 ) == 1 );
	
	// Previous values persisted
	assert( myArray2.Get( 1, 2 ) == 1 );
	assert( myArray2.Get( 0, 2 ) == 0 );
	assert( myArray2[1][1] == 14 );

	// Testing copy constructor
	Array2< int > myArray2Copy( myArray2 );
	assert( myArray2Copy.Width() == 4 );
	assert( myArray2Copy.Height() == 5 );
	assert( myArray2Copy.Get( 3, 2 ) == 1 );
	
	// Testing that myArray2Copy isn't pointing to myArray2
	myArray2.Set( 3, 1, 10 );
	assert( myArray2.Get( 3, 1 ) == 10 );
	assert( myArray2Copy.Get( 3, 1 ) != 10 );

	// Data was cleared
	myArray2.Clear();
	assert( myArray2.Width() == 0 );
	assert( myArray2.Height() == 0 );

	// Assignment operator
	myArray2 = myArray2Copy;
	assert( myArray2.Width() == myArray2Copy.Width() );
	assert( myArray2.Height() == myArray2Copy.Height() );

	return 0;
}