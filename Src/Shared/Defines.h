#pragma once

// Solution specific defines
//
#ifndef _CRT_SECURE_NO_DEPRECATE
#	define _CRT_SECURE_NO_DEPRECATE	1
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#	define _CRT_SECURE_NO_WARNINGS	1
#endif

#ifndef _CRT_NONSTDC_NO_WARNINGS
#	define _CRT_NONSTDC_NO_WARNINGS	1
#endif

#ifndef NDEBUG
#	ifndef DEBUG
#		define DEBUG
#	endif
#endif

// Useful tools
//
#if defined(DISABLE_ASSIGN)
#	pragma message ("DISABLE_ASSIGN already defined.")
#else
#	define DISABLE_ASSIGN(ClassName)					\
		private:										\
		ClassName &operator=(const ClassName &);		\
		ClassName &operator=(const ClassName &&);
#endif


#define NOOP ((void)0)

/*
#include <cassert>
#include <QtCore/qglobal.h>

#if defined(ASSERT)
#	pragma message ("ASSERT already defined.")
#else
#	define ASSERT(condition) assert(condition)
#endif

#if defined(VERIFY_FATAL)
#	pragma message ("VERIFY_FATAL already defined.")
#else
#	define VERIFY_FATAL(condition)			\
	__pragma(warning(push))					\
	__pragma(warning(disable : 4127))		\
	do {									\
		if (!condition) {					\
			_wassert(_CRT_WIDE(#condition), _CRT_WIDE(__FILE__), __LINE__);		\
			abort();						\
		}									\
	} while (0)								\
	__pragma(warning(pop))
#endif


#if defined(ASSERT_MSG)
#	pragma message ("ASSERT_MSG already defined.")
#else
#	if defined(DEBUG)
#		define ASSERT_MSG(condition, message) \
	(void)( (!!(condition)) || (_wassert(_CRT_WIDE(#condition) _CRT_WIDE("\nMessage: ") _CRT_WIDE(#message), _CRT_WIDE(__FILE__), __LINE__), 0) )
#	else
#		define ASSERT_MSG(condition, message) ((void)0)
#	endif
#endif

#if defined(CHECK_PTR)
#	pragma message ("CHECK_PTR already defined.")
#else
#	define CHECK_PTR(pointer)							\
	__pragma(warning(push))								\
	__pragma(warning(disable : 4127))					\
	ASSERT_MSG(pointer != nullptr, "Invalid pointer");	\
	Q_CHECK_PTR(pointer) \
	__pragma(warning(pop))											
#endif


#if defined(CHECK_QSTRING)
#	pragma message ("CHECK_QSTRING already defined.")
#else
#	define CHECK_QSTRING(qstring)							\
	ASSERT( !qstring.isEmpty() )
#endif


#if defined(CHECK_STDSTRING)
#	pragma message ("CHECK_STDSTRING already defined.")
#else
#	define CHECK_STDSTRING(stdstring)						\
	ASSERT( !stdstring.empty() )
#endif


#if defined(CHECK_CSTRING)
#	pragma message ("CHECK_CSTRING already defined.")
#else
#	define CHECK_CSTRING(cstring)							\
	CHECK_PTR(cstring);	\
	ASSERT(strlen(cstring) > 0);
#endif


#if defined(CHECK_CWSTRING)
#	pragma message ("CHECK_CWSTRING already defined.")
#else
#	define CHECK_CWSTRING(cwstring)							\
	CHECK_PTR(cwstring);									\
	ASSERT(wcslen(cwstring) > 0);
#endif


#ifdef _S
#	error "_S already defined"
#else
#	define _S(string)	QLatin1String(string)
#endif

#ifdef _C
#	error "_C already defined"
#else
#	define _C(symbol)	QLatin1Char(symbol)
#endif

#ifdef NOINIT_VTABLE
#	error "NOINIT_VTABLE already defined"
#else
#	define NOINIT_VTABLE __declspec(novtable)
#endif*/

/*
#if defined(ASSERT_ACTION)
#	pragma message ("ASSERT_ACTION already defined.")
#else
#	define ASSERT_ACTION(condition, action)							\
	__pragma(warning(push))											\
	__pragma(warning(disable : 4127))								\
	if (!condition) { ASSERT(condition); action; } ((void)0)		\
	__pragma(warning(pop))
#endif*/