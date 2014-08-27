// File: aidebug.h
// Created 15/04/2014
// (c)2014 by Tyler

#ifndef _AIDEBUG_H
#define _AIDEBUG_H

#pragma once
 
#ifdef _DEBUG	

void AIDebugPrintf( bool writeCon, const char *pFormat, ... );
#define dbPrintf AIDebugPrintf


// Sets a breakpoint
#define BREAKPOINT do { void __cdecl :: __debugbreak(void); __debugbreak(); } while (0)


// Assertion Macros
// expression = condition
bool AIAssertFunc( bool exp, const char *pExp, const char *pMsg, 
				   const char *pFile, const int line, bool *ignore );

#define AIAssert( exp ) _AI_ASSERT_MESSAGE( exp, #exp )
#define AIAssertMsg( exp, msg ) _AI_ASSERT_MESSAGE( exp, msg )
#define _AI_ASSERT_MESSAGE( exp, msg )\
{\
	static bool ignoreAlways = false; \
	if ( !ignoreAlways && AIAssertFunc( exp, #exp, msg, __FILE__, __LINE__, &ignoreAlways ) )\
	{\
		BREAKPOINT;\
	}\
}


#else  // Release build


/* All debug statements are replaced with void in release mode */
#define dbPrintf(...) void(0);
#define AIAssert(...) void(0);
#define AIAssertMsg(...) void(0);


#endif	// Build Type

#endif	// Header Guard