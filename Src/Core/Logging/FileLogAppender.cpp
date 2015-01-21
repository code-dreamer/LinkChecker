#include "stdafx.h"
#include "FileLogAppender.h"

FileLogAppender::FileLogAppender(const QString& filePath)
	: LogAppender()
{
	Q_ASSERT(!filePath.isEmpty());

	file_.setFileName(filePath);

	QFileInfo fileInfo(filePath);
	QDir dir = fileInfo.absoluteDir();
	QString dirPath = dir.path();
	if (!dir.exists()) {
		if (!dir.mkpath(dirPath)) {
			std::cerr << "Logger: could not create log path " << qPrintable(dirPath);
		}
	}
	
	if (!file_.open(QFile::WriteOnly | QFile::Text | QIODevice::Append)) {
		std::cerr << "QsLog: could not open log file " << qPrintable(filePath);
	}
	outputStream_.setDevice(&file_);
	//mOutputStream.setCodec(QTextCodec::codecForName("UTF-8"));
}

void FileLogAppender::write(const QString& message)
{
	if (!file_.isOpen()) {
		Q_ASSERT(false);
		return;
	}

	outputStream_ << message << endl;
	outputStream_.flush();
}
