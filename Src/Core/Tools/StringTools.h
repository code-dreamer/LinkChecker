#pragma once

namespace Tools {
namespace StringTools { // TODO: rename into Tools::Strings
QString fromSourceEncoding(const char* str);
bool isUrl(const QString& str);
} // namespace StringTools
} // namespace Tools