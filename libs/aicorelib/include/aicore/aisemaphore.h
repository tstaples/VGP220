//
// File: aisemaphore.h
// Created 29/04/2014
// (c)2014 by Tyler
//

#ifndef _AISEMAPHORE_H
#define _AISEMAPHORE_H
#pragma once

/*	Purpose is to notify worker threads when there
	is work to be done. Uses 0 resources when checking. */

class cAISemaphore
{
// --------------------------------
public:
// --------------------------------

	enum
	{
		kSignaled,
		kTimeout,
		kFailed
	};

// --------------------------------
public: // Semaphore
// --------------------------------

	cAISemaphore( unsigned int mTimeout );
	~cAISemaphore();

	unsigned int GetSemaphore();

	void ReleaseSemaphore();

// --------------------------------
protected: // member vars
// --------------------------------

	void *mSemaphore;		// Semaphore handle
	unsigned int mTimeout;	// Timeout (ms)
};

#endif