
#pragma once

#include "singletone/singleton.h"
#include <string>

class crashpadHandlerPrivate;

class crashpadHandler
{
    friend class Singleton<crashpadHandler>;
public:
    static std::string version();
	    
	bool initCrashpad();

    std::string uploadUrl() const;
    std::string dumpPath() const;

	crashpadHandler* setDBPath(const std::wstring& path);
	crashpadHandler* setHandlerPath(const std::wstring& path);

	crashpadHandler* setDumpPath(const std::string& path);
	crashpadHandler* setUploadUrl(const std::string& url);

private:
	crashpadHandler();
	~crashpadHandler();

    crashpadHandlerPrivate* d;
};

#define crashpadInstance Singleton<crashpadHandler>::instance()
