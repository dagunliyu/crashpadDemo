/*
 * @Description: 
 * @Author: lhc
 * @Date: 2024-07-15 13:57:04
 * @LastEditTime: 2024-07-15 14:00:47
 * @LastEditors: lhc
 * @Reference: 
 */
#include <filesystem>
#include <iostream>
#include "client/crash_report_database.h"
#include "client/crashpad_client.h"
#include "client/settings.h"
#include "base/files/file_path.h" //! mini_chromium
#include <windows.h>


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

bool initializeCrashpad()
{    
    using namespace crashpad;    
    std::map<std::string, std::string> annotations;    
    std::vector<std::string> arguments;
        arguments.push_back("--no-rate-limit");    

        //L"F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty/crashpad/bin/crashpad_handler.exe";
    //const std::wstring crash_dir_path = L"/";    
    const std::wstring crash_dir_path = L"F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty/crashpad/bin/";
    const base::FilePath db(crash_dir_path);    

	//F:\Proj_Coding_Alog_Interview_Recruit\Proj_Basic\Proj_Optimize\Proj_CrashRPT\crashpadDemo\thirdParty
	//F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty
	//const std::wstring handler_exe_path = L"/thirdParty/crashpad/bin/crashpad_handler.exe";
	const std::wstring handler_exe_path = L"F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty/crashpad/bin/crashpad_handler.exe";
    const base::FilePath handler(handler_exe_path);

    //const std::unique_ptr<CrashReportDatabase> database = crashpad::CrashReportDatabase::Initialize(db);
    //if (database == nullptr || database->GetSettings() == NULL)
    //{        
    ////return false;
    //}
    //else
    //{
    ////database->GetSettings()->SetUploadsEnabled(true);
    //}

	CrashpadClient client;

    const std::string url("http://127.0.0.1:8000");    

    bool ret = client.StartHandler(handler,
            db,
            db,
            url,
            annotations,
            arguments,        
            true,        
            true);    
    if (ret == false)
    {        
        return false;
    }

    ret = client.WaitForHandlerStart(INFINITE);    
    if (ret == false)
    {
        return false;
    }    

    return true;
}

void crash_fun()
{    
    const auto p = static_cast<int*>(nullptr);
    *p = 1;
}

int main()
{ 
    //std::cout << "当前程序路径：" << path << std::endl;
    std::cout << "Hello World!\n";
    
    initializeCrashpad();//程序运行前初始化崩溃时生成dmp文件

    crash_fun();
}