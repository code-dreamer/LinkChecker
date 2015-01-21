#include "stdafx.h"
#include "FileOpenError.h"

FileOpenError::FileOpenError(const QString& filePath, const QIODevice& device)
	: IOError(device)
	, filePath_(filePath)
{
	CHECK_QSTRING(filePath);

	Exception::setMessage( QCoreApplication::translate("FileOpenError", "Can't open file '%1'\n%2").arg(filePath_, IOError::message()) );
}

Bugs::Exception* FileOpenError::clone() const
{
	return new IOError(*this);
}

void FileOpenError::rethrow() const
{
	throw *this;
}
