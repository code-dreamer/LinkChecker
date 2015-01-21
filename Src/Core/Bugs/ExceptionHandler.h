#pragma once

namespace Bugs {
class Exception;
enum class ErrorSeverity;
namespace ExceptionHandler {

void reportError(const Exception& e, bool enableGui = true);
void reportError(const std::exception& e, bool enableGui = true);
void reportError(const QString& message, ErrorSeverity severity, bool disableGui = true);

} // namespace ExceptionHandler 
} // namespace Bugs