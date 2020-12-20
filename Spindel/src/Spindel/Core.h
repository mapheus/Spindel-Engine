#pragma once

#ifdef SP_PLATFORM_WINDOWS
	#ifdef SP_BUILD_DLL
		#define SPINDEL_API __declspec(dllexport)
	#else
		#define SPINDEL_API __declspec(dllimport)
	#endif
#else
	#error Spindel only supports Windows.
#endif