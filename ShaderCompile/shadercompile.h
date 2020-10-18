
//====== Copyright � 1996-2006, Valve Corporation, All rights reserved. =======//
//
// Purpose: Module prototypes.
//
// $NoKeywords: $
//
//=============================================================================//
#pragma once

#if defined(__linux__) || defined(__apple__)
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#endif

void DebugOut( const char* pMsg, ... );

#if defined(__linux__) || defined(__apple__)

using LONG = long;
using DWORD = unsigned int;
using BOOL = bool;
using errno_t = int;

#define WINAPI

/* Forceinline will just be expanded to inline */
#define __forceinline inline
#define FORCEINLINE inline

/* Same as on windows */
#define MAX_PATH 260

#define _unlink unlink
#define sprintf_s snprintf

static inline errno_t strcat_s(char* __restrict dest, size_t sz, const char* __restrict src)
{
	strncat(dest, src, sz);
	return errno;
}

static inline errno_t strcpy_s(char* __restrict dest, size_t sz, const char* __restrict src)
{
	strncpy(dest, src, sz);
	return errno;
}

static inline errno_t strcpy_s(char* __restrict dest, const char* __restrict src)
{
	strcpy(dest, src);
	return errno;
}

static inline errno_t _strupr_s(char* __restrict s, size_t sz)
{
	for(char* c = &s[0]; *c && sz >= 0; c++, sz--)
		*c = toupper(*c);
	return 0;
}

static inline errno_t _strupr_s(char* __restrict s)
{
	for(char* c = &s[0]; *c; c++)
		*c = toupper(*c);
	return 0;
}

static inline int _stricmp(const char* __restrict a, const char* __restrict b)
{
	return strcasecmp(a, b);
}


static inline void Sleep(DWORD dwMillis)
{
	usleep(dwMillis * 1000);
}

#endif