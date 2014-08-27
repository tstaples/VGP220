//
// File: aisemaphore.cpp
// Date: 29/04/2014
// (c)2014 by Tyler
//


#include "stdafx.h"

#include <Windows.h>
#include <process.h>

#include "aicore/aisemaphore.h"
#include "aicore/aidebug.h"



cAISemaphore::cAISemaphore( unsigned int timeout )
	:	mSemaphore(NULL)
	,	mTimeout(timeout)
{
	mSemaphore = CreateSemaphore(
		nullptr,	// Security
		0,			// Initial Count
		1000,		// Max
		NULL );		// Name

	if( !mSemaphore )
	{
		dbPrintf( false, "Semaphore failed" );
	}
}
// ------------------------------------------------------

cAISemaphore::~cAISemaphore()
{
	CloseHandle( mSemaphore );
}
// ------------------------------------------------------

unsigned int cAISemaphore::GetSemaphore()
{
	UINT rc = WaitForSingleObject( mSemaphore, mTimeout );

	switch( rc )
	{
	case WAIT_OBJECT_0:
		return cAISemaphore::kSignaled;	// Object was retrieved

	case WAIT_TIMEOUT:				// Timeout expired while waiting for object
		return cAISemaphore::kTimeout;

	default:						// Object not retrieved
		// WAIT_FAILED || WAIT_ABANDONED
		return cAISemaphore::kFailed;
	}
}
// ------------------------------------------------------

/*	Give out the initial number of tickets, any thread
	can get a ticket. 
*/

void cAISemaphore::ReleaseSemaphore()
{
	::ReleaseSemaphore( mSemaphore, 1, NULL );
}