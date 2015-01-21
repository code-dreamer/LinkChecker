#pragma once

enum class CheckResult
{
	undefined,
	notChecked,
	inProgress,
	linkPresent,
	linkNotFound,
	searchFailed
};

enum class CheckType
{
	onePage, 
	siteWide
};

class Site : public QObject
{
	Q_OBJECT

public:
	Site(QObject* parent);
	virtual ~Site() {};

signals:
	void propChanged(qint32 index);

//private:
	//Site(const Site &);

public:
	static QString checkResultToString(CheckResult checkResult);
	static CheckResult stringToCheckResult(const QString& checkResultStr);

public:
	static qint32 propsCount();
	static QString propName(qint32 index);
	static qint32 propMinWidth(qint32 index);

	// mySite
	const QUrl& url() const;
	void setUrl(const QUrl& url);
	
	// hisLinkOnMySite
	const QUrl& linkedUrl() const;
	void setLinkedUrl(const QUrl& url);
	
	// hisSite
	const QUrl& linkedSite() const;
	void setLinkedSite(const QUrl& url);
	
	// myLinkOnHisSite
	const QUrl& urlOnLinkedSite() const;
	void setUrlOnLinkedSite(const QUrl& url);
	
	CheckType checkType() const;
	void setCheckType(CheckType checkType);

	CheckResult checkResult() const;
	void setCheckResult(CheckResult checkResult);

	QString lastCheckResultString() const;
	
	const QDateTime& lastCheckDate() const;
	void setLastCheckDate(const QDateTime& date);

	static Site* createFromString(const QString& csvValuesString, QObject* parent = nullptr);
	QString toString() const;

private:
	QUrl url_;
	QUrl linkedUrl_;
	QUrl linkedSite_;
	QUrl urlOnLinkedSite_;
	CheckType checkType_;
	CheckResult checkResult_;
	QDateTime lastChecked_;
};


/*
enum class CheckResult
{
	  notStarted
	, inProgress
	, linkPresent
	, linkNotFound
	, searchFailed
};

struct SiteInfo
{
	QUrl mySite;
	QUrl hisLinkOnMySite;
	QUrl hisSite;
	QUrl myLinkOnHisSite;
	QDateTime lastChecked;
};

struct SearchPrivateData
{
	QList<QUrl> processedLinks;
	bool processedLinksMaxRiched;
};

enum class CheckOption
{
	onepage
	, siteWide
};

struct SiteCheckInfo
{
	SiteCheckInfo()
		: searchResult(CheckResult::notStarted) 
		, siteWide(false)
		, processedLinksMaxRiched(false)
	{}

	QUrl mySite;
	QUrl hisLinkOnMySite;
	QUrl hisSite;
	QUrl myLinkOnHisSite;
	QDateTime lastChecked;
	//bool isLinkPresent;
	bool siteWide;
	QList<QUrl> processedLinks;
	bool processedLinksMaxRiched;
	//bool siteInProcess;

	SearchResult searchResult;
};*/