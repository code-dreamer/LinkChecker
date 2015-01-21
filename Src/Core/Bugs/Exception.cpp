#include "stdafx.h"
#include "Exception.h"
#include "Logging/Logger.h"

namespace Bugs {

const ErrorSeverity kDefaultSeverity = ErrorSeverity::error;

void* NewImpl(size_t size)
{
	DCHECK(size > 0);
	return malloc(size);
}

void DeleteImpl(void* ptr)
{
	DCHECK_PTR(ptr);
	free(ptr);
}

QString formateThrowedSource(const char* functionName, const char* filename, int lineNumber)
{
	DCHECK_CSTRING(functionName);
	DCHECK_CSTRING(filename);
	DCHECK(lineNumber >= 0);

	using SolutionShared::Constants::kNewLine;

	QString info;
	QTextStream infoStream(&info);
	infoStream << "Source:" << kNewLine
		<< "Function: " << functionName << kNewLine
		<< "File: " << filename << kNewLine
		<< "Line: " << lineNumber;

	return info;
}

void writeExceptionToLog(const Bugs::Exception& e)
{
	using SolutionShared::Constants::kNewLine;

	const ErrorSeverity exceptionSeverity = e.severity();
	const QString exceptionDump = e.toString();
	if (exceptionSeverity == ErrorSeverity::warning) {
		LOG_WARNING() << "Exception throwed:" << kNewLine << exceptionDump;
	}
	else if (exceptionSeverity == ErrorSeverity::error) {
		LOG_ERROR() << "Exception throwed:" << kNewLine << exceptionDump;
	}
	else if (exceptionSeverity == ErrorSeverity::fatal) {
		LOG_FATAL() << "Exception throwed:" << kNewLine << exceptionDump;
	}
}

QString severityToStr(ErrorSeverity severity)
{
	switch (severity) {
	case ErrorSeverity::warning:
		return _S("Warning");
	case ErrorSeverity::error:
		return _S("Error");
	case ErrorSeverity::fatal:
		return _S("Fatal");
	}

	FAIL();
	return QString();
}

Exception::Exception(const QString& message)
	: message_(message)
	, inner_(nullptr)
	, severity_(kDefaultSeverity)
{
	DCHECK_QSTRING(message);
}

Exception::Exception(const QString& message, const Exception& inner)
	: message_(message)
	, inner_(inner.clone())
	, severity_(kDefaultSeverity)
{
	DCHECK_QSTRING(message);
}

Exception::Exception(const Exception& other)
	: message_(other.message())
	, additionalValues_(other.additionalValues_)
	, throwedSource_(other.throwedSource_)
	, inner_(other.inner_ == nullptr ? 0 : other.inner_->clone() )
	, severity_(kDefaultSeverity)
{
}

Exception::~Exception()
{
	if (inner_ != nullptr) {
		delete inner_;
		inner_ = nullptr;
	}
}

void* Exception::operator new(size_t size)
{
	return NewImpl(size);
}
void* Exception::operator new[](size_t size) 
{  
	return NewImpl(size);
}

void Exception::operator delete(void* ptr) {  
	DeleteImpl(ptr);
}

void Exception::operator delete[](void* ptr) {
	DeleteImpl(ptr);
}

QString Exception::toString() const
{
	QString dump;
	QTextStream dumpStream(&dump);

	using SolutionShared::Constants::kNewLine;

	dumpStream 
		<< "Exception: " << className() << kNewLine
		<< "Severity: " << severityToStr(severity_);

	QString errorMessage = message();
	if ( !errorMessage.isEmpty() ) {
		dumpStream 
			<< kNewLine << "Error message: " << errorMessage << kNewLine;
	}

	if ( !throwedSource_.isEmpty() ) {
		dumpStream << throwedSource_ << kNewLine;
	}

	QString diagnosticInformation = additionalProperties();
	if ( !diagnosticInformation.isEmpty() ) {
		dumpStream 
			<< kNewLine << "Additional properties:" << kNewLine	<< additionalProperties();
	}

	if (inner_ != nullptr) {
		dumpStream 
			<< kNewLine << "Inner exception dump:" << kNewLine << inner_->toString();
	}

	return dump;
}

QString Exception::className() const
{
	return QString::fromLatin1( typeid(*this).name() );
}

QString Exception::additionalProperties() const
{
	using SolutionShared::Constants::kNewLine;

	QString info;
	QTextStream infoStream(&info);

	foreach(const ExceptionValue& value, additionalValues_) {		
		infoStream << "[" << value.first << "]";
		infoStream << " = ";
		infoStream << "[" << value.second.toString() << "]";
		infoStream << kNewLine;
	}

	return info;
}

void Exception::setSeverity(ErrorSeverity severity)
{
	severity_ = severity;
}

ErrorSeverity Exception::severity() const
{
	return severity_;
}

void Exception::setThrowedSource(const QString& info)
{
	DCHECK_QSTRING(info);

	throwedSource_ = info;
}

void Exception::addAdditionalValue(const ExceptionValue& value)
{
	additionalValues_.push_back(value);
}

void Exception::setMessage(const QString& message)
{
	DCHECK_QSTRING(message);
	message_ = message;
}

QString Exception::message() const
{
	return message_;
}

/*
Exception* Exception::clone() const
{
	return new Exception(*this);
}*/

/*
void Exception::rethrow() const
{
	throw *this;
}*/

ExceptionValue makeExProp(const QByteArray& name, const QVariant& value)
{
	DCHECK_QSTRING(name);
	DCHECK(!value.isNull());

	return qMakePair<QString, QVariant>(QLatin1String(name.constData()), value);
}

} // namespace Bugs