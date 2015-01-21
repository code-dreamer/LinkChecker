#pragma once

#ifndef CORE_EXPORT
	#if defined(CORE_STATIC_LIB)
		#define CORE_EXPORT		// build as a static library
	#else
		#ifdef CORE_LIB
			#define CORE_EXPORT	__declspec(dllexport)
		#else
			#define CORE_EXPORT	__declspec(dllimport)
		#endif
	#endif
#endif
