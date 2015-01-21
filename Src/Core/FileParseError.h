#pragma once

#include "IOError.h"

class FileParseError: public IOError
{
public:
	FileParseError(const QString& filepath, QString ioError = QCoreApplication::translate("FileParseError", "Invalid file contents"));
	virtual ~FileParseError();

	virtual Bugs::Exception* clone() const override;		
	virtual void rethrow() const override;				
	const QString& filePath() const;

private:													
	IOError& operator=(const IOError& exc);

private:
	QString filepath_;
};
