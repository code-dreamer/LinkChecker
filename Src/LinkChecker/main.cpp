#include "stdafx.h"
#include "Core/Core.h"

namespace  {

bool pathExists(const std::wstring& path)
{
	assert(!path.empty());

	return _waccess_s(path.c_str(), 0) != -1;
}

std::wstring libsDir()
{
	std::wstring result;

	wchar_t dllPath[MAX_PATH] = {0};
	DWORD res = GetModuleFileName(nullptr, dllPath, MAX_PATH);
	if (res != 0) {
		std::wstring pluginDir = dllPath;
		std::size_t ind = pluginDir.find_last_of('\\');
		if (ind != std::wstring::npos) {
			pluginDir.erase(ind, pluginDir.length()-ind);
			pluginDir += L"\\";
			pluginDir += L"Lib";
			if (pathExists(pluginDir.c_str())) {
				result = pluginDir;
			}
		}
	}

	return result;
}

std::wstring getEnv(const wchar_t* varName)
{
	assert(varName != nullptr);
	assert(wcslen(varName) > 0);

	std::wstring resut;

	size_t requiredSize = 0;
	wchar_t* buffer = nullptr;
	_wgetenv_s(&requiredSize, 0, 0, varName);
	if (requiredSize == 0) {
		return resut;
	}
	buffer = new wchar_t[requiredSize];
	_wgetenv_s(&requiredSize, buffer, requiredSize, varName);

	resut = buffer;
	delete[] buffer;

	return resut;
}

bool putEnv(const wchar_t* varName, const wchar_t* value)
{
	assert(varName != nullptr && wcslen(varName) > 0);
	assert(value != nullptr && wcslen(value) > 0);

	return _wputenv_s (varName, value) == 0;
}

bool addAdditionalDllPath(const std::wstring& pluginDir)
{
	assert(!pluginDir.empty());

	const wchar_t envName[] = L"PATH";
	std::wstring pathEnv = getEnv(envName);
	pathEnv += L";" + pluginDir;

	return putEnv(envName, pathEnv.c_str());
}

bool initDllPath()
{
	bool ok = false;

	std::wstring path = libsDir();
	if (!path.empty()) {
		ok = addAdditionalDllPath(path);
	}

	return ok;
}

LPSTR* commandLineToArgvA(LPCSTR lpCmdLine, INT* pNumArgs)
{
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
		assert(bufLen > 0);
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

} // namespace

#ifdef DEBUG
int main(int argc, char *argv[])
{
	if (!initDllPath()) {
		return EXIT_FAILURE;
	}

	return Core::exec(argc, argv);
}
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	if (!initDllPath()) {
		return EXIT_FAILURE;
	}

	char appPathRaw[MAX_PATH];
	GetModuleFileNameA(nullptr, appPathRaw, MAX_PATH);

	std::string appPath = appPathRaw;
	appPath += " ";
	std::string cmdline = lpCmdLine;
	cmdline.insert(0, appPath);

	int argc = 0;
	LPSTR* argv = commandLineToArgvA(cmdline.c_str(), &argc);

	return Core::exec(argc, argv);
}
#endif // DEBUG


/*
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);
	
	if (!initDllPath()) {
		return EXIT_FAILURE;
	}

	int argc = 0;
	LPSTR* argv = commandLineToArgvA(lpCmdLine, &argc);

	return Core::exec(argc, argv);
}


int main(int argc, char *argv[])
{
	if (!initDllPath()) {
		return EXIT_FAILURE;
	}

	return Core::exec(argc, argv);
}*/

///ENTRY:"_tWinMain" 