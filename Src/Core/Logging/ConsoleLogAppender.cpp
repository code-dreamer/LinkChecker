#include "stdafx.h"
#include "Logging/ConsoleLogAppender.h"

void ConsoleLogAppender::write(const QString& message)
{
	std::wcout << message.toStdWString();
}
