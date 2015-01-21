#pragma once

#include "AppError.h"

class IOError : public AppError
{
public:
	IOError(const QIODevice& failedDevice);
	IOError(const QString& ioError);

	virtual Bugs::Exception* clone() const override;		
	virtual void rethrow() const override;				
	
//private:													
	//IOError& operator=(const IOError& exc);				
};
