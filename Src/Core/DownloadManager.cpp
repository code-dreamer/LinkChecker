#include "stdafx.h"
#include "DownloadManager.h"

DownloadManager::DownloadManager()
{
	connect(&manager, SIGNAL(finished(QNetworkReply*)),
		SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::doDownload(const QUrl &url)
{
	QNetworkRequest request(url);
	//request.setRawHeader("Accept","application/xml");
	//request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml");
	//request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:19.0) Gecko/20100101 Firefox/19.0");
	//Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.22 (KHTML, like Gecko) Chrome/25.0.1364.172 Safari/537.22
	request.setRawHeader("User-Agent", "Firefox/19.0");
	//request.setRawHeader("Accept-Language","ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3");
	//request.setRawHeader("Accept-Encoding","gzip, deflate");

	QNetworkReply *reply = manager.get(request);

#ifndef QT_NO_SSL
	connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif

	currentDownloads.append(reply);
}

QString DownloadManager::saveFileName(const QUrl &url)
{
	QString path = url.path();
	QString basename = QFileInfo(path).fileName();

	if (basename.isEmpty())
		basename = _S("download");

	if (QFile::exists(basename)) {
		// already exists, don't overwrite
		int i = 0;
		basename += _C('.');
		while (QFile::exists(basename + QString::number(i)))
			++i;

		basename += QString::number(i);
	}

	return basename;
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data)
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly)) {
		fprintf(stderr, "Could not open %s for writing: %s\n",
			qPrintable(filename),
			qPrintable(file.errorString()));
		return false;
	}

	file.write(data->readAll());
	file.close();

	return true;
}

void DownloadManager::execute()
{
	QStringList args = QCoreApplication::instance()->arguments();
	args.takeFirst();           // skip the first argument, which is the program's name
	if (args.isEmpty()) {
		printf("Qt Download example - downloads all URLs in parallel\n"
			"Usage: download url1 [url2... urlN]\n"
			"\n"
			"Downloads the URLs passed in the command-line to the local directory\n"
			"If the target file already exists, a .0, .1, .2, etc. is appended to\n"
			"differentiate.\n");
		QCoreApplication::instance()->quit();
		return;
	}

	foreach (QString arg, args) {
		QUrl url = QUrl::fromEncoded(arg.toLocal8Bit());
		doDownload(url);
	}
}

void DownloadManager::sslErrors(const QList<QSslError> &sslErrors)
{
#ifndef QT_NO_SSL
	foreach (const QSslError &error, sslErrors)
		fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
	Q_UNUSED(sslErrors);
#endif
}

void DownloadManager::downloadFinished(QNetworkReply *reply)
{
	QUrl url = reply->url();
	if (reply->error()) {
		fprintf(stderr, "Download of %s failed: %s\n",
			url.toEncoded().constData(),
			qPrintable(reply->errorString()));
	} else {
		QString filename = saveFileName(url);
		if (saveToDisk(filename, reply))
			printf("Download of %s succeeded (saved to %s)\n",
			url.toEncoded().constData(), qPrintable(filename));
	}

	currentDownloads.removeAll(reply);
	reply->deleteLater();

	if (currentDownloads.isEmpty())
		// all downloads finished
			QCoreApplication::instance()->quit();
}