#ifndef _BITVECTOR_H
#define _BITVECTOR_H

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

#endif