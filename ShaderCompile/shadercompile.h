
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

static inline void Sleep(DWORD dwMillis)
{
	usleep(dwMillis * 1000);
}

#endif