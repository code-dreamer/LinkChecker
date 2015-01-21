#include "stdafx.h"
#include "Core.h"
#include "CoreApp.h"
#include "Bugs/Exception.h"
#include "Bugs/ExceptionHandler.h"
#include "Gui/MainWindow.h"
#include "Tools/Filesystem.h"
#include "Tools/Sys.h"
#include "Logging/Logger.h"
#include "Logging/DebugConsoleLogAppender.h"
#include "Logging/ConsoleLogAppender.h"
#include "Logging/FileLogAppender.h"

using namespace Tools::Filesystem;

static void initAppLogger(const QString& appDir)
{
	Logger* logger = Logger::instance();

#ifdef DEBUG
	logger->setLevel(LogLevel::debug);
#else
	logger->setLevel(LogLevel::warning);
#endif // DEBUG

	logger->addAppender(new DebugConsoleLogAppender());
	logger->addAppender(new ConsoleLogAppender());

	//QString logDir = mergePath(Tools::Sys::currentDir(), _S("Log"));// QStandardPaths::writableLocation(QStandardPaths::DataLocation);
	//QString logPath = mergePath(logDir, _S("main.log"));
	QString logDir = mergePath(appDir, _S("Log"));
	QString logPath = mergePath(logDir, _S("main.log"));
	FileLogAppender* fileAppender = new FileLogAppender(logPath);
	logger->addAppender(fileAppender);
}

namespace Core {
int exec(int& argc, char** argv) 
{
	using Bugs::ExceptionHandler::reportError;

	if (argc < 1) {
		std::wcerr << "argc = " << argc << std::endl;
		return EXIT_FAILURE;
	}

	try {
		QString appFilePath = QLatin1String(argv[0]);
		QFileInfo appPathInfo(appFilePath);
		QString appDir = appPathInfo.canonicalPath();
		initAppLogger(appDir);

		QString libDir = mergePath(appDir, _S("Lib"));
		if (!QFileInfo(libDir).exists()) {
			FAIL();
			std::wcerr << "Folder " << libDir.toStdWString() << " not exist" << std::endl;
			return EXIT_FAILURE;
		}

		QCoreApplication::addLibraryPath(libDir);

		CoreApp app(argc, argv);

#ifdef DEBUG
		DCHECK( QCoreApplication::applicationDirPath().endsWith(_S("Debug"), Qt::CaseInsensitive) );
#endif

		app.init();
		app.showGui();
		//QString platformPluginPath = QLatin1String(qgetenv("QT_QPA_PLATFORM_PLUGIN_PATH"));
		//QString platformPluginPath1 = QLatin1String(qgetenv("QT_PLUGIN_PATH"));

		return app.exec();
	}
	catch (const Bugs::Exception& exception) 	{
		FAIL();
		Bugs::ExceptionHandler::reportError(exception);
	}
	catch (const std::exception& exception) {
		FAIL();
		Bugs::ExceptionHandler::reportError(exception);
	}
	catch (...) {
		FAIL();
		reportError( QCoreApplication::translate("Core::exec", "%1. Critical error was happened!").arg(QLatin1String(AppGlobal::AppInfo::Name)), Bugs::ErrorSeverity::fatal, true);
	}

	return EXIT_FAILURE;
}

} // namespace Core
