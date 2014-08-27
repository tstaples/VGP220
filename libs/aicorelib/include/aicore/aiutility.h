// File: aidebug.h
// Created 15/04/2014
// (c)2014 by Tyler

#ifndef _AIUTILITY_H
#define _AIUTILITY_H

#pragma once


typedef const char _CCHAR;
typedef const int _CINT;
typedef const short _CSHORT;
typedef const double _CDOUBLE;
typedef const float _CFLOAT;


#define repeat(i,x) for(unsigned i=0; i< x; ++i)

/*	MIN / MAX macros have problems of multiple evaluations if expressions 
	or function calls are used as arguments */

#ifndef MIN
#define MIN( n1, n2 )   ((n1) > (n2) ? (n2) : (n1))
#endif

#ifndef MAX
#define MAX( n1, n2 )   ((n1) > (n2) ? (n1) : (n2))
#endif

/*	Can only be used for fixed size arrays */
#define GET_ARRAY_LEN( arrayName ) (sizeof( arrayName ) / sizeof(( arrayName)[ 0 ] ))

#define IS_ODD( num )   ((num) & 1)
#define IS_EVEN( num )  (!IS_ODD( (num) ))


/* --- Network Related --- */

#define IS_LITTLE_ENDIAN()  (((*(short *)"21") & 0xFF) == '2')
#define IS_BIG_ENDIAN()     (((*(short *)"21") & 0xFF) == '1')
#define IS_DEFAULT_ENDIAN() IS_LITTLE_ENDIAN()


/*	If the current machine is not default endian, re-arranges the bytes of the
	given number. Does nothing if the current machine is default endian. */
#define REVERSE_BYTE_ARRAY( ByteArray, Size )\
        if (!IS_DEFAULT_ENDIAN())\
        {\
            int     _i, _j;\
            char    _cTmp;\
            for (_i = 0, _j = (Size) - 1; _i < _j; _i++, _j--)\
            {\
                _cTmp = ((char *)(ByteArray))[ _i ];\
                ((char *)(ByteArray))[ _i ] = ((char *)(ByteArray))[ _j ];\
                ((char *)(ByteArray))[ _j ] = _cTmp;\
            }\
        }

#define CONVERT_NUM( n )    REVERSE_BYTE_ARRAY( (&(n)), sizeof( n ))
#define CONVERT_NUM16( n )  ((void)(IS_DEFAULT_ENDIAN() ? (n)\
        : ((n) = ((((n) & 0x00FF) << 8) | (((n) & 0xFF00) >> 8)))))

/*	If the current machine is not default endian, re-arranges the bytes of the
	given 32-bit number. Does nothing if the current machine is default endian. */
#define CONVERT_NUM32( n )  ((void)(IS_DEFAULT_ENDIAN() ? (n)\
        : ((n) = ((((n) & 0x000000FF) << 24) | (((n) & 0x0000FF00) << 8)\
        | (((n) & 0xFF0000) >> 8) | (((n) & 0xFF000000) >> 24)))))



#endif