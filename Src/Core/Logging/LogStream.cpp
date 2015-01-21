#include "stdafx.h"
#include "LogStream.h"
#include "Logger.h"

LogStream::LogStream(Logger* logger, LogLevel logLevel, const char* func, const char* fileName, int line)
	:logger_(logger)
	, stream_(&buffer_)
	, logLevel_(logLevel)
	, fileName_(nullptr)
	, line_(line)
	, enabled_(false)
{
	//assert(logger != nullptr);
	if (logger != nullptr) {
		enabled_ = (logLevel >= logger->level());
	}

	if (func != nullptr) {
		func_ = new char[qstrlen(func) + 1];
		qstrcpy(func_, func);
	}

	if (fileName != nullptr) {
		fileName_ = new char[qstrlen(fileName) + 1];
		qstrcpy(fileName_, fileName);
	}
}

LogStream::~LogStream()
{
	if (enabled_) {
		logger_->writeMessage(buffer_, logLevel_, func_, fileName_, line_);
	}

	if (fileName_ != nullptr) {
		delete[] fileName_;
		fileName_ = nullptr;
	}

	if (func_ != nullptr) {
		delete[] func_;
		func_ = nullptr;
	}
}
