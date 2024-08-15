
#include "crashpadHandler.h"
#include "client/crash_report_database.h"
#include "client/crashpad_client.h"
#include "client/settings.h"

#define CRASHPAD_VERSION

class crashpadHandlerPrivate
{
public:
    std::string dumpPath; 
	std::wstring dbPath;
	std::wstring handlerPath;
	std::string uploadUrl;
};

//------------------------------------------------------------------------------
std::string crashpadHandler::version()
{
	return std::string();
    //return QString("%1.%2.%3").arg(
    //    QString::number((CRASHPAD_VERSION >> 16) & 0xff),
    //    QString::number((CRASHPAD_VERSION >> 8) & 0xff),
    //    QString::number(CRASHPAD_VERSION & 0xff));
}

crashpadHandler::crashpadHandler() :
    d(new crashpadHandlerPrivate())
{
}

crashpadHandler::~crashpadHandler()
{
    delete d;
}

crashpadHandler* crashpadHandler::setHandlerPath(const std::wstring& path)
{
	d->handlerPath = path;
	return this;
}

crashpadHandler* crashpadHandler::setDumpPath(const std::string& path)
{
	d->dumpPath = path;
	return this;
}

std::string crashpadHandler::uploadUrl() const
{
    return d->uploadUrl;
}


std::string crashpadHandler::dumpPath() const
{
	return d->dumpPath;
}

crashpadHandler* crashpadHandler::setUploadUrl(const std::string &urlstr)
{
	//! TODO: check valid of url
    d->uploadUrl = urlstr;
	return this;
}


bool crashpadHandler::initCrashpad()
{
	using namespace crashpad;
	std::map<std::string, std::string> annotations;
	annotations.emplace("IBEVersionMajor", "5");
	annotations.emplace("IBEVersionMinor", "0");

#ifdef _DEBUG
	annotations.emplace("IBEVersionName", "Test_Debug");
#else
	annotations.emplace("IBEVersionName", "Test_Release");
#endif
	annotations.emplace("IBEVersionMain", "V2024R1");
	annotations.emplace("IBEVersionSmall", "C00106.1");
	annotations.emplace("IBEVersionDate", "0626");
	annotations.emplace("IBERevision", "20240724");
	annotations.emplace("IBERevisionDate", "2024/07/23 12:07:30");
	annotations.emplace("IBERepositoryURL", "");
	annotations.emplace("IBERepositoryHash", "b2159db0dcae7c8b3681bd4180895f52a8ec1ca9");
	annotations.emplace("IBERepositoryBranch", "release/SimdroidEC_5.0_0730");

	std::vector<std::string> arguments;
	arguments.push_back("--no-rate-limit");

	//L"F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty/crashpad/bin/crashpad_handler.exe";
	//const std::wstring crash_dir_path = L"/";    
	//const std::wstring crash_dir_path = L"F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty/crashpad/bin/";
	
	if (d->dumpPath.empty())
	{
		return false;
	}
	const std::wstring crash_dir_path = d->dbPath;
	const base::FilePath db(crash_dir_path);

	//L"F:/Proj_Coding_Alog_Interview_Recruit/Proj_Basic/Proj_Optimize/Proj_CrashRPT/crashpadDemo/thirdParty/crashpad/bin/crashpad_handler.exe"
	
	if (d->handlerPath.empty())
	{
		return false;
	}
	const std::wstring handler_exe_path = d->handlerPath;
	const base::FilePath handler(handler_exe_path);

	const std::unique_ptr<CrashReportDatabase> database = crashpad::CrashReportDatabase::Initialize(db);

	if (database == nullptr || database->GetSettings() == NULL)
	{
		return false;
	}
	else
	{
		database->GetSettings()->SetUploadsEnabled(true);
	}

	CrashpadClient client;

	//const std::string url("http://127.0.0.1:8000");
	const std::string url = d->uploadUrl;

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

crashpadHandler* crashpadHandler::setDBPath(const std::wstring& path)
{
	this->d->dbPath = path;
	return this;
}
