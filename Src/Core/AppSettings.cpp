#include "stdafx.h"
#include "AppSettings.h"
#include "Tools/Filesystem.h"
#include "Tools/FilesystemErrors.h"

namespace {

QSettings* gSettings;

QString createAppSettingsFilePath()
{
	QString appDir = QCoreApplication::applicationDirPath();
	QString settingsDirPath = Tools::Filesystem::mergePath(appDir, _S("Settings"));
	QDir settingsDir(settingsDirPath);
	if (!settingsDir.exists()) {
		if (!settingsDir.mkpath(settingsDir.path())) {
			QString msg = qApp->translate("AppSettings", "Can't create dir %1").arg(Tools::Filesystem::normalizePath(settingsDir.path(), false));
			THROW(Tools::Filesystem::DirError(msg));
		}
	}

	QString settingsFile = QString::fromLatin1(AppGlobal::AppInfo::StrId) + _S(".ini");
	QString settingsFilePath = Tools::Filesystem::mergePath(settingsDirPath, settingsFile);
	return settingsFilePath;
}
} // namespace

AppSettings::AppSettings(QObject* parent)
{
	CHECK(!gSettings);
	gSettings = new QSettings(createAppSettingsFilePath(), QSettings::IniFormat, parent);
}

AppSettings::~AppSettings()
{
	gSettings = nullptr;
}

QMap<QString, QString>& AppSettings::locales()
{
	return locales_;
}

void AppSettings::setCurrLocale(const QLocale& locale, QTranslator* translator)
{
	currLocale_ = locale;
	gSettings->setValue(_S("General/Locale"), currLocale_.name());

	if (translator != nullptr) {
		if (translator_ != nullptr) {
			delete translator_;
		}
		translator_ = translator;
	}
}

const QLocale& AppSettings::currLocale() const
{
	return currLocale_;
}

QSettings* AppSettings::get()
{
	CHECK_PTR(gSettings);
	return gSettings;
}
