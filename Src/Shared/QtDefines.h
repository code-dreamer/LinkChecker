#pragma once

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
