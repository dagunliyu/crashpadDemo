/*
* @Description: 
* @Author: lhc
* @Date: 2024-07-15 13:57:04
* @LastEditTime: 2024-07-15 14:00:47
* @LastEditors: lhc
* @Reference: 
*/

#include "PreCompiled.h"
#include <filesystem>
#include <iostream>
// #include "client/crash_report_database.h"
// #include "client/crashpad_client.h"
// #include "client/settings.h"
// #include "base/files/file_path.h" //! mini_chromium
#include <crashpadHandler.h>
#include <windows.h>
#include <xlocbuf>
#include <locale>
#include <codecvt>
#include <string>
#include <thread>
#include <utility>
#include <future>
#include <vector>
#include <util/cpHelper.h>

//#include <unistd.h>

using namespace std;
//using namespace crashpad;


//StringType getExecutableDir() 
//{
//	HMODULE hModule = GetModuleHandleW(NULL);
//	WCHAR path[MAX_PATH];
//	DWORD retVal = GetModuleFileNameW(hModule, path, MAX_PATH);
//	if (retVal == 0) return NULL;
//
//	wchar_t* lastBackslash = wcsrchr(path, '\\');
//	if (lastBackslash == NULL) return NULL;
//	*lastBackslash = 0;
//
//	return path;
//}
//std::string getExeDirectory()
//{
//	wchar_t path[MAX_PATH];
//	if (!GetModuleFileNameW(NULL, path, MAX_PATH))
//	{
//		// Handle error
//		return "";
//	}
//
//	// Convert wide string to narrow string
//	const size_t len = wcslen(path);
//	std::string strPath(len, '\0');
//	std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(path, path + len, '?', &strPath[0]);
//
//	// Remove the filename part to leave only the directory
//	const char* lastSlash = strrchr(strPath.c_str(), '\\');
//	if (lastSlash != nullptr)
//	{
//		strPath.erase(lastSlash - strPath.begin());
//	}
//
//	return strPath;
//}
 
void crash_fun()
{    
    const auto p = static_cast<int*>(nullptr);
    *p = 1;
}

std::wstring string_to_wstring(const std::string& str) 
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.from_bytes(str);
}

std::string GetExecutablePath() 
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string fullPath = buffer;
	size_t pos = fullPath.find_last_of("\\/");
	return fullPath.substr(0, pos);
}

int func(bool isCrash)
{
	if (isCrash)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		//crash_fun();
		cpHelper cpHelperObj;
		cpHelperObj.crash_fun();
	}
	
	return 1;
}

int main()
{ 
    //std::cout << "当前程序路径：" << path << std::endl;
    std::cout << "Hello World!\n";
	//QString appDirPath = QCoreApplication::applicationDirPath();
	//QString dbPath = appDirPath + "/database";
	//QString dmpPath = appDirPath + "/database/reports";//+ "/database/reports";
	//QString handlerPath = "D:/Projects/Proj_Basic_proj/build_cp/cp_cxx14/crashpad/x64/release/crashpad_handler.exe";

	std::string appDir = GetExecutablePath();
	std::string dmpDir = appDir + "\\database\\reports";
	std::string dbPath = appDir + "\\database";
	std::wstring dbDir = string_to_wstring(dbPath);// = dbPath.toStdWString();
	std::wstring handlerDir = L"C:/Users/ibe/Projects/Proj_Basic_proj/build_cp_cxx14/cp_cxx14-240806/crashpad/x64/release/crashpad_handler.exe";
	// handlerPath.toStdWString();
	//L"D:/Projects/Proj_Basic_proj/build_cp/cp_cxx14/crashpad/x64/release/crashpad_handler.exe"
	//L"C:/Users/ibe/Projects/Proj_Basic_proj/build_cp_cxx14/cp_cxx14-240806/crashpad/x64/release/crashpad_handler.exe"

	crashpadInstance.setDBPath(dbDir)
		->setHandlerPath(handlerDir)
		->setDumpPath(dmpDir)
		->setUploadUrl("http://192.168.24.32:18080/crash/upload_mini_dump")
		->initCrashpad();
	
	//"http://192.168.24.32:18080/crash/upload_mini_dump"
	//"http://127.0.0.1:18080/upload_mini_dump"

	 
	try
	{
		std::packaged_task<int(bool)> pkTask(func);
		//std::packaged_task<int(cpHelper&,bool)> pkTask(&cpHelper::func);
		std::future<int> fut = pkTask.get_future();

		std::thread(std::move(pkTask), true).detach();
		int val = fut.get();
	}
	catch (const std::exception&)
	{
		std::cout << "std::exception catch" << std::endl;
	}
	catch (...)
	{
		std::cout << "..." << std::endl;
	}

	/////////////////////////////////////////////////////
	//! test async
	std::vector<std::shared_future<int>> v;
	std::shared_future<int> f = std::async(std::launch::async, 
		[](int a, int b) 
		{
			return a + b; 
		}, 
		2, 3);

	v.push_back(f);
	std::cout << "The shared_future result is " << v[0].get() << std::endl;

	//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	//crash_fun();
}