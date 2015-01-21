#include "stdafx.h"
#include "Psapi.h"
#include "Tools/Proc.h"
#include "Bugs/Checks.h"
#include "Tools/WinApi.h"
#include "Tools/Filesystem.h"

namespace Tools {
namespace Proc {

DWORD currentProcessId()
{
	return GetCurrentProcessId();
}

DWORD mainThreadId()
{
	DWORD currProcessId = currentProcessId();

	LPVOID lpThId = 0;
	_asm
	{
		mov eax, fs:[18h]
		add eax, 36
		mov [lpThId], eax
	}

	HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, currProcessId);
	if (processHandle == NULL) {
		DCHECK(false);
		return InvalidID;
	}

	DWORD result = InvalidID;
	if (ReadProcessMemory(processHandle, lpThId, &result, sizeof(result), NULL) == FALSE) {
		DCHECK(false);
		CloseHandle(processHandle);
		return InvalidID;
	}

	CloseHandle(processHandle);

	return result;
}

DWORD currentThreadId()
{
	return GetCurrentThreadId();
}

QList<PROCESSENTRY32> processList()
{
	QList<PROCESSENTRY32> info;

	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE processSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // TH32CS_SNAPALL
	if (processSnap != INVALID_HANDLE_VALUE) {
		procEntry.dwSize = sizeof(PROCESSENTRY32);

		if (::Process32First(processSnap, &procEntry)) {
			do {
				info.push_back(procEntry);
			} while (::Process32Next(processSnap, &procEntry));
		}

		::CloseHandle(processSnap);
	}

	return info;
}

QString procPath(HANDLE processHandle)
{
	DCHECK_PTR(processHandle);

	QString processPath;
	wchar_t buff[MAX_PATH];
	DWORD res = GetProcessImageFileName(processHandle, buff, MAX_PATH);
	if (res != 0) {
		QString deviceFormPah = QString::fromWCharArray(buff);
		processPath = WinApi::driveLetterPathFromDeviceForm(deviceFormPah);
		processPath = Filesystem::normalizePath(processPath, true);
	}

	DCHECK_QSTRING(processPath);
	return processPath;
}

} // namespace Proc
} // namespace Tools