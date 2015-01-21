#include "stdafx.h"
#include "Bugs/Checks.h"

namespace Tools {
namespace StringTools {

QString fromSourceEncoding(const char* str)
{
	QTextCodec* const sourcesEncoding = QTextCodec::codecForLocale(); // assume that sources have system locale
	return sourcesEncoding->toUnicode(str);
}

bool isUrl(const QString& str)
{
	DCHECK_QSTRING(str);

	// TODO: change to more intelligible check
	return (
		str.startsWith(_S("http://")) 
		|| str.startsWith(_S("https://")) 
		|| str.startsWith(_S("www."))
	);
}

} // namespace StringTools
} // namespace Tools