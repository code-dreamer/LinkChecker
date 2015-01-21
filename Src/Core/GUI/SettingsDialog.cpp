#include "stdafx.h"
#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "CoreApp.h"
#include "Tools/Filesystem.h"
#include "AppSettings.h"
#include "Tools/QtHelpers.h"
#include "Logging/Logger.h"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent)
	, ui_(new Ui::SettingsDialog())
{
	ui_->setupUi(this);
	QWidget::setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	CoreApp* app = qobject_cast<CoreApp*>(qApp);
	const QMap<QString, QString>& locales = app->settings()->locales();
	DCHECK(!locales.empty());
	ui_->languagesCombo->clear();
	int i = 0, selIndex = 0;
	QString appLangName = QLocale::languageToString(app->settings()->currLocale().language());
	for (auto it = locales.begin(); it != locales.end(); ++it) {
		QString langName = it.key();
		ui_->languagesCombo->addItem(it.key(), it.value());
		if (langName == appLangName) {
			selIndex = i;
		}
		++i;
	}
	ui_->languagesCombo->setCurrentIndex(selIndex);

	using Tools::QtHelpers::checkedConnect;
	checkedConnect(ui_->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::accepted);
	checkedConnect(ui_->buttonBox, &QDialogButtonBox::rejected, this, &SettingsDialog::rejected);
}

SettingsDialog::~SettingsDialog()
{}

void SettingsDialog::accepted()
{
	bool needToRestart = false;

	CoreApp* app = qobject_cast<CoreApp*>(qApp);
	int index = ui_->languagesCombo->currentIndex();
	if (index == -1) {
		DCHECK(false);
		LOG_WARNING() << "Invalid index";
		return;
	}
	QString appLang = QLocale::languageToString(app->settings()->currLocale().language());
	if (appLang != ui_->languagesCombo->itemText(index)) {
		needToRestart = true;

		QString trFilename = ui_->languagesCombo->itemData(index).toString();
		QString appDir = QCoreApplication::applicationDirPath();
		QString trDirPath = Tools::Filesystem::mergePath(appDir, _S("Languages"));
		QDir trDir(trDirPath);
		if (!trDir.exists()) {
			LOG_WARNING() << "Languages dir not exist" << trDir.path();
			return;
		}

		QLocale newLocale(trFilename);
		app->settings()->setCurrLocale(newLocale);

		if (newLocale == QLocale::English || newLocale == QLocale::C) {
			QApplication::removeTranslator(app->settings()->translator_);
		}
		else {
			QTranslator* translator = new QTranslator(qApp);
			bool loaded = translator->load(trFilename, trDirPath);
			if (!loaded) {
				LOG_WARNING() << "Translation wasn't loaded." << 
					"filename" << trFilename << 
					"dir" << trDirPath;

				delete translator;
				return;
			}

			QApplication::installTranslator(translator);
		}
	}

	if (needToRestart) {
		QMessageBox::warning(this, tr("Restart"), tr("You need to restart application to apply new settings"));
	}

	QDialog::accept();
}

void SettingsDialog::rejected()
{
	QDialog::reject();
}
