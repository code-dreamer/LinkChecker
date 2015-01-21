#pragma once

class DownloadManager: public QObject
{
	Q_OBJECT
		QNetworkAccessManager manager;
	QList<QNetworkReply *> currentDownloads;

public:
	DownloadManager();
	void doDownload(const QUrl &url);
	QString saveFileName(const QUrl &url);
	bool saveToDisk(const QString &filename, QIODevice *data);

	public slots:
		void execute();
		void downloadFinished(QNetworkReply *reply);
		void sslErrors(const QList<QSslError> &errors);
};

