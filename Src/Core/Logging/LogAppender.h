#pragma once

class LogAppender
{
public:
	virtual ~LogAppender(){}
	virtual void write(const QString& message) = 0;
};