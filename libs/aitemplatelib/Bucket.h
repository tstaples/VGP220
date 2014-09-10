#ifndef INCLUDED_BUCKET_H
#define INCLUDED_BUCKET_H

#include "binarytree.h"

template <typename TVal>
class Bucket
{
public:
	typedef unsigned long Key;

	struct Entry
	{
		Key mKey;
		TVal mValue;
	};

	void Clear();

	// Inserts a new key-val pair in to a bucket
	void Insert(const Key& key, const TVal& value);
	void Remove(const Key& key);

	// Returns the value paired with the key
	Entry* Find(const Key& key);

	unsigned int Size() const;

private:
	// Holds all the entries for the keys associated with this bucket
	BinaryTree<Entry> mEntryTree;
	unsigned int mSize;	// number of elements in the tree
};


// ------------------------------------------------------------


template <typename T>
void Bucket<T>::Clear()
{
	mEntryTree.Clear();
}

template <typename T>
void Bucket<T>::Insert(const Key& key, const T& value)
{
	Entry entry;
	entry.mKey = key;
	entry.mValue = value;
	mEntryTree.Insert(entry);
	++mSize;
}

template <typename T>
void Bucket<T>::Remove(const Key& key)
{
	// TODO
	--mSize;
}


template <typename T>
typename Bucket<T>::Entry* Bucket<T>::Find(const Key& key)
{
}

template <typename T>
unsigned int Bucket<T>::Size() const
{
	return mSize;
}

#endif