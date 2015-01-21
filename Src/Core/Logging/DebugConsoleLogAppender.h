#pragma once

#include "LogAppender.h"

class DebugConsoleLogAppender : public LogAppender
{
public:
	DebugConsoleLogAppender() {};
	virtual void write(const QString& message) override;
};