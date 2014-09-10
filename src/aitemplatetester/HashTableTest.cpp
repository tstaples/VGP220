#include "aitl.h"
#include "HashTable.h"

#include <string>
#include <iostream>

bool testHashTable();

int main()
{
	std::cout << "Testing ReversePolish...\n";
	if (testHashTable())
	{
		std::cout << "Test sucessful!\n";
	}
	else
	{
		std::cout << "Test failed\n";
	}


	return 0;
}

bool testHashTable()
{
	HashTable<std::string, int> myHashTable(100);
	assert(myHashTable.Size() == 100);

	myHashTable.Insert("Tyler", 16);
	myHashTable.Insert("Tom", 11);

	std::cout << "Found: " << myHashTable.Find("Tyler") << std::endl;

	return true;
}