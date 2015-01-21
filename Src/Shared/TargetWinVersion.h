#pragma once

// The following macros define the minimum required platform.  The minimum required platform
// is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run 
// your application.  The macros work by enabling all features available on platform versions up to and 
// including the version specified.

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

// Specifies that the minimum required platform is Windows XP.
// Change this to the appropriate value to target other versions of Windows.
#define WIN_VERSION _WIN32_WINNT_WINXP /*0x0501*/

#include <SDKDDKVer.h>

#ifndef _WIN32_WINNT
#	define _WIN32_WINNT WIN_VERSION
#endif

#ifndef WINVER
#	define WINVER WIN_VERSION
#endif

#ifndef _WIN32_WINDOWS
#	define _WIN32_WINDOWS WIN_VERSION
#endif