#include "stdafx.h"
#include "Checks.h"
#include "Debugging.h"
#include "Logging/Logger.h"

namespace Bugs {

void reportRuntimeFailure(const char* expr, const char* funcName, const char* file, int line)
{
	Q_UNUSED(expr);
	Q_UNUSED(funcName);
	Q_UNUSED(file);
	Q_UNUSED(line);

#ifdef NDEBUG
	LOG_FATAL() << expr << funcName << file << line;
	Debugging::abortApp();
#endif // NDEBUG
}

} // namespace Checks