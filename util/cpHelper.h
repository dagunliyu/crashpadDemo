
#pragma once

//#include "singletone/singleton.h"
#include <string>


class cpHelperPrivate;

class cpHelperExport cpHelper
{
    //friend class Singleton<cpHelper>;
public:
    static std::string version();
	    
	int func(bool isCrash);
	void crash_fun();
	bool initCpHelper();

    std::string uploadUrl() const;
    std::string dumpPath() const;

	cpHelper* setDBPath(const std::wstring& path);
	cpHelper* setHandlerPath(const std::wstring& path);

	cpHelper* setDumpPath(const std::string& path);
	cpHelper* setUploadUrl(const std::string& url);

//private:
	cpHelper();
	~cpHelper();

    cpHelperPrivate* d;
};

// #define crashpadInstance Singleton<cpHelper>::instance()
