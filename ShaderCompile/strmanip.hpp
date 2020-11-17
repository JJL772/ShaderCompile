#pragma once

#include <iostream>
#include <iomanip>

#ifndef _WIN32
#define __forceinline inline
#endif

static std::string PrettyPrintNumber( uint64_t k )
{
	char chCompileString[50] = { 0 };
	char* pchPrint = chCompileString + sizeof( chCompileString ) - 3;
	for ( uint64_t j = 0; k > 0; k /= 10, ++j )
	{
		( j && !( j % 3 ) ) ? ( *pchPrint-- = ',' ) : 0;
		*pchPrint-- = '0' + char( k % 10 );
	}
	*++pchPrint ? 0 : *pchPrint = 0;
	return pchPrint;
}

struct FormatTime
{
	int64_t m_time;
	FormatTime() = delete;
	explicit FormatTime(int64_t time) :
		m_time(time)
	{
	}

	friend std::ostream& operator<<(std::ostream& o, const FormatTime& t)
	{
		int64_t nMinutes = t.m_time / 60;
		const int64_t nSeconds = t.m_time - nMinutes * 60;
		const int64_t nHours = nMinutes / 60;
		nMinutes -= nHours * 60;

		constexpr const char* const extra[2] = { "", "s" };

		auto& str = dynamic_cast<std::ostream&>( o );
		if ( nHours > 0 )
			str << clr::green << nHours << clr::reset << " hour" << extra[nHours != 1] << ", " << clr::green << nMinutes << clr::reset << " minute" << extra[nMinutes != 1] << ", " << clr::green << nSeconds << clr::reset << " second" << extra[nSeconds != 1];
		else if ( nMinutes > 0 )
			str << clr::green << nMinutes << clr::reset << " minute" << extra[nMinutes != 1] << ", " << clr::green << nSeconds << clr::reset << " second" << extra[nSeconds != 1];
		else
			str << clr::green << nSeconds << clr::reset << " second" << extra[nSeconds != 1];
		return o;
	}
};

struct FormatTimeShort
{
	int64_t m_time;
	FormatTimeShort() = delete;
	explicit FormatTimeShort(int64_t time) :
		m_time(time)
	{
	}

	friend std::ostream& operator<<(std::ostream& o, const FormatTimeShort& t)
	{
		int64_t nMinutes = t.m_time / 60;
		const int64_t nSeconds = t.m_time - nMinutes * 60;
		const int64_t nHours = nMinutes / 60;
		nMinutes -= nHours * 60;

		constexpr const char* const extra[2] = { "", "s" };

		auto& str = dynamic_cast<std::ostream&>( o );
		if ( nHours > 0 )
			str << clr::green << nHours << clr::reset << ":" << clr::green << nMinutes << clr::reset << ":" << clr::green << nSeconds << clr::reset;
		else if ( nMinutes > 0 )
			str << clr::green << nMinutes << clr::reset << ":" << clr::green << nSeconds << clr::reset;
		else
			str << clr::green << nSeconds << clr::reset << " second" << extra[nSeconds != 1];
		return o;
	}
};


static __forceinline bool PATHSEPARATOR( char c )
{
	return c == '\\' || c == '/';
}

static const char* V_GetFileExtension( const char* path )
{
	const char* src = path + ( strlen( path ) - 1 );

	while ( src != path && *( src - 1 ) != '.' )
		src--;

	if ( src == path || PATHSEPARATOR( *src ) )
		return nullptr; // no extension

	return src;
}

static __forceinline bool V_IsAbsolutePath( const char* pStr )
{
	return pStr[0] && pStr[1] == ':' || pStr[0] == '/' || pStr[0] == '\\';
}

static void V_StripFilename( char* path )
{
	int length = static_cast<int>( strlen( path ) ) - 1;
	if ( length <= 0 )
		return;

	while ( length > 0 && !PATHSEPARATOR( path[length] ) )
		length--;

	path[length] = 0;
}

static void V_FixSlashes( char* pname, char separator = '\\' )
{
	while ( *pname )
	{
		if ( *pname == '/' || *pname == '\\' )
			*pname = separator;
		pname++;
	}
}

static void V_StrTrim( char* pStr )
{
	char* pSource = pStr;
	char* pDest = pStr;

	// skip white space at the beginning
	while ( *pSource != 0 && isspace( *pSource ) )
		pSource++;

	// copy everything else
	char* pLastWhiteBlock = nullptr;
	while ( *pSource != 0 )
	{
		*pDest = *pSource++;
		if ( isspace( *pDest ) )
		{
			if ( pLastWhiteBlock == nullptr )
				pLastWhiteBlock = pDest;
		}
		else
			pLastWhiteBlock = nullptr;
		pDest++;
	}
	*pDest = 0;

	// did we end in a whitespace block?
	if ( pLastWhiteBlock != nullptr )
		// yep; shorten the string
		*pLastWhiteBlock = 0;
}