//
// File: aimutex.h 
// Date: 2012/04/02
// Updated: 2014/04/22
// (c)2014 by Tyler
//

#ifndef _AIMUTEX_H
#define _AIMUTEX_H

/*	Locks out other threads from accessing
	data in the locked process until released. */

class cAIMutex
{
public:

	enum
	{
		kSignaled,
		kTimeout,
		kFailed
	};

public: // cAIMutex

	cAIMutex( UINT timeout );
	~cAIMutex();

	UINT GetMutex();

	void ReleaseMutex();

protected: // member vars

	void *mMutex;	// Mutext handle
	UINT mTimeout;	// Timeout (ms)
};

#endif // __AIMUTEX_H