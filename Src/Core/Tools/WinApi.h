#pragma once



namespace Tools {
namespace WinApi {

QString driveLetterPathFromDeviceForm(const QString& deviceFormPath);
LPSTR* commandLineToArgvA(LPSTR lpCmdLine, INT* pNumArgs);

} // namespace WinApi
} // namespace Tools