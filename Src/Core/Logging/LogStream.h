#pragma once

class Logger;
enum class LogLevel;

class LogStream
{
	Q_DISABLE_COPY(LogStream)

public:
	LogStream(Logger* logger, LogLevel logLevel, const char* func, const char* fileName, int line);
	~LogStream();

	template<typename T>
	inline LogStream& operator<<(const T& val)
	{
		if (enabled_) {
			stream_ << val;
		}

		return *this;
	}

	void handlQtLog(bool handle);

private:
	Logger* logger_;
	char* fileName_; 
	char* func_; 
	int line_;
	QString buffer_;
	QDebug stream_;
	LogLevel logLevel_;
	bool enabled_;
};