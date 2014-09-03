#ifndef INCLUDED_HASHTABLE_H
#define INCLUDED_HASHTABLE_H

#include "binarytree.h"


template <typename T>
class HashTable
{
public:
	typedef unsigned long Key;

	struct Entry
	{
		Key mKey;
		T mValue;
	};

	HashTable(unsigned int size);
	HashTable(const HashTable& rhs);
	~HashTable();

	void Clear();

	void Insert(const Key& key, const T& value);
	void Remove(const Key& key);

	Entry* Find(const Key& key);

	unsigned int Size() const;

	HashTable& operator=(const HashTable& rhs);

private:
	BinaryTree<Entry> mHashTree;
	unsigned int mSize;
};

// ------------------------------------------------------------

template <typename T>
HashTable<T>::HashTable(unsigned int size)
	:	mSize(size)
{
	for (int i=0; i < mSize; ++i)
	{
		Entry myEntry;
		myEntry.mKey = NULL;
		myEntry.mValue = nullptr;
		mHashTree.Insert(myEntry);
	}
}

template <typename T>
HashTable<T>::HashTable(const HashTable& rhs)
{
}

template <typename T>
HashTable<T>::~HashTable()
{
}

template <typename T>
void HashTable<T>::Clear()
{
	mHashTree.Clear();
}

template <typename T>
void HashTable<T>::Insert(const Key& key, const T& value)
{
	Entry entry;
	entry.mKey = key;
	entry.mValue = value;
	mHashTree.Insert(entry);
	++mSize;
}

template <typename T>
void HashTable<T>::Remove(const Key& key)
{
	// TODO
	--mSize;
}


template <typename T>
typename HashTable<T>::Entry* HashTable<T>::Find(const Key& key)
{
}

template <typename T>
unsigned int HashTable<T>::Size() const
{
	return mSize;
}

#endif

/*
class StrHash
{
public:
	StrHash(const char* string)
	{
		mHash = 5381;
		int c = static_cast<int>(*string++);
		while (c != NULL)
		{
			c = tolower(c);
			mHash = ((mHash << 5) + mHash) + ((unsigned long) c);
			c = (*string++);
		}
	}
	bool Compare(const StrHash& other) { return (mHash == other.mHash); }
private:
	unsigned long mHash;
};
*/