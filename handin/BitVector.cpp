#include <cassert>

// ========================================================================
// BitVector.h
// ========================================================================

class BitVector
{
public:
	BitVector();
	BitVector( unsigned int size );
	BitVector( const BitVector& rhs );
	~BitVector();

	void Resize( unsigned int size );
	void Clear();

	void Set( unsigned int index, bool value );
	bool Get( unsigned int index ) const;

	void SetAll();		// Set all flags to be true
	void ClearAll();	// Sets all flags to false

	unsigned int Size() const;

	BitVector& operator=( const BitVector& rhs );

private:
	unsigned int* mData;
	unsigned int mSize;			// number of elements (bools)
	unsigned int mAllocSize;	// number of unsigned ints needed to store mSize of bools

};

// ========================================================================
// BitVector.cpp
// ========================================================================

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

// ========================================================================
// Driver code
// ========================================================================

int main()
{
	BitVector bv( 64 );
	
	// Testing initial values
	assert( bv.Size() == 64 );
	assert( bv.Get( 12 ) == 0 );

	// Testing Set
	bv.Set( 24, 1 );
	assert( bv.Get( 24 ) == 1 );
	
	bv.Set( 36, 1 );
	assert( bv.Get( 36 ) == 1 );

	bv.Set( 30, 0 );
	assert( bv.Get( 30 ) == 0 );

	// Testing resize
	bv.Resize( 72 );
	assert( bv.Size() == 72 );
	assert( bv.Get( 12 ) == 0 );
	assert( bv.Get( 24 ) == 1 );

	// Testing copy constructor and assignment operator
	BitVector bv2( bv );
	assert( bv.Size() == 72 );
	assert( bv.Get( 12 ) == 0 );

	// Testing bv's values aren't altered by bv2
	bv2.Set( 60, 1 );
	assert( bv2.Get( 60 ) == 1 );
	assert( bv.Get( 60 ) == 1 );

	// Testing clear and set
	bv.ClearAll();
	assert( bv.Get( 11 ) == 0 );
	bv.SetAll();
	assert( bv.Get( 11 ) == 1 );

	bv.Clear();
	bv2.Clear();

	return 0;
}