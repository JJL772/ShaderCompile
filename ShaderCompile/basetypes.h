#ifndef BASETYPES_H
#define BASETYPES_H

#pragma once

#include <cstdint>
#ifdef _DEBUG
	#include <cassert>
#endif

using byte = std::uint8_t;

#ifdef _DEBUG
	#define Assert assert
#else
#ifdef _WIN32
	#define Assert __noop
#else
	#define Assert(x)
#endif
#endif

#endif // BASETYPES_H