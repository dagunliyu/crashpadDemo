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

bool initializeCrashpad()
{    
	std::string exeDir = GetExecutablePath();
    using namespace crashpad;    
    std::map<std::string, std::string> annotations;    
    std::vector<std::string> arguments;
        arguments.push_back("--no-rate-limit");    

        //L"F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty/crashpad/bin/crashpad_handler.exe";
    //const std::wstring crash_dir_path = L"/";
    //D:\Projects\Proj_Coding_Alog_Interview_Recruit\Proj_Basic_proj\build_crashpadDemo\Release
    //F: / Proj_Coding_Alog_Interview_Recruit / Proj_Basic / Proj_Optimize / Proj_CrashRPT / crashpadDemo / thirdParty / crashpad / bin /
	const std::wstring crash_dir_path = string_to_wstring(GetExecutablePath()); // L"D:/Projects/Proj_Coding_Alog_Interview_Recruit/Proj_Basic_proj/build_crashpadDemo/Release/";
    const base::FilePath db(crash_dir_path);    

	//F:\Proj_Coding_Alog_Interview_Recruit\Proj_Basic\Proj_Optimize\Proj_CrashRPT\crashpadDemo\thirdParty
	//F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty
	//const std::wstring handler_exe_path = L"/thirdParty/crashpad/bin/crashpad_handler.exe";
    // F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty/crashpad/bin/crashpad_handler.exe
    //D:\Projects\Proj_Coding_Alog_Interview_Recruit\Proj_Basic_proj\build_crashpad\crashpad_depot2\crashpad\x64\debug
	const std::wstring handler_exe_path = string_to_wstring(exeDir + "\\crashpad_handler.exe");

#ifdef _DEBUG
	std::wstring handlerDir = L"C:/Users/ibe/Projects/Proj_Basic_proj/build_cp_cxx14-v140-240809/cp_cxx14/crashpad/x64/debug/crashpad_handler.exe";
#else
	std::wstring handlerDir = L"C:/Users/ibe/Projects/Proj_Basic_proj/build_cp_cxx14-v140-240809/cp_cxx14/crashpad/x64/release/crashpad_handler.exe";
#endif

	//L"D:/Projects/Proj_Coding_Alog_Interview_Recruit/Proj_Basic_proj/build_crashpad/crashpad_depot2/crashpad/x64/debug/crashpad_handler.exe";
    const base::FilePath handler(handlerDir);

    const std::unique_ptr<CrashReportDatabase> database =
            crashpad::CrashReportDatabase::Initialize(db);
    if (database == nullptr || database->GetSettings() == NULL)
    {        
        return false;
    }
    else
	{
		database->GetSettings()->SetUploadsEnabled(true);
    }

	CrashpadClient client;
	//http://127.0.0.1:8000
	//http://192.168.24.32:18080/submit
	// http://192.168.24.32:18080/crash/upload_mini_dump
	// http://172.30.100.21:28080/crash/upload_mini_dump
    const std::string url("http://172.30.100.21:28080/crash/upload_mini_dump");    


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