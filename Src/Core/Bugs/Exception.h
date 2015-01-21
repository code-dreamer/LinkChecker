#pragma once

#include "Bugs/Checks.h"
#include "Tools/NonAssignable.h"

//////////////////////////////////////////////////
// don't write something like that:
// try {
// ...
// }
// catch (Exception& e) {
//		throw e; // wrong
//		throw; // ok
// }
//////////////////////////////////////////////////

namespace Bugs {

typedef QPair<QString, QVariant> ExceptionValue;

enum class ErrorSeverity
{
	  warning =	0x0		// Some strange, but non-fatal has happen
						// "Partial allocation for 'Quake 2' failed. Prepare for full allocation..."

	, error	=	0x1		// Error (not critical). Application may remain unstable but not crashing.
						// "Can't load icon 'smile.png'. Windows error 2."

	, fatal =	0x2		// Fatal, unrecoverable error. Application in crash state and can't be recovered (unhandled exceptions handlers and etc).
						// "Unhanded Exception. Code 0xC0000005 (access violation). Address:
};

class Exception : private Tools::NonAssignable 
{
	template<typename T>
	friend void throwImpl(T& exception, const char* functionName, const char* filename, int lineNumber);

	template <typename T> 
	friend T& operator<<(T& exception, const ExceptionValue& value);

public:
	virtual ~Exception() throw();

protected:
	//Exception();
	Exception(const QString& message);
	Exception(const QString& message, const Exception& inner);
	Exception(const Exception& other);

protected: // deny creating on the heap
	static void* operator new(size_t size);
	static void* operator new[](size_t size);
	static void operator delete(void* ptr);
	static void operator delete[](void* ptr);

protected:
	void setMessage(const QString& message);

public:
	QString message() const;
	QString toString() const;
	QString className() const;
	QString additionalProperties() const;
	void setSeverity(ErrorSeverity severity);
	ErrorSeverity severity() const;

	/// Creates an exact copy of the exception.
	///
	/// The copy can later be thrown again by
	/// invoking rethrow() on it.
	virtual Exception* clone() const = 0; // return new Exception(*this);

	/// (Re)Throws the exception.
	///
	/// This is useful for temporarily storing a
	/// copy of an exception (see clone()), then
	/// throwing it again.
	virtual void rethrow() const = 0; // throw *this;

private:
	void setThrowedSource(const QString& info);
	void addAdditionalValue(const ExceptionValue& value);

private:
	QString message_;
	QList<ExceptionValue> additionalValues_;
	QString throwedSource_;
	Exception* inner_;
	ErrorSeverity severity_;
};

extern ExceptionValue makeExProp(const QByteArray& name, const QVariant& value);

template<typename T>
T& operator<<(T& exception, const ExceptionValue& value)
{
	exception.addAdditionalValue(value);
	return exception;
}

QString formateThrowedSource(const char* functionName, const char* filename, int lineNumber);
void writeExceptionToLog(const Bugs::Exception& e);

template<typename T>
void throwImpl(T& exception, const char* functionName, const char* filename, int lineNumber)
{
	QString source = Bugs::formateThrowedSource(functionName, filename, lineNumber);
	exception.setThrowedSource(source);
	writeExceptionToLog(exception);
	throw exception;
}

} // namespace Bugs

#define THROW(exception)															\
	__pragma(warning(push))															\
	__pragma(warning(disable : 4127))												\
	__pragma(warning(disable : 4239))												\
	Bugs::throwImpl(exception, __FUNCTION__, __FILE__, __LINE__);					\
	__pragma(warning(pop))

// Useful macros
//
#define DECLARE_EXCEPTION(ExClass, ExBaseClass)					\
	class ExClass: public ExBaseClass							\
	{															\
	public:														\
		ExClass(const QString& message);						\
		ExClass(const QString& message, const ExClass& inner);	\
		ExClass(const ExClass& other);							\
		virtual ~ExClass();										\
		virtual Bugs::Exception* clone() const override;		\
		virtual void rethrow() const override;					\
																\
	private:													\
		ExClass& operator= (const ExClass& exc);				\
	};


#define PARTIAL_IMPLEMENT_EXCEPTION(ExClass)									\
	Bugs::Exception* ExClass::clone() const { return new ExClass(*this); }		\
	void ExClass::rethrow() const {	throw *this; }

#define IMPLEMENT_EXCEPTION(ExClass, ExBaseClass)													\
	ExClass::ExClass(const QString& message): ExBaseClass(message) {}								\
	ExClass::ExClass(const QString& message, const ExClass& inner): ExBaseClass(message, inner) {}	\
	ExClass::ExClass(const ExClass& exc): ExBaseClass(exc) {}										\
	ExClass::~ExClass()	{}																			\
	PARTIAL_IMPLEMENT_EXCEPTION(ExClass)
