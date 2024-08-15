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
//#include <iosfwd>
#include <sstream>
#include <new.h> // use new 和 bad_alloc
#include <eh.h>
#include <cstdlib> // use std::malloc
#include <csignal> 
#include <exception>
#include <iostream>
#include <util/cpHelper.h>

//#include <unistd.h>

using namespace std;
//using namespace crashpad;
 
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

#
int func(bool isCrash)
{
	if (isCrash)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		crash_fun();
		//cpHelper cpHelperObj;
		//cpHelperObj.crash_fun();
	}
	return 1;
}

#if defined(LC_WIN)
// set SEH to cxx exception
void my_se_translator_filter(unsigned int code, EXCEPTION_POINTERS* pExp)
{
	switch (code)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		break;
	}

	std::stringstream str;
	str << "SEH exception of type: " << code;
	throw;
}
#endif

void seg_fault_handler(int sig)
{
	switch (sig)
	{
	case SIGSEGV:
		std::cerr << "illegal storage access..." << std::endl;
		throw;
		//throw Base::AccessViolation("***");
		break;
	case SIGABRT:
		std::cerr << "abnormal program termination..." << std::endl;
		//throw Base::AbnormalProgramTermination("***");
		break;
	default:
		std::cerr << "unknown error occurred..." << std::endl;
		break;
	}
}

void unhandled_exception_handler()
{
	std::cerr << "terminating..." << std::endl;
}

void unexception_error_handler()
{
	std::cerr << "unexpected error occured..." << std::endl;
}

void InstallExceptionHandler()
{
	// install our own handler
#ifdef _MSC_VER
	//_set_new_handler();
	_set_new_mode(1); // throw bad_alloc while malloc failed
#endif

	// 
#ifdef _MSC_VER
	std::signal(SIGSEGV, seg_fault_handler);
	std::signal(SIGABRT, seg_fault_handler); 
	std::set_terminate(unhandled_exception_handler);
	//std::set_unexcepted(unexception_error_handler);

#define _SE_TRANSLATOR_
#if defined(_SE_TRANSLATOR_)
	_set_se_translator(my_se_translator_filter);
#endif

#elif defined(_OS_LINUX)
	std::signal(SIGSEGV, );
#endif

}

int main()
{ 
	InstallExceptionHandler();

    std::cout << "Hello World!\n";
	//QString appDirPath = QCoreApplication::applicationDirPath();
	//QString dbPath = appDirPath + "/database";
	//QString dmpPath = appDirPath + "/database/reports";//+ "/database/reports";
	//QString handlerPath = "D:/Projects/Proj_Basic_proj/build_cp/cp_cxx14/crashpad/x64/release/crashpad_handler.exe";
	//handlerPath.toStdWString();

	std::string appDir = GetExecutablePath();
	std::string dmpDir = appDir + "\\database\\reports";
	std::string dbPath = appDir + "\\database";
	std::wstring dbDir = string_to_wstring(dbPath);// = dbPath.toStdWString();

	std::cout << "当前程序路径 %s：\n" << appDir << std::endl;

#ifdef _DEBUG
	std::wstring handlerDir = L"C:/Users/ibe/Projects/Proj_Basic_proj/build_cp_cxx14-v140-240809/cp_cxx14/crashpad/x64/release/crashpad_handler.exe";
#else
	std::wstring handlerDir = L"C:/Users/ibe/Projects/Proj_Basic_proj/build_cp_cxx14-v140-240809/cp_cxx14/crashpad/x64/release/crashpad_handler.exe";
#endif

	crashpadInstance.setDBPath(dbDir)
		->setHandlerPath(handlerDir)
		->setDumpPath(dmpDir)
		->setUploadUrl("http://172.30.100.21:28080/crash/upload_mini_dump")
		->initCrashpad();

	//const std::string url("http://172.30.100.21:28080/crash/upload_mini_dump");
	 
	try
	{
		//std::packaged_task<int(bool)> pkTask(func);
		////std::packaged_task<int(cpHelper&,bool)> pkTask(&cpHelper::func);
		//std::future<int> fut = pkTask.get_future();
		//std::thread(std::move(pkTask), true).detach();
		//int val = fut.get();

		const auto p = static_cast<int*>(nullptr);
		*p = 1;
		//func(true);
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