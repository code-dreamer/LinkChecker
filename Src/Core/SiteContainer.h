#pragma once

class Site;

class SiteContainer : public QObject
{
	Q_OBJECT

public:
	SiteContainer(QObject* parent = nullptr);
	virtual ~SiteContainer();

signals:
	void sitePropChanged(qint32 siteIndex, qint32 propIndex);

public:
	static qint32 sitePropsCount();
	static qint32 sitePropMinWidth(qint32 index);
	static QString sitePropName(qint32 index);

	qint32 count() const;
	Site* site(int index);
	const Site* site(int index) const;
	void clear();

	void addFromString(const QString& csvLine);

private slots:
	void handleSitePropChanged(qint32 propIndex);

private:
	QList<Site*> sites_;
};
