#include "stdafx.h"
#include "LocaleManager.h"
#include "AppSettings.h"
#include "Tools/Filesystem.h"

using namespace Tools;

LocaleManager::LocaleManager(QObject* parent)
	: QObject(parent)
{}

LocaleManager::~LocaleManager()
{}

void LocaleManager::loadTranslation()
{
	QString localeName = loadLocale();
	loadTranslator(localeName);
}

QString LocaleManager::loadLocale()
{
	QSettings* settings = AppSettings::get();

	CHECK_QSTRING(currLocale_.name());
	QString localeName = settings->value(_S("General/Locale")).toString();
	if (!localeName.isEmpty())
		currLocale_ = QLocale(localeName);
	else
		localeName = currLocale_.name();

	settings->setValue( SettingsDefs::kLocaleKey, currLocale_.name());

	return localeName;
}

void LocaleManager::loadTranslator(const QString& localeName)
{
	CHECK_QSTRING(localeName);

	QString appDir = QCoreApplication::applicationDirPath();
	QString trDirPath = Filesystem::mergePath(appDir, _S("Languages"));
	QDir trDir(trDirPath);
	if (!trDir.exists()) {
		LOG_WARNING() << "Languages dir not exist" << trDir.path();
		return;
	}

	DCHECK(locales_.empty());
	locales_.clear();
	locales_.insert(_S("English"), _S("en_EN"));
	QFileInfoList trFiles = trDir.entryInfoList(QStringList(_S("*.qm")));
	foreach (const QFileInfo& langFileInfo, trFiles) {
		QString trFilename = langFileInfo.fileName();
		QLocale locale(trFilename);
		QString localeName = QLocale::languageToString(locale.language());

		locales_.insert(localeName, trFilename);
	}

	if (currLocale_ == QLocale::English || currLocale_ == QLocale::C)
		return;

	QString translationFilename = QFileInfo(localeName).fileName();// localeName.mid(0, 2) + _S(".qm");
	QTranslator* translator = new QTranslator(qApp);
	bool loaded = translator->load(translationFilename, trDirPath);
	if (!loaded) {
		LOG_WARNING() << "Translation wasn't loaded." 
			<< "filename" << translationFilename 
			<< "dir" << trDirPath
			<< "locale" << localeName;

		delete translator;
		return;
	}

	QApplication::installTranslator(translator);
}
