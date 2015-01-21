#include "stdafx.h"
#include "Logger.h"

QtMessageHandler sPrevQtLogHandler = nullptr;

void qtMessageHandler(QtMsgType type, const QMessageLogContext& messageContext, const QString& message)
{
	Logger* logger = Logger::instance();
	
	switch (type) {
	case QtDebugMsg:
		logger->writeMessage(message, LogLevel::debug, messageContext.function, messageContext.file, messageContext.line);
		break;
	case QtWarningMsg:
		logger->writeMessage(message, LogLevel::warning, messageContext.function, messageContext.file, messageContext.line);
		break;
	case QtCriticalMsg:
		logger->writeMessage(message, LogLevel::critical, messageContext.function, messageContext.file, messageContext.line);
		break;
	case QtFatalMsg:
		logger->writeMessage(message, LogLevel::fatal, messageContext.function, messageContext.file, messageContext.line);
		break;
	default:
		Q_ASSERT(false);
	}
}

Logger::Logger()
	: currLogLevel_(LogLevel::warning)
{
	replaceQtLogHandler(true);
}

Logger::~Logger()
{
	replaceQtLogHandler(false);
	Q_FOREACH(LogAppender* appender, appenders_) {
		delete appender;
	}
	appenders_.clear();
}

void Logger::setLevel(LogLevel logLevel)
{
	currLogLevel_ = logLevel;
}

LogLevel Logger::level() const
{
	return currLogLevel_;
}

void Logger::writeMessage(const QString& message, LogLevel logLevel, const char* funcName, const char* fileName, int line)
{
	QString formattedMessage;
	QTextStream out(&formattedMessage);
	out << QDateTime::currentDateTime().toString(QLatin1String("dd.MM.yyyy hh:mm:ss.zzz"))
		<< QLatin1String(" <") << levelToStr(logLevel) << QLatin1String(">") 
		<< endl << message << endl
		<< funcName << QLatin1String(", ") << fileName << QLatin1String(":") << line << endl;

	Q_FOREACH(LogAppender* appender, appenders_) {
		appender->write(formattedMessage);
	}
}

void Logger::replaceQtLogHandler(bool replace)
{
	if (replace) {
		sPrevQtLogHandler = qInstallMessageHandler(qtMessageHandler);
	}
	else {
		qInstallMessageHandler(sPrevQtLogHandler);
		sPrevQtLogHandler = nullptr;
	}
}

void Logger::addAppender(LogAppender* takedAppender)
{
	appenders_ << takedAppender;
}