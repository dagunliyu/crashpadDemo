
#pragma once

#if defined(WIN64) || defined(WIN32)
	#define cpHelperExport __declspec(dllimport)
#else
	#define cpHelperExport
#endif
