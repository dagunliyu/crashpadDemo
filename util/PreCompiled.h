
#pragma once

// only when dllexport is added, the cpHelper.lib will be generated
#if defined(WIN64) || defined(WIN32)
	#define cpHelperExport __declspec(dllexport)
#else
	#define cpHelperExport
#endif
//
//#if defined(WIN64) || defined(WIN32)
//#define cpHelperExport __declspec(dllexport)
//#else
//#define cpHelperExport
//#endif