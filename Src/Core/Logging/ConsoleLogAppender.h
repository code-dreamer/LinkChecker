#pragma once

#include "LogAppender.h"

class ConsoleLogAppender : public LogAppender
{
public:
	ConsoleLogAppender() {};
	virtual void write(const QString& message) override;
};
