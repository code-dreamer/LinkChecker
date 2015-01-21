#include "stdafx.h"
#include "FileParseError.h"

static QString formateError(const QString& filepath, QString ioError)
{
	QString out;
	QTextStream outStream(&out);
	outStream << qApp->translate("FileParseError", "Can't parse file");
	if ( !filepath.isEmpty() ) {
		outStream << _S(" ") << filepath << _S(" ");
	}
	outStream << ".";
	outStream << SolutionShared::Constants::kNewLine;
	outStream << ioError;

	DCHECK_QSTRING(out);
	return out;
}

FileParseError::FileParseError(const QString& filepath, QString ioError)
	: IOError(formateError(filepath, ioError))
	, filepath_(filepath)
{
	DCHECK_QSTRING(filepath);
}

FileParseError::~FileParseError()
{}

Bugs::Exception* FileParseError::clone() const
{
	return new IOError(*this);
}

void FileParseError::rethrow() const
{
	throw *this;
}

const QString& FileParseError::filePath() const
{
	DCHECK_QSTRING(filepath_);
	return filepath_;
}
