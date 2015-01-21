#pragma once

// Useful macros for converting numbers into chars.
//
#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

///////////////////////////// Application info //////////////////////////////////

// Major release version of the program, increment only when major changes are made.
//
#ifndef APP_VERSION_MAJOR
	#define APP_VERSION_MAJOR 0
#endif

// Minor release version of the program, increment if any new features are added.
//
#ifndef APP_VERSION_MINOR
	#define APP_VERSION_MINOR 1
#endif

// Any bug fix updates, no new features.
//
#ifndef APP_VERSION_BUILD
	#define APP_VERSION_BUILD 1
#endif

#ifndef APP_RELEASE_TYPE
	#define APP_RELEASE_TYPE "Alpha"
#endif

#ifndef BUILD_YEAR
	#define BUILD_YEAR 2013
#endif

#ifndef COMPANY_NAME
	#define COMPANY_NAME "Some Company"
#endif

#ifndef APP_NAME
	#define APP_NAME "Link Checker"
#endif

#ifndef APP_STR_ID
	#define APP_STR_ID "LinkChecker"
#endif

#ifndef APP_LONG_NAME
	#define APP_LONG_NAME COMPANY_NAME APP_NAME
#endif

////////////////////////////////////////////////////////////////////////////////


// Construct Application version
//
#define APP_VERSION			STRINGIFY(APP_VERSION_MAJOR APP_VERSION_MINOR APP_VERSION_BUILD)
#define APP_FULL_VERSION	STRINGIFY(APP_VERSION_MAJOR APP_VERSION_MINOR APP_VERSION_BUILD APP_RELEASE_TYPE)


namespace AppGlobal {
namespace AppInfo {

const char MajorVersionStr[] = STRINGIFY(APP_VERSION_MAJOR);
const int MajorVersion = APP_VERSION_MAJOR;
const char MinorVersionStr[] = STRINGIFY(APP_VERSION_MINOR);
const int MinorVersion = APP_VERSION_MINOR;
const char BuildVersionStr[] = STRINGIFY(APP_VERSION_BUILD);
const int BuildVersion = APP_VERSION_BUILD;
const char ReleaseType[] = APP_RELEASE_TYPE;
const char Version[] = APP_VERSION;
const char FullVersion[] = APP_FULL_VERSION;

const char StrId[] = APP_STR_ID;
const char Name[] = APP_NAME;
const char LongName[] = APP_LONG_NAME;
const char FullName[] = APP_LONG_NAME " " APP_FULL_VERSION;
const char CompanynName[] = COMPANY_NAME;

const char HomeUrl[] = "http://www.ya.ru/";
//const char ContactsUrl[] = "http://www.ya.ru/";

const char Copyright[] = "© " STRINGIFY(BUILD_YEAR) " " COMPANY_NAME ". All rights reserved.";

} // namespace AppInfo
} // namespace AppGlobal


#undef STRINGIFY_INTERNAL
#undef STRINGIFY
#undef APP_VERSION_MAJOR
#undef APP_VERSION_MINOR
#undef APP_VERSION_BUILD
#undef APP_RELEASE_TYPE
#undef BUILD_YEAR
#undef COMPANY_NAME
#undef APP_NAME
