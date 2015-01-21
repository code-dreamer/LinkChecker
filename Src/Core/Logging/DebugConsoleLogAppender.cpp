#include "stdafx.h"
#include "DebugConsoleLogAppender.h"

void DebugConsoleLogAppender::write(const QString& message)
{
	const QTextCodec* codecForCurrLocale = QTextCodec::codecForLocale();
	QByteArray messageBa = codecForCurrLocale->fromUnicode(message);

	std::string logEntry(messageBa.constData(), messageBa.length());

	OutputDebugStringA(logEntry.c_str());
}
