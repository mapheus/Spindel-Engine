#pragma once

#include <memory>
#include "Ref.h"

#ifdef SP_PLATFORM_WINDOWS
	#if SP_DYNAMIC_LINK
		#ifdef SP_BUILD_DLL
			#define SPINDEL_API __declspec(dllexport)
		#else
			#define SPINDEL_API __declspec(dllimport)
		#endif
	#else
		#define SPINDEL_API
	#endif
#else
	#error Spindel only supports Windows.
#endif

#ifdef SP_ENABLE_ASSERTS
	#define SP_ASSERT(x, ...) { if(!(x)) {SP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SP_CORE_ASSERT(x, ...) { if(!(x)) {SP_CORE_WARN("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SP_ASSERT(x, ...)
	#define SP_CORE_ASSERT(x, ...)
#endif
#define BIT(x) (1 << x)
#define SP_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Spindel {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	typename Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	using byte = uint8_t;
}