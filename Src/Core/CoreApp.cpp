#include "stdafx.h"
#include "CoreApp.h"
#include "AppSettings.h"
#include "Tools/StringTools.h"
#include "Bugs/Exception.h"
#include "Bugs/ExceptionHandler.h"
#include "Tools/Filesystem.h"
#include "Gui/MainWindow.h"
#include "SitesDataModel.h"
#include "Bugs/ExceptionHandler.h"
#include "SiteContainer.h"
#include "SiteChecker.h"
#include "Logging/Logger.h"
#include "LocaleManager.h"

CoreApp::CoreApp(int& argc, char** argv)
	: QApplication(argc, argv)
	, appSettings_(nullptr)
{}

void CoreApp::init()
{
	//QFileDialogArgs args;
	/*args.parent = parent;
	args.caption = caption;
	args.directory = QFileDialogPrivate::workingDirectory(dir);
	args.mode = (options & ShowDirsOnly ? DirectoryOnly : Directory);
	args.options = options;
	*/
	//qt_win_get_existing_directory(args)

	/*QString dir = QFileDialog::getExistingDirectory(0, tr("Open Directory"),
		QString(),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);*/

	appSettings_ = new AppSettings(this);

	setAppInfo();
	setupTextCodecs();

	localeManager_ = new LocaleManager();
	localeManager_->loadTranslation();

	siteContainer_ = new SiteContainer();
	siteChecker_ = new SiteChecker();
	dataModel_ = new SitesDataModel(siteContainer_, siteChecker_);
	mainWindow_ = new Gui::MainWindow(dataModel_);

	loadFromCmdLine();
}

CoreApp::~CoreApp()
{
	safeDelete(mainWindow_);
	safeDelete(dataModel_);
	safeDelete(siteChecker_);
	safeDelete(siteContainer_);
	safeDelete(localeManager_);
	safeDelete(appSettings_);
}

void CoreApp::loadFromCmdLine()
{
	QStringList cmdlineArgs = QCoreApplication::arguments();
	if (Tools::Filesystem::normalizePath(cmdlineArgs.first(), true) == QCoreApplication::applicationFilePath()) {
		cmdlineArgs.removeFirst();
	}
	
	foreach(const QString& arg, cmdlineArgs) {
		if (arg.endsWith(_S(".csv"))) {
			try {
				QString filePath = Tools::Filesystem::normalizePath(arg, true);
				dataModel_->loadFromCSV(filePath);
			}
			catch (const Bugs::Exception& e) {
				Bugs::ExceptionHandler::reportError(e, true);
			}
			break;
		}
	}
}

void CoreApp::showGui()
{
#ifdef DEBUG
	mainWindow_->showMaximized();
#else
	mainWindow_->show();
#endif
}

AppSettings* CoreApp::settings()
{
	DCHECK_PTR(appSettings_);
	return appSettings_;
}

void CoreApp::setAppInfo()
{
	using Tools::StringTools::fromSourceEncoding;
	using namespace AppGlobal;

	QCoreApplication::setOrganizationDomain( QLatin1String(AppInfo::HomeUrl) );
	QCoreApplication::setOrganizationName( fromSourceEncoding(AppInfo::CompanynName) );
	QCoreApplication::setApplicationName( fromSourceEncoding(AppInfo::Name) );
	QCoreApplication::setApplicationVersion( QLatin1String(AppInfo::Version) );
}

void CoreApp::setupTextCodecs()
{
	const QString systemLocaleName = QLocale::languageToString( QLocale::system().language() );
	const char* locale = std::setlocale(LC_ALL, systemLocaleName.toLatin1().constData());
	if (locale == nullptr) {
		LOG_WARNING() << "Can't set locale" << systemLocaleName;
	}
}

bool CoreApp::notify(QObject* receiver, QEvent* event)
{
	using Bugs::ExceptionHandler::reportError;

	try {
		return QApplication::notify(receiver, event);
	}
	catch (const Bugs::Exception& exception) {
		reportError(exception);
	}
	catch (const std::exception& exception) {
		reportError(exception);
	}
	catch(...) {
		reportError(tr("%1. Critical error was happened!").arg(QLatin1String(AppGlobal::AppInfo::Name)), Bugs::ErrorSeverity::fatal, false);
		QApplication::exit(-1);
	}

	return false;
}
