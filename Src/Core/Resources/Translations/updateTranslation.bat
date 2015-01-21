set prevPath=%CD%
cd ../../../../3rdparty/qt-5.0.1/qt/bin
set PATH=%PATH%;%CD%
chdir %prevPath%

lupdate -recursive ../../../Core -ts %CD%\ru_RU.ts
::lupdate --help
pause