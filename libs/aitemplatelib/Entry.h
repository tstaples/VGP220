#ifndef INCLUDED_ENTRY_H
#define INCLUDED_ENTRY_H

template <typename T>
class Entry
{
	typedef unsigned long Key;
private:
	Key mKey;
	T mData;
public:
	Entry();
	~Entry();

	Entry(const Key& key, const T& val)
		:	mKey(key), mData(val) {}
	
	const Key GetKey() const { return mKey; }
	const T& GetData() const { return mData; }
};

#endif