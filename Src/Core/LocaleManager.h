#pragma once

class LocaleManager : public QObject
{
	Q_OBJECT

public:
	explicit LocaleManager(QObject* parent = nullptr);
	virtual ~LocaleManager();

public:
	void loadTranslation();

	//QMap<QString, QString>& locales();
	//void setCurrLocale(const QLocale& locale, QTranslator* translator = nullptr);
	//const QLocale& currLocale() const;

private:
	QString loadLocale();
	void loadTranslator(const QString& localeName);

private:
	QLocale currLocale_; // Load default locale for current system.
	QMap<QString, QString> locales_; // locale name -> filename
};
