#pragma once

namespace SettingsDefs {

const QString kLocaleKey = _S("General/Locale");

}

class AppSettings : public QObject
{
	Q_OBJECT

public:
	explicit AppSettings(QObject* parent = nullptr);
	virtual ~AppSettings();

	static QSettings* get();

	// TODO: move locales stuff to separate class
	QMap<QString, QString>& locales();
	void setCurrLocale(const QLocale& locale, QTranslator* translator = nullptr);
	QTranslator* translator_;
	const QLocale& currLocale() const;

private:
	QMap<QString, QString> locales_; // locale name -> filename
	QLocale currLocale_;
};
