#include "stdafx.h"
#include "Tools/WinApi.h"
#include "Bugs/Checks.h"

namespace Tools {
namespace WinApi {

QString driveLetterPathFromDeviceForm(const QString& deviceFormPath)
{
	DCHECK_QSTRING(deviceFormPath);

	QString result;

	QString currPath = deviceFormPath;
	TCHAR buff[MAX_PATH];
	buff[0] = '\0';
	wchar_t driveLetter[3] = L" :";
	if (GetLogicalDriveStrings(MAX_PATH-1, buff)) {
		wchar_t* p = buff;
		wchar_t driveDeviceName[MAX_PATH];
		do {
			*driveLetter = *p;
			// Look up each device name
			if (QueryDosDevice(driveLetter, driveDeviceName, MAX_PATH)) {
				QString driveDeviceNameStr = QString::fromWCharArray(driveDeviceName);
				if (currPath.startsWith(driveDeviceNameStr, Qt::CaseInsensitive )) {
					currPath.replace(driveDeviceNameStr, QString::fromWCharArray(driveLetter));
					result = currPath;
					break;
				}
			}

			// Go to the next '\0' character.
			while (*p++);
		} while (*p);
	}

	return result;
}

LPSTR* commandLineToArgvA(LPSTR lpCmdLine, INT* pNumArgs)
{
	DCHECK_CSTRING(lpCmdLine);
	DCHECK_PTR(pNumArgs);

	int retval;
	retval = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, NULL, 0);
	if (!SUCCEEDED(retval))
		return NULL;

	LPWSTR lpWideCharStr = (LPWSTR)malloc(retval * sizeof(WCHAR));
	if (lpWideCharStr == NULL)
		return NULL;

	retval = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, lpWideCharStr, retval);
	if (!SUCCEEDED(retval))	{
		free(lpWideCharStr);
		return NULL;
	}

	int numArgs;
	LPWSTR* args;
	args = CommandLineToArgvW(lpWideCharStr, &numArgs);
	free(lpWideCharStr);
	if (args == NULL)
		return NULL;

	int storage = numArgs * sizeof(LPSTR);
	for (int i = 0; i < numArgs; ++ i) {
		BOOL lpUsedDefaultChar = FALSE;
		retval = WideCharToMultiByte(CP_ACP, 0, args[i], -1, NULL, 0, NULL, &lpUsedDefaultChar);
		if (!SUCCEEDED(retval))	{
			LocalFree(args);
			return NULL;
		}

		storage += retval;
	}

	LPSTR* result = (LPSTR*)LocalAlloc(LMEM_FIXED, storage);
	if (result == NULL)	{
		LocalFree(args);
		return NULL;
	}

	int bufLen = storage - numArgs * sizeof(LPSTR);
	LPSTR buffer = ((LPSTR)result) + numArgs * sizeof(LPSTR);
	for (int i = 0; i < numArgs; ++ i) {
		DCHECK(bufLen > 0);
		BOOL lpUsedDefaultChar = FALSE;
		retval = WideCharToMultiByte(CP_ACP, 0, args[i], -1, buffer, bufLen, NULL, &lpUsedDefaultChar);
		if (!SUCCEEDED(retval))	{
			LocalFree(result);
			LocalFree(args);
			return NULL;
		}

		result[i] = buffer;
		buffer += retval;
		bufLen -= retval;
	}

	LocalFree(args);

	*pNumArgs = numArgs;
	return result;
}

} // namespace WinApi
} // namespace Tools