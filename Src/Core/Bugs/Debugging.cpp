#include "stdafx.h"
#include "Debugging.h"

// NOTE: In this module, we use the C library functions (fputs) for,
// output since, at the time we're called, the C++ iostream objects std::cout, etc.
// might not have been initialized yet.

namespace Debugging {

std::string formateReport(const char* expression, const char* functionName, const char* errorMessage)
{
	assert(expression != nullptr && qstrlen(expression) > 0);
	assert(functionName != nullptr && qstrlen(functionName) > 0);

	std::stringstream customMessage;
	if (errorMessage != nullptr) {
		customMessage << "Error message: '" << errorMessage << "'" << std::endl;
	}

	std::stringstream messageStream;
	messageStream << "ASSERT: '" << expression << "'" << " in " << functionName;
	if (errorMessage != nullptr) {
		messageStream << std::endl << errorMessage;
	}

	return messageStream.str();
}

void abortApp()
{
	raise(SIGABRT);
	_exit(3);
}

void writeMessage(const char* msg)
{
	assert(msg != nullptr && qstrlen(msg) > 0);

	std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
	std::fputs(msg, stderr);
	std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);

	OutputDebugStringA("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	OutputDebugStringA(msg);
	OutputDebugStringA("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n");
}

void debugBreak()
{
	_CrtDbgBreak();	
}

} // namespace Debugging
