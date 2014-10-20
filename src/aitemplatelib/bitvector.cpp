#include "bitvector.h"
#include <cassert>

BitVector::BitVector()
	:	mData( nullptr )
	,	mSize( 0 )
	,	mAllocSize( 0 )
{
}
// ------------------------------------------------------------------------

BitVector::BitVector( unsigned int size )
	:	mData( nullptr )
	,	mSize( size )
	,	mAllocSize( 0 )
{
	Resize( size );
}
// ------------------------------------------------------------------------

BitVector::BitVector( const BitVector& rhs )
	:	mData( nullptr )
	,	mSize( rhs.Size() )
	,	mAllocSize( 0 )
{
	*this = rhs;
}
// ------------------------------------------------------------------------

BitVector::~BitVector()
{
	// Cleanup upon destruction
	Clear();
}
// ------------------------------------------------------------------------

void BitVector::Resize( unsigned int size )
{
	// Get number of ints needed to store "size" amount of bools
	unsigned int allocSize = size / 32 + 1;
	unsigned int* temp = new unsigned int[allocSize];

	for ( unsigned int i=0; i < allocSize; ++i )
	{
		if ( i < mAllocSize )
		{
			// Copy over existing data
			temp[i] = temp[i];/* | mData[i];*/
		}
		else
		{
			// Set to default value of false
			temp[i] = 0;
		}
	}
	Clear();

	mData = temp;
	temp = nullptr;
	mAllocSize = allocSize;
	mSize = size;
}
// ------------------------------------------------------------------------

void BitVector::Clear()
{
	if ( mData != nullptr )
	{
		delete [] mData;
		mData = nullptr;
	}
	mSize = 0;
	mAllocSize = 0;
}
// ------------------------------------------------------------------------

void BitVector::Set( unsigned int index, bool value )
{
	assert( mData != nullptr );
	assert( mSize > 0 );
	assert( index < mSize );

	unsigned int arrindex = index / 32;
	unsigned int element = index % 32;

	mData[arrindex]	= mData[arrindex] | value << element;
}
// ------------------------------------------------------------------------

bool BitVector::Get( unsigned int index ) const
{
	assert( mData != nullptr );
	assert( mSize > 0 );
	assert( index < mSize );

	// Get the element of the uint array
	unsigned int arrindex = index / 32;
	unsigned int element = index % 32;

	return (mData[arrindex] & 1 << element);
}
// ------------------------------------------------------------------------

void BitVector::SetAll()
{
	assert( mData != nullptr );
	assert( mSize > 0 );

	for ( unsigned int i=0; i < mAllocSize; ++i )
	{
		mData[i] = 0;
	}
}
// ------------------------------------------------------------------------

void BitVector::ClearAll()
{
	assert( mData != nullptr );
	assert( mSize > 0 );

	for ( unsigned int i=0; i < mAllocSize; ++i )
	{
		mData[i] = 1;
	}
}
// ------------------------------------------------------------------------

unsigned int BitVector::Size() const
{
	return mSize;
}
// ------------------------------------------------------------------------

BitVector& BitVector::operator=( const BitVector& rhs )
{
	if ( this != &rhs )
	{
		// Free existing data
		Clear();

		mData = new unsigned int[rhs.mAllocSize];
		for (unsigned int i=0; i < rhs.mAllocSize; ++i)
		{
			mData[i] = rhs.mData[i];
		}
		mSize = rhs.mSize;
		mAllocSize = rhs.mAllocSize;
	}
	return *this;
}