#pragma once

#include "LogAppender.h"
#include "LogLevel.h"
#include "LogStream.h"
#include "Tools/Singleton.h"

// LOG
//
// Debug messages. Can be useful for app debugging
//#define LOG_DEBUG()		
	//LogStream(plogger, LogLevel::debugLevel, __FUNCTION__, __FILE__, __LINE__)

/*LOG_DEBUG( Logging::appLogger() )

// Information messages. Can be useful for signaling about important events in application. 
#define LOG_INFO()		LOG_INFO( Logging::appLogger() )

// Can be useful if some strange, but non-fatal has happen
#define LOG_WARNING()	LOG_WARNING( Logging::appLogger() )

// Error (not critical). Application may remain unstable but not crashing.
#define LOG_ERROR()		LOG_ERROR( Logging::appLogger() )

// Critical error. Some application components may not work correctly.
#define LOG_CRITICAL()	LOG_CRITICAL( Logging::appLogger() )

// Fatal, unrecoverable error. Application in crash state and can't be recovered (unhandled exceptions handlers and etc).
#define LOG_FATAL()		LOG_FATAL( Logging::appLogger() )


class Logger
{
	Q_DISABLE_COPY(Logger)

	//friend Logger* createLogger(const QString& name, const QString& filename);
	//friend class Impl::LogStream;
	//friend class LogFuncHelper;
	// 
public:
	~Logger();

	void setLevel(LogLevel logLevel);
	void handleQtLog(bool handle);
	void writeMessage(const QString& message, LogLevel logLevel, const char* func, const char* fileName, int line);

//private:
	//bool needLogging(LogLevel logLevel);
};
*/


class Logger : public Singleton<Logger> 
{
	friend class Singleton<Logger>;
private:
	Logger();
	virtual ~Logger();

public:
	void setLevel(LogLevel logLevel);
	LogLevel level() const;
	void addAppender(LogAppender* takedAppender);
	void writeMessage(const QString& message, LogLevel logLevel, const char* funcName, const char* fileName, int line);

private:
	void replaceQtLogHandler(bool replace);

private:
	LogLevel currLogLevel_;
	QList<LogAppender*> appenders_;
};


// Debug messages. Can be useful for app debugging
#define LOG_DEBUG()		\
	LogStream(Logger::instance(), LogLevel::debug, __FUNCTION__, __FILE__, __LINE__)

// Information messages. Can be useful for signaling about important events in application.
#define LOG_INFO()		\
	LogStream(Logger::instance(), LogLevel::info, __FUNCTION__, __FILE__, __LINE__)

// Can be useful if some strange, but non-fatal has happen
#define LOG_WARNING()	\
	LogStream(Logger::instance(), LogLevel::warning, __FUNCTION__, __FILE__, __LINE__)

// Error (not critical). Application may remain unstable but not crashing.
#define LOG_ERROR()		\
	LogStream(Logger::instance(), LogLevel::error, __FUNCTION__, __FILE__, __LINE__)

// Critical error. Some application components may not work correctly.
#define LOG_CRITICAL()	\
	LogStream(Logger::instance(), LogLevel::critical, __FUNCTION__, __FILE__, __LINE__)

// Fatal, unrecoverable error. Application in crash state and can't be recovered (unhandled exceptions handlers and etc).
#define LOG_FATAL()	\
	LogStream(Logger::instance(), LogLevel::fatal, __FUNCTION__, __FILE__, __LINE__)