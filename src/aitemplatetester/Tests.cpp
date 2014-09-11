#include "aitl.h"
#include "ReversePolish.h"
#include "Tests.h"
#include <map>
#include <string>

typedef std::map<std::string, bool(*)(void)> Tests_map;

int main()
{
	// TODO: have main take cmd line args which determine which tests to run.
	// This way we can create a toolbar button which runs a bat file calling this
	// with the appropriate args.

	Tests_map tests;
	//tests.insert(std::make_pair("Array", &testArray));
	//tests.insert(std::make_pair("Array2", &testArray2));
	//tests.insert(std::make_pair("BinaryTree", &testBinaryTree));
	//tests.insert(std::make_pair("BitVector", &testBitVector));
	//tests.insert(std::make_pair("Stack", &testStack));
	//tests.insert(std::make_pair("Queue", &testQueue));
	//tests.insert(std::make_pair("ReversePolish", &testReversePolish));
	//tests.insert(std::make_pair("HashTable", &testHashTable));
	tests.insert(std::make_pair("PriorityQueue", &testPriorityQueue));

	Tests_map::iterator it = tests.begin();
	while (it != tests.end())
	{
		std::cout << "Testing " << it->first << "...\n";
		if (it->second())
		{
			std::cout << "Test sucessful!\n";
		}
		else
		{
			std::cout << "Test failed\n";
		}
		++it;
	}
	return 0;
}