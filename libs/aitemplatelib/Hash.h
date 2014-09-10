#ifndef INCLUDED_HASH_H
#define INCLUDED_HASH_H

template <typename T>
class Hash
{
	typedef unsigned long key;
public:
	Hash(const T& hkey);

	const key& Key() const { return mHash; }
	bool Compare(const Hash& other) { return (mHash == other.mHash); }
private:
	key mHash;
};

template <typename T>
Hash<T>::Hash(const T& hkey)
{
	mHash = 5381;
	int c = static_cast<int>(*hkey++);
	while (c != NULL)
	{
		c = tolower(c);
		mHash = ((mHash << 5) + mHash) + ((unsigned long) c);
		c = (*hkey++);
	}
}

#endif