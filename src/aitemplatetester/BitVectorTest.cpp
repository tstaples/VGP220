#include "Tests.h"
#include "bitvector.h"

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
	bv2.Set(30, 1);
	assert(bv2.Get(30) == 1);
	assert(bv.Get(30) == 1);

	// Testing clear and set
	bv.ClearAll();
	assert(bv.Get(11) == 0);
	bv.SetAll();
	assert(bv.Get(11) == 0);

	bv.Clear();
	bv2.Clear();

	return true;
}