#pragma once

class AppSettings;
class SitesDataModel;
class SiteContainer;
class SiteChecker;
class LocaleManager;

namespace Gui {
class MainWindow;
}

class CoreApp : public QApplication
{
	Q_OBJECT

public:
	CoreApp(int& argc, char** argv);
	virtual ~CoreApp();

public:
	AppSettings* settings();
	void init();
	void showGui();

public:
	virtual bool notify(QObject* obj, QEvent* event) override;

private:
	void setAppInfo();
	void setupTextCodecs();
	void loadFromCmdLine();

private:
	AppSettings* appSettings_;
	LocaleManager* localeManager_;
	Gui::MainWindow* mainWindow_;
	SitesDataModel* dataModel_;
	SiteContainer* siteContainer_;
	SiteChecker* siteChecker_;
};
