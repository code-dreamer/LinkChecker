#include "stdafx.h"
#include "Tools/Sys.h"
#include "Tools/Filesystem.h"

namespace Tools {
namespace Sys {

QString currentDir()
{
	wchar_t buff[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, buff);

	return Filesystem::normalizePath(QString::fromWCharArray(buff), true);
}

} // namespace WinApi
} // namespace Tools