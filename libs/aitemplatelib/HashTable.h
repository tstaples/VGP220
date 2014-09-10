#ifndef INCLUDED_HASHTABLE_H
#define INCLUDED_HASHTABLE_H

//#include "Bucket.h"
#include <vector>
#include "Entry.h"
#include "pairtree.h"
#include "Hash.h"


template <typename TKey, typename TVal>
class HashTable
{
	typedef unsigned long Key;
private:
	typedef typename std::vector<PairTree<Entry<TVal>>> BucketList;
	//typedef std::pair<Key, TVal> KeyPair;

public:
	HashTable(unsigned int size);
	HashTable(const HashTable& rhs);
	~HashTable();

	void Clear();

	// Inserts a new key-val pair in to a bucket
	void Insert(const TKey& key, const TVal& value);
	void Remove(const TKey& key);

	// Returns the value paired with the key
	TVal* Find(const TKey& key);

	unsigned int Size() const;

	HashTable& operator=(const HashTable& rhs);

private:
	BucketList mBucketList;
	unsigned int mSize;	// Number of buckets
};

// ------------------------------------------------------------
// ------------------------------------------------------------

template <typename TKey, typename TVal>
HashTable<TKey, TVal>::HashTable(unsigned int size)
	:	mSize(size)
{
	mBucketList.resize(size);
}
// ------------------------------------------------------------

template <typename TKey, typename TVal>
HashTable<TKey, TVal>::HashTable(const HashTable& rhs)
{
}
// ------------------------------------------------------------

template <typename TKey, typename TVal>
HashTable<TKey, TVal>::~HashTable()
{
}
// ------------------------------------------------------------

template <typename TKey, typename TVal>
void HashTable<TKey, TVal>::Clear()
{
	for (int i=0; i < mSize; ++i)
	{
		mBucketList[i].Clear();
	}
	mBucketList.clear();
}
// ------------------------------------------------------------

template <typename TKey, typename TVal>
void HashTable<TKey, TVal>::Insert(const TKey& key, const TVal& value)
{
	// Convert the raw key to its hash value
	Hash<TKey> hash(key);
	unsigned int bucketIndex = hash.Key() % mSize;
	Entry entry(key, value);

	// Insert the pair
	mBucketList.at(bucketIndex).Insert(entry);
}
// ------------------------------------------------------------

template <typename TKey, typename TVal>
void HashTable<TKey, TVal>::Remove(const TKey& key)
{
	// TODO
	--mSize;
}
// ------------------------------------------------------------


template <typename TKey, typename TVal>
TVal* HashTable<TKey, TVal>::Find(const TKey& key)
{
	Hash<TKey> hash(key);
	unsigned int bucketIndex = hash.Key() % mSize;

	 return mBucketList[bucketIndex].Find(hash.Key());

}
// ------------------------------------------------------------

template <typename TKey, typename TVal>
unsigned int HashTable<TKey, TVal>::Size() const
{
	return mSize;
}
// ------------------------------------------------------------

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