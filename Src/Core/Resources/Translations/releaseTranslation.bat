set prevPath=%CD%
cd ../../../../3rdparty/qt-5.0.1/qt/bin
set PATH=%PATH%;%CD%
chdir %prevPath%

::lrelease -removeidentical -compress -nounfinished %CD%\ru.ts -qm ../../../../Build/Debug/Languages/ru_RU.qm
::lrelease -removeidentical -compress -nounfinished %CD%\ru.ts -qm ../../../../Build/Release/Languages/ru_RU.qm
lrelease -removeidentical -compress -nounfinished %CD%\ru_RU.ts -qm ru_RU.qm
::lupdate --help
pause