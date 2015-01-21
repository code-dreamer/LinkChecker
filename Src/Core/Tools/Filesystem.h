#pragma once

namespace Tools {
namespace Filesystem {

QString normalizePath(const QString& path, bool internalFormat);
QString mergePath(const QString& path1, const QString& path2);

bool checkPath(const QString& path, bool internalFormat);

bool checkExistedPath(const QString& path);
QByteArray readFile(const QString& path);
bool isEqual(const QString& path1, const QString& path2);
QString extractDirPath(const QString& filePath);

bool isNativePath(const QString& path);
bool isInternalPath(const QString& path);

} // namespace Filesystem
} // namespace Tools