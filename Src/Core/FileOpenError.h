#pragma once

#include "IOError.h"

class FileOpenError: public IOError
{
public:
	FileOpenError(const QString& filePath, const QIODevice& device);

	virtual Bugs::Exception* clone() const override;		
	virtual void rethrow() const override;				

private:													
	IOError& operator=(const IOError& exc);	

private:
	QString filePath_;
};
