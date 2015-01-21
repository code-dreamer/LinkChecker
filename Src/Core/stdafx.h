#pragma once

#pragma warning(push, 0)
#pragma warning (disable : 4127 4265 4350)

#include "Shared/WinHeader.h"
#include "Shared/GlobalHeader.h"

#define QT_CORE_LIB
#include <QtCore>
#include <QtCore/qt_windows.h>
#define QT_GUI_LIB
#include <QtGui>
#define QT_WIDGETS_LIB
#include <QtWidgets>
#define QT_NETWORK_LIB
#include <QtNetwork>
#define QT_XML_LIB
#include <QtXml>

#include "Shared/QtDefines.h"

#include <clocale>

// std headers
#include <chrono>
#include <thread>
#include <string>
#include <memory>
#include <iostream>

#ifdef DEBUG
//#	include <vld.h>
#endif // DEBUG

#include "Bugs/BugsPrec.h"

// Project specific includes
#include "Bugs/BugsPrec.h"
#include "Bugs/Checks.h"
#include "Shared/AppInfo.h"
#include "Shared/SolutionShared.h"
#include "Shared/QtDefines.h"
#include "Tools/Cpp.h"
using Tools::Cpp::safeDelete;
using Tools::Cpp::safeDeleteA;
#include "Tools/ScopeExit.h"
#include "Logging/Logger.h"

#pragma warning(pop)