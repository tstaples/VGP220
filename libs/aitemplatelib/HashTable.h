//#ifndef INCLUDED_HASHTABLE_H
//#define INCLUDED_HASHTABLE_H
//
//#include <vector>
//#include "pairtree.h"
//#include "Hash.h"
//
//
//template <typename TVal>
//class HashTable
//{
//	typedef unsigned long Key;
//public:
//	struct Entry
//	{
//		Key key;
//		TVal val;
//	};
//
//	HashTable(unsigned int size);
//	HashTable(const HashTable& rhs);
//	~HashTable();
//
//	void Clear();
//
//	// Inserts a new key-val pair in to a bucket
//	void Insert(const Key& key, const TVal& value);
//	void Remove(const Key& key);
//
//	// Returns the value paired with the key
//	Entry* Find(const Key& key);
//
//	unsigned int Size() const;
//	HashTable& operator=(const HashTable& rhs);
//
//private:
//	PairTree<Entry> mPTree;
//	unsigned int mSize;	// Number of buckets
//};
//
//// ------------------------------------------------------------
//// ------------------------------------------------------------
//
//template <typename TVal>
//HashTable<TVal>::HashTable(unsigned int size)
//	:	mSize(size)
//{
//}
//// ------------------------------------------------------------
//
//template <typename TVal>
//HashTable<TVal>::HashTable(const HashTable& rhs)
//{
//}
//// ------------------------------------------------------------
//
//template <typename TVal>
//HashTable<TVal>::~HashTable()
//{
//}
//// ------------------------------------------------------------
//
//template <typename TVal>
//void HashTable<TVal>::Clear()
//{
//	mPTree.Clear();
//}
//// ------------------------------------------------------------
//
//template <typename TVal>
//void HashTable<TVal>::Insert(const Key& key, const TVal& value)
//{
//	// Convert the raw key to its hash value
//	Hash<TVal> hash(key);
//	unsigned int bucketIndex = hash.Key() % mSize;
//	Entry entry(key, value);
//
//	// Insert the pair
//	mBucketList.at(bucketIndex).Insert(entry);
//}
//// ------------------------------------------------------------
//
//template <typename TVal>
//void HashTable<TVal>::Remove(const TKey& key)
//{
//	// TODO
//	--mSize;
//}
//// ------------------------------------------------------------
//
//
//template <typename TVal>
//TVal* HashTable<TVal>::Find(const TKey& key)
//{
//	Hash<TKey> hash(key);
//	unsigned int bucketIndex = hash.Key() % mSize;
//
//	 return mBucketList[bucketIndex].Find(hash.Key());
//
//}
//// ------------------------------------------------------------
//
//template <typename TVal>
//unsigned int HashTable<TVal>::Size() const
//{
//	return mSize;
//}
//// ------------------------------------------------------------
//
//#endif
//
///*
//class StrHash
//{
//public:
//	StrHash(const char* string)
//	{
//		mHash = 5381;
//		int c = static_cast<int>(*string++);
//		while (c != NULL)
//		{
//			c = tolower(c);
//			mHash = ((mHash << 5) + mHash) + ((unsigned long) c);
//			c = (*string++);
//		}
//	}
//	bool Compare(const StrHash& other) { return (mHash == other.mHash); }
//private:
//	unsigned long mHash;
//};
//*/