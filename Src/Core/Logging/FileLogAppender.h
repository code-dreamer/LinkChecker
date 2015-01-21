#pragma once

#include "LogAppender.h"

class FileLogAppender : public LogAppender
{
public:
	FileLogAppender(const QString& filePath);
	virtual ~FileLogAppender() {};
	virtual void write(const QString& message) override;

private:
	QFile file_;
	QTextStream outputStream_;
};
