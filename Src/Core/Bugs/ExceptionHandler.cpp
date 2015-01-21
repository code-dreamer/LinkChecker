#include "stdafx.h"
#include "Bugs/ExceptionHandler.h"
#include "Bugs/Exception.h"
#include "Logging/Logger.h"
#include "Gui/ExceptionInfoWindow.h"

namespace Bugs {
namespace ExceptionHandler {

void showErrorToUser(const QString& message, const QString& errorProps = QString(), ErrorSeverity severity = ErrorSeverity::error)
{
	Q_UNUSED(severity);

	if (QCoreApplication::startingUp()) {
		const QString msgTitle = QCoreApplication::translate("ExceptionHandler", "Error");

		auto msgBoxFlags = MB_OK;

		switch (severity) {
		case ErrorSeverity::warning:
			msgBoxFlags |= MB_ICONWARNING;
			break;
		case ErrorSeverity::error:
		case ErrorSeverity::fatal:
			msgBoxFlags |= MB_ICONERROR;
			break;
		default:
			FAIL();
		}

		MessageBox(nullptr, message.toStdWString().c_str(), msgTitle.toStdWString().c_str(), msgBoxFlags);
	}
	else {
		ExceptionInfoWindow wnd(QApplication::activeWindow());
		wnd.setError(message);
		if ( !errorProps.isEmpty() ) {
			wnd.setAdditionalInfo(errorProps);
		}
		wnd.exec();
	}
}

void reportError(const Exception& e, bool enableGui)
{
	using SolutionShared::Constants::kNewLine;

	const ErrorSeverity exceptionSeverity = e.severity();
	const QString exceptionDump = e.toString();
	if (exceptionSeverity == ErrorSeverity::warning) {
		LOG_WARNING() << "Exception catched:" << kNewLine << exceptionDump;
	}
	else if (exceptionSeverity == ErrorSeverity::error) {
		LOG_ERROR() << "Exception catched:" << kNewLine << exceptionDump;
	}
	else if (exceptionSeverity == ErrorSeverity::fatal) {
		LOG_FATAL() << "Exception catched:" << kNewLine << exceptionDump;
	}

	if (enableGui && exceptionSeverity != ErrorSeverity::warning) {
		showErrorToUser(e.message(), e.additionalProperties(), exceptionSeverity);
	}
}

void reportError(const std::exception& e, bool enableGui)
{
	const char* errorMessage = e.what();
	LOG_ERROR() << errorMessage;
	
	if (enableGui) {
		showErrorToUser(QString::fromLatin1(errorMessage));
	}
}

void reportError(const QString& message, ErrorSeverity severity, bool enableGui)
{
	DCHECK_QSTRING(message);

	switch (severity) {
	case ErrorSeverity::warning:
		LOG_WARNING() << message;
		break;
	case ErrorSeverity::error:
		LOG_ERROR() << message;
		break;
	case ErrorSeverity::fatal:
		LOG_FATAL() << message;
		break;
	default:
		FAIL();
	}

	if (enableGui) {
		showErrorToUser(message);
	}
}

} // namespace ExceptionHandler
} // namespace Bugs