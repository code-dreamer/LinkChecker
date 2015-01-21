#pragma once


#include "Bugs/Checks.h"

namespace Tools {
namespace QtHelpers {

template <typename Func1, typename Func2>
static inline QMetaObject::Connection checkedConnect(const typename QtPrivate::FunctionPointer<Func1>::Object* sender, Func1 signal,
                                     const typename QtPrivate::FunctionPointer<Func2>::Object* receiver, Func2 slot,
                                     Qt::ConnectionType type = Qt::AutoConnection)
{
	QMetaObject::Connection connection = QObject::connect(sender, signal, receiver, slot, type);
	DCHECK_MSG(connection, "Connection failed.");

	return connection;
}

template <typename T>
struct QueuedDeleter
{
	static inline void cleanup(T* pointer)
	{
		// Enforce a complete type.
		typedef char IsIncompleteType[ sizeof(T) ? 1 : -1 ];
		(void) sizeof(IsIncompleteType);

		DCHECK_PTR(pointer);
		pointer->deleteLater();
	}
};

} // namespace QtHelpers
} // namespace Tools