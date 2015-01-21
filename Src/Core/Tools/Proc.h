#pragma once

#include <TlHelp32.h>

namespace Tools {
namespace Proc {

const DWORD InvalidID = ((DWORD)0xFFFFFFFF);

DWORD currentProcessId();
DWORD mainThreadId();
DWORD currentThreadId();

QList<PROCESSENTRY32> processList();

QString procPath(HANDLE processHandle);

} // namespace Proc
} // namespace Tools