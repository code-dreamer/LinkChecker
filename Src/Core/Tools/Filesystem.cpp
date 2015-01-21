#include "stdafx.h"
#include "Tools/Filesystem.h"
#include "Bugs/Checks.h"

namespace Tools {
namespace Filesystem {

namespace {

QString getShortPathName(const QString& path)
{
	DCHECK_QSTRING(path);

	// Determine length, then convert.
	const LPCTSTR pathC = reinterpret_cast<LPCTSTR>(path.utf16());
	const DWORD length = ::GetShortPathNameW(pathC, NULL, 0);
	if (length == 0) {
		qWarning() << "GetShortPathNameW failed";
		return path;
	}
	
	QScopedArrayPointer<TCHAR> buffer(new TCHAR[length]);
	::GetShortPathNameW(pathC, buffer.data(), length);
	
	QString result = QString::fromUtf16(reinterpret_cast<const ushort *>(buffer.data()), length - 1);
	DCHECK_QSTRING(result);
	return result;
}

QString getLongPathName(const QString& path)
{
	DCHECK_QSTRING(path);

	// Determine length, then convert
	const LPCTSTR pathC = reinterpret_cast<LPCTSTR>(path.utf16());
	const DWORD length = ::GetLongPathNameW(pathC, NULL, 0);
	if (length == 0) {
		qWarning() << "GetLongPathNameW failed";
		return path;
	}

	QScopedArrayPointer<TCHAR> buffer(new TCHAR[length]);
	::GetLongPathNameW(pathC, buffer.data(), length);
	
	QString result = QString::fromUtf16(reinterpret_cast<const ushort *>(buffer.data()), length - 1);
	DCHECK_QSTRING(result);
	return result;
}

} // namespace

QString normalizePath(const QString& path, bool internalFormat)
{
	DCHECK_QSTRING(path);

	QString normalizedPath = path.trimmed();
	QString canonicalPath = QFileInfo(normalizedPath).canonicalPath();
	if (!canonicalPath.isEmpty() && canonicalPath != _S(".")) {
		normalizedPath = getShortPathName(normalizedPath);
		normalizedPath = getLongPathName(normalizedPath);
	}
	
	if (normalizedPath.length() > 2 && normalizedPath.at(1) == _C(':')) {
		normalizedPath[0] = normalizedPath.at(0).toUpper();
	}

	if (internalFormat) {
		normalizedPath = QDir::fromNativeSeparators(normalizedPath);
		if (QFileInfo(normalizedPath).isDir() && !normalizedPath.endsWith(_C('/'))) {
			normalizedPath += _C('/');
		}
	}
	else {
		normalizedPath = QDir::toNativeSeparators(normalizedPath);
		if (QFileInfo(normalizedPath).isDir() && !normalizedPath.endsWith(_C('\\'))) {
			normalizedPath += _C('\\');
		}
	}
	
	DCHECK_QSTRING(normalizedPath);
	return normalizedPath;
}

QString mergePath(const QString& path1, const QString& path2)
{
	DCHECK(checkPath(path1, true));
	DCHECK(checkPath(path2, true));

	QString localPath1 = normalizePath(path1, true);
	const QChar separator = _C('/');
	if ( !localPath1.endsWith(separator) ) {
		localPath1.append(separator);
	}

	QString localPath2 = normalizePath(path2, true);
	if ( localPath2.startsWith(separator) ) {
		localPath2.remove(0, 1);
	}

	return localPath1.append(localPath2);
}

bool pathExist(const QString& path)
{
	DCHECK(checkPath(path, true));
	return QFileInfo(path).exists();
}

bool checkPath(const QString& path, bool internalFormat)
{
	bool ok = !path.isEmpty();
	
	if (internalFormat) {
		return ok && isInternalPath(path);
	}
	else {
		return ok && isNativePath(path);
	}
}

bool checkExistedPath(const QString& path)
{
	return checkPath(path, true) && pathExist(path);
}

QByteArray readFile(const QString& path)
{
	QByteArray result;

	QFile data(path);
	if (data.open(QIODevice::ReadOnly)) {
		result = data.readAll();
	}

	return result;
}

bool isEqual(const QString& path1, const QString& path2)
{
	DCHECK(checkPath(path1, true));
	DCHECK(checkPath(path2, true));

	return QString::compare( QDir::toNativeSeparators(path1), QDir::toNativeSeparators(path2), Qt::CaseInsensitive ) == 0;
}

QString extractDirPath(const QString& filePath)
{
	DCHECK(checkPath(filePath, true));
	DCHECK(isInternalPath(filePath));

	QString result = filePath;
	
	if (!QFileInfo(filePath).isDir()) {
		if (result.endsWith(_C('/'))) {
			result = result.left(result.length()-1);
		}
		int ind = result.lastIndexOf(_C('/'));
		if (ind != -1) {
			result = result.left(ind);
			result += _C('/');
		}
	}

	return result;
}

bool isNativePath(const QString& path)
{
	return QDir::toNativeSeparators(path) == path;
}

bool isInternalPath(const QString& path)
{
	return QDir::fromNativeSeparators(path) == path;
}

} // namespace Tools
} // namespace FileSystemTools
