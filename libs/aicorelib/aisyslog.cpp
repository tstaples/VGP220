//
// File: aisyslog.cpp
// Created 15/04/2014
// (c)2014 by Tyler
//

#include "stdafx.h"

#include <Windows.h>
#include <ctime>
#include <process.h>
#include <direct.h>

#include "aicore/aisyslog.h"
#include "aicore/aidebug.h"
#include "aicore/aisemaphore.h"


// ------------------------------------------------------

/*	__cdecl			- read right to left
					- caller is responsible for cleaning the stack
	__stdcall		- cleans its own stack when it goes out of scope
	__thiscall		- default "*this" argument for class members
	__fastcall		- loads var to cpu so it doesn't have to retrieve it
					  from cache. Should only be used for high speed math~
*/

namespace AI
{

// Instantiate the instance
Syslog *Syslog::spInstance = nullptr;

unsigned int __stdcall syslogThreadFunc( void *pvArg )
{
	Syslog *pSyslog = reinterpret_cast< Syslog * >( pvArg );
	if ( pSyslog )
	{
		pSyslog->writeLog();
	}
	return 0;
}

// ------------------------------------------------------

Syslog::Syslog()
	:	mIsItitialized( false )
	,	mMutex( 10000 )
	,	mSemaphore( 10000 )
{
	
}

Syslog::~Syslog()
{
}
// ------------------------------------------------------

Syslog &Syslog::Get()
{
	if ( !spInstance )
	{
		spInstance = new Syslog();
		//AIAssert( spInstance != nullptr );
	}
	return *spInstance;
}
// ------------------------------------------------------


bool Syslog::openLog( UINT facilities, const char *pToolname )
{
	if ( !mIsItitialized )
	{
		/* TODO: Do something with facilities 
			
			- Load default log file from config created by aibuild.build
		*/

		mThreadID = 0;
		unsigned int initialRunState = 0; // Running
		mThreadHandle = (void*)_beginthreadex( 
				nullptr,			// security
				(65535),			// stack
				&syslogThreadFunc,	// thread function
				this,				// arg*
				initialRunState,	// runstate (suspended/running)
				&mThreadID );		// returned tid   ... &mThreadId
			if(!mThreadHandle)
			{
				mIsItitialized = false;
			}

		// The AILOGDIR enviroment variable is set by the nant build script.
		//char *env = getenv("AILOGDIR");
		//AIAssertFunc( ml != NULL, "AI assert", "Enviroment var is null", "aisyslog.cpp", 95, false );
		//dbPrintf( true, "Env %s", env );

		// Temporily taking the arg as the path. Optimally it would get the path from an environment variable.
		mhLog = fopen( pToolname, "a+" );

		//if ( env )
		//{
		//	mLogPath.copy( env, 0, strlen( env ) );
		//	mLogPath.append( pToolname );
		//	mLogFile = mLogPath, ".log";

		//	// Temporily taking the arg as the path. Optimally it would get the path from an environment variable.
		//	mhLog = fopen( pToolname, "a+" );
		//}
		//else
		//{
		//	mLogPath = pToolname;
		//}

		if ( mhLog )
		{
			mIsItitialized = true;
		}
	}
	return ( mIsItitialized );
}
// ------------------------------------------------------

void Syslog::closeLog()
{
	if ( mIsItitialized )
	{
		// when blocked on a semaphore you need to trigger it
		// in order to shut down
		mSemaphore.ReleaseSemaphore();

		// Wait until the worker thread has exited cleanly.
		WaitForSingleObject( mThreadHandle, 1000 );

		// Kill the thread
		CloseHandle( mThreadHandle );
	}
}
// ------------------------------------------------------

void Syslog::log( UINT priority, const char *category, const char *pFormat, ... )
{
	if ( mIsItitialized )
	{
		int len = NULL;
		const int kBufflen = 8196;
		char buff[kBufflen];

		char *pPri;
		switch ( priority )
		{
		case kLogEmerg:
			pPri = "EMERG";
			break;
		case kLogAlert:
			pPri = "ALERT";
			break;
		case kLogCrit:
			pPri = "CRIT";
			break;
		case kLogErr:
			pPri = "ERROR";
			break;
		case kLogWarning:
			pPri = "WARN";
			break;
		case kLogNotice:
			pPri = "NOTICE";
			break;
		case kLogInfo:
			pPri = "INFO";
			break;
		case kLogDebug:
		default:
			pPri = "DEBUG";
			break;
		}	
		
		time_t pTimeStamp = time( NULL );
		len += _snprintf( buff + len, kBufflen - len, "[%s", ctime( &pTimeStamp ) ) - 1;	// -1 is to remove '\n'
		len += _snprintf( buff + len, kBufflen - len, "] %s ", pPri );
		len += _snprintf( buff + len, kBufflen - len, "%s ", category );

		va_list va;
		va_start( va, pFormat );
		len += _vsnprintf( buff + len, kBufflen - len, pFormat, va );
		va_end( va );
		len += _snprintf( buff + len, kBufflen - len, "\n" );	// carriage return


		char *pBuff = new char[len+1];
		memcpy( pBuff, buff, len );
		pBuff[len] = 0;		// Null terminate

		mMutex.GetMutex();
		mLogQ.push( pBuff );
		mMutex.ReleaseMutex();

		// Tell worker thread there is a new item on the queue
		mSemaphore.ReleaseSemaphore();
	}
}
// ------------------------------------------------------

// facility == output debug string
// facility == network syslog
// facility == console
// facility == stderr / stdout
// facility == windows event manager

void Syslog::writeLog()
{
	//while ( mIsItitialized )
	while ( 1 )
	{
		if ( mSemaphore.GetSemaphore() == cAISemaphore::kSignaled )
		{
			if ( !mLogQ.empty() )
			{
				char *pBuff = mLogQ.front();

				// Safely put the item on the queue
				mMutex.GetMutex();
				mLogQ.pop();
				mMutex.ReleaseMutex();			

				// Facility == local log file
				if ( mhLog )
				{
					int i=0;
					dbPrintf( false, "%d: Writing: %s to file", i++, pBuff );

					UINT bytesWritten = 
						fwrite( pBuff, 1, strlen( pBuff ), mhLog );

					fflush( mhLog );
				}
				delete [] pBuff;
			}
		}
	}
}

}