#include "Tests.h"
#include "ReversePolish.h"

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