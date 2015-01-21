#include "stdafx.h"
#include "IOError.h"

IOError::IOError(const QIODevice& failedDevice)
	: AppError( QString(_S("I/O error: '%1'")).arg(failedDevice.errorString()) )
{}

IOError::IOError(const QString& ioError)
	: AppError( _S("I/O error: ") + ioError )
{
}

Bugs::Exception* IOError::clone() const
{
	return new IOError(*this);
}

void IOError::rethrow() const
{
	throw *this;
}
