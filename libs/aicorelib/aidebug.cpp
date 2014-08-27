//
// File: aidebug.cpp
// Created 15/04/2014
// (c)2014 by Tyler
//

#include "stdafx.h"
#include "aicore/aidebug.h"
#include <Windows.h>

#ifdef _DEBUG	
void AIDebugPrintf( bool writeCon, const char *pFormat, ... )
{
	char buff[8196];

	va_list va;
	va_start( va, pFormat );

	vsnprintf( buff, sizeof( buff ), pFormat, va );

	va_end( va );

	if ( writeCon ) 
	{
		printf( buff );
		printf( "\n" );
	}

	::OutputDebugStringA( buff );
	::OutputDebugStringA( "\n" );
}
#endif

#ifdef _DEBUG

/* TODO: add callstack trace to window */
bool AIAssertFunc( bool exp, const char *pExp, const char *pMsg, 
				   const char *pFile, const int line, bool *ignore )
{
	char buff[8196];
	sprintf( buff, "Debug Assert\n"
					"%s(%d)\n\n"
					"Expression: %s\n"
					"Message: %s", 
					pFile, line, pExp, pMsg );

	dbPrintf( true, buff );

	if ( !exp )
	{
		int ret = MessageBoxA( NULL, buff, "AIAssert", MB_ABORTRETRYIGNORE | MB_ICONERROR );

		switch ( ret )
		{
		case IDABORT:
			return true;
		case IDRETRY:
			return false;
		case IDIGNORE:
			*ignore = true;
			return false;
		}

		return true;
	}
	return false; // Expression is valid
}
#endif