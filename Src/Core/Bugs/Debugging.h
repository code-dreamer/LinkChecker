#pragma once

namespace Debugging {

std::string formateReport(const char* expression, const char* functionName, const char* errorMessage);

// Writes a message to the debugger log, if available, otherwise to
// standard error output.
void writeMessage(const char* msg);
void abortApp();
void debugBreak();

} // namespace Debugging

