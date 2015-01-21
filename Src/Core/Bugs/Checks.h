#pragma once

#include "Debugging.h"

namespace Bugs {
void reportRuntimeFailure(const char* expr, const char* funcName, const char* file, int line);
} // namespace Bugs


#define DEBUG_BREAK(expression, message)															\
	if (!(expression)) {																			\
		const std::string reportMsg = Debugging::formateReport(#expression, __FUNCSIG__, message);	\
		Debugging::writeMessage(reportMsg.c_str());													\
		_CrtDbgBreak();																				\
	}																								

// CHECK_IMPL
//
#define CHECK_IMPL(expression, message)		{		\
	__pragma(warning(push))							\
	__pragma(warning(disable : 4127))				\
	DEBUG_BREAK(expression, message)				\
	if (!(expression)) ::Bugs::reportRuntimeFailure(#expression, __FUNCSIG__, __FILE__, __LINE__); \
	__pragma(warning(pop))							\
}

#ifdef NDEBUG
#	define DCHECK(expression)			NOOP
#	define CHECK(expression)			CHECK_IMPL(expression, nullptr)
#else
#	define DCHECK(expression)			CHECK_IMPL(expression, nullptr)
#	define CHECK(expression)			CHECK_IMPL(expression, nullptr)
#endif

#ifdef NDEBUG
#	define DCHECK_MSG(expression, msg)	NOOP
#	define CHECK_MSG(expression, msg)	CHECK_IMPL(expression, msg)
#else
#	define DCHECK_MSG(expression, msg)	CHECK_IMPL(expression, msg)
#	define CHECK_MSG(expression, msg)	CHECK_IMPL(expression, msg)
#endif

// NOT_REACHABLE
//
#define NOT_REACHABLE_IMPL()		{			\
	__pragma(warning(push))						\
	__pragma(warning(disable : 4127))			\
	DCHECK_MSG(false, "Not reachable place!");	\
	__pragma(warning(pop))						\
}

#ifdef NDEBUG
#	define FAIL()	NOOP
#	define FAIL()	NOT_REACHABLE_IMPL();
#else
#	define FAIL()	NOT_REACHABLE_IMPL();
#	define FAIL()	NOT_REACHABLE_IMPL();
#endif
/////////////////////////////////////////

// CHECK_PTR
//
#define CHECK_PTR_IMPL(ptr)		{			\
	DCHECK_MSG(ptr != nullptr, "Invalid pointer '" #ptr "'");	\
}

#ifdef NDEBUG
#	define DCHECK_PTR(ptr)	NOOP
#	define CHECK_PTR(ptr)	CHECK_PTR_IMPL(ptr)
#else
#	define DCHECK_PTR(ptr)	CHECK_PTR_IMPL(ptr)
#	define CHECK_PTR(ptr)	CHECK_PTR_IMPL(ptr)
#endif
/////////////////////////////////////////


// CHECK_QSTRING
//
#define CHECK_QSTRING_IMPL(qstring)		{			\
	DCHECK_MSG(!qstring.isEmpty(), "Invalid Qt string '" #qstring "'"); \
}

#ifdef NDEBUG
#	define DCHECK_QSTRING(qstring)	NOOP
#	define CHECK_QSTRING(qstring)	CHECK_QSTRING_IMPL(qstring);
#else
#	define DCHECK_QSTRING(qstring)	CHECK_QSTRING_IMPL(qstring);
#	define CHECK_QSTRING(qstring)	CHECK_QSTRING_IMPL(qstring);
#endif
/////////////////////////////////////////


// CHECK_CSTRING
//
#define CHECK_CSTRING_IMPL(string) {										\
	DCHECK_MSG((string != nullptr && strlen(string) > 0), "Invalid char string '" #string "'");	\
}

#ifdef NDEBUG
#	define DCHECK_CSTRING(wstring)	NOOP
#	define CHECK_CSTRING(wstring)	CHECK_CSTRING_IMPL(wstring)
#else
#	define DCHECK_CSTRING(wstring)	CHECK_CSTRING_IMPL(wstring)
#	define CHECK_CSTRING(wstring)	CHECK_CSTRING_IMPL(wstring)
#endif
/////////////////////////////////////////


// CHECK_CWSTRING
//
#define CHECK_CWSTRING_IMPL(wstring) {										\
	DCHECK_MSG((wstring != nullptr && wcslen(wstring) > 0), "Invalid wchar_t string '" #wstring "'");	\
}

#ifdef NDEBUG
#	define DCHECK_CWSTRING(wstring)	NOOP
#	define CHECK_CWSTRING(wstring)	CHECK_CWSTRING_IMPL(wstring)
#else
#	define DCHECK_CWSTRING(wstring)	CHECK_CWSTRING_IMPL(wstring)
#	define CHECK_CWSTRING(wstring)	CHECK_CWSTRING_IMPL(wstring)
#endif
/////////////////////////////////////////







/*
#define DEBUG_BREAK(expression, message)																					
	__pragma(warning(push))					
	__pragma(warning(disable : 4127))		
	if (!(expression)) {																								
	const std::string reportMsg = Debugging::formateReport(#expression, __FUNCSIG__, message);	
	const int prevReportMode = _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);										
	const int reportResult = _CrtDbgReport(_CRT_ERROR, __FILE__, __LINE__, nullptr, reportMsg.c_str());		
	_CrtSetReportMode(_CRT_ERROR, prevReportMode);																		
	if (reportResult == 1)																								
	_CrtDbgBreak();																									
	}																														
	__pragma(warning(pop))*/