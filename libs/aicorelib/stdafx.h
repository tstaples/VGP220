// Precompiled header for aicorelib
#pragma once

#include "targetver.h"

// ------------------------------

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_WARNINGS


#define MAX_PATH 260

#else

// Typedefs that are default in win32, but may not be on other platforms

typedef unsigned int UINT;
typedef unsigned long int ULONG;
typedef unsigned short USHORT;
typedef unsigned char UCHAR;

#endif

// ------------------------------

// C headers
#include <stdio.h>


// ------------------------------

// C++ Headers
#include <cstdarg>
#include <cstring>
