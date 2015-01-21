#pragma once
/*
#include "Shared/Includes/Defines.h"

template<typename T>
static void safeDelete(T*& ptr)
{
	CHECK_PTR(ptr);

	typedef char TypeIsCompleteCheck[sizeof(T)];
	if (ptr != nullptr) {
		delete ptr;
		ptr = nullptr;
	}
}

template<typename T>
static void safeSeleteA(T*& ptr) 
{
	CHECK_PTR(ptr);

	typedef char TypeIsCompleteCheck[sizeof(T)];
	if (ptr != nullptr) {
		delete[] ptr;
		ptr = nullptr;
	}
}*/

/*
// check connections in debug mode
//
#include <QtCore/QObject>

static inline bool checkedConnect(const QObject* sender, const char* signal, const QObject* receiver, const char* member, 
	Qt::ConnectionType connectionType = Qt::AutoConnection)
{
	bool connected = QObject::connect(sender, signal, receiver, member, connectionType);
	ASSERT_MSG(connected, "Connection failed.");

	return connected;
}

static inline bool checkedConnect(const QObject* sender, const QMetaMethod& signal, const QObject* receiver, const QMetaMethod& method,
	Qt::ConnectionType connectionType = Qt::AutoConnection)
{
	bool connected = QObject::connect(sender, signal, receiver, method, connectionType);
	ASSERT_MSG(connected, "Connection failed.");

	return connected;
}

static inline bool checkedDisonnect(const QObject* sender, const char* signal, const QObject* receiver, const char* member)
{
	bool disconnected = QObject::disconnect(sender, signal, receiver, member);
	ASSERT_MSG(disconnected, "Disconnection failed.");

	return disconnected;
}

static inline bool checkedDisonnect(const QObject* sender, const QMetaMethod& signal, const QObject* receiver, const QMetaMethod& member)
{
	bool disconnected = QObject::disconnect(sender, signal, receiver, member);
	ASSERT_MSG(disconnected, "Disconnection failed.");

	return disconnected;
}
*/