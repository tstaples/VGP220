//
// File: aisyslog.h
// Created 15/04/2014
// (c)2014 by Tyler
//

#ifndef _AISYSLOG_H
#define _AISYSLOG_H
#pragma once

#include "aicore/aimutex.h"
#include "aicore/aisemaphore.h"
#include <queue>

namespace AI
{

class Syslog
{
// --------------------------------
public:
// --------------------------------

	~Syslog();

	// Singleton accessor
	static Syslog &Get();

	enum ePriorities
	{
		kLogEmerg,		// System unstable
		kLogAlert,		// Action must be taken immediatley
		kLogCrit,		// Critical condition
		kLogErr,		// Error conditions
		kLogWarning,	// Warning conditions
		kLogNotice,		// Normal but significant conditions
		kLogInfo,		// Informational
		kLogDebug		// Debug-level messages
	};

// --------------------------------
protected:	// member vars
// --------------------------------

	// Protected constructor so the class cannot be instantiated outside it's usage
	Syslog();

	// Singleton pointer
	static Syslog *spInstance;

	// Write thread
	friend unsigned int __stdcall syslogThreadFunc( void *pvArg );
	void *mThreadHandle;
	unsigned int mThreadID;

	// Log options
	UINT mCatMask;			// Category
	UINT mFacMask;			// Facility
	bool mIsItitialized;
	std::string mLogPath;	// Logging path
	std::string mLogFile;	// Logging file

	// Log handle
	FILE *mhLog;

	cAIMutex mMutex;			// Mutex handle
	cAISemaphore mSemaphore;	// Semaphore handle

	// Messages to be written
	std::queue< char * > mLogQ;

	// Disc I/O is expensive 
	void writeLog();

// --------------------------------
public:	// Methods
// --------------------------------

	// Init and open the log for writing
	bool openLog( UINT facilities, const char *pFilename );

	// Shut everything down
	void closeLog();

	// Write to disc
	void log( UINT priority, const char *category, const char *pFormat, ... );

	
};

}
#endif	// Header guard


/*	Initial state = unitialized 
	
	Steps:
	1. open log

	- Thread for writing to disk
	- Thread for queueing data

	Mutex:
		- locks a process
		- If threads are switched and another thread tries to access it while it's locked, it is blocked and 
		the next process is grabbed. Once that mutex is unlocked, another process using a lock can now access it.

*/