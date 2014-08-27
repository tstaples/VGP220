//
// File: aimutex.cpp
// Date: 2012/04/02
// Updated: 2014/04/22
// (c)2014 by Tyler
//


#include "stdafx.h"

#include <Windows.h>
#include <process.h>

#include "aicore/aimutex.h"
#include "aicore/aidebug.h"



cAIMutex::cAIMutex( UINT timeout )
	:	mMutex(NULL)
	,	mTimeout(timeout)
{
	mMutex = CreateMutex( NULL, FALSE, NULL );
	// Security : NUll = inherit from parent app
	// Init in a locked state?
	// Mutex name

	if( !mMutex )
	{
		AIAssert( false, "Mutex failed" );
	}
}
// ------------------------------------------------------

cAIMutex::~cAIMutex()
{
	CloseHandle( mMutex );
}
// ------------------------------------------------------

unsigned int cAIMutex::GetMutex()
{
	UINT rc = WaitForSingleObject( mMutex, mTimeout );

	switch( rc )
	{
	case WAIT_OBJECT_0:
		return cAIMutex::kSignaled;	// Object was retrieved

	case WAIT_TIMEOUT:				// Timeout expired while waiting for object
		return cAIMutex::kTimeout;

	default:						// Object not retrieved
		// WAIT_FAILED || WAIT_ABANDONED
		return cAIMutex::kFailed;
	}
}
// ------------------------------------------------------

void cAIMutex::ReleaseMutex()
{
	::ReleaseMutex( mMutex );
}