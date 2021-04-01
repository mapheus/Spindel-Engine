#pragma once

#include <memory>
#include "Ref.h"

#ifndef SP_PLATFORM_WINDOWS
	#error Spindel only supports Windows.
#endif

// __VA_ARGS__ expansion to get past MSVC "bug"
#define SP_EXPAND_VARGS(x) x


#define BIT(x) (1 << x)
#define SP_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#include "Assert.h"

namespace Spindel {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	using byte = uint8_t;
}