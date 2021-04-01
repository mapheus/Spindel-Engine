#pragma once

#define SP_ENABLE_ASSERTS

#ifdef SP_ENABLE_ASSERTS
	#define SP_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { SP_ERROR("Assertion Failed"); __debugbreak(); } }
	#define SP_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { SP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

	#define SP_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
	#define SP_GET_ASSERT_MACRO(...) SP_EXPAND_VARGS(SP_ASSERT_RESOLVE(__VA_ARGS__, SP_ASSERT_MESSAGE, SP_ASSERT_NO_MESSAGE))


	#define SP_ASSERT(...) SP_EXPAND_VARGS( SP_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
	#define SP_CORE_ASSERT(...) SP_EXPAND_VARGS( SP_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )

#else
	#define SP_ASSERT(x, ...)
	#define SP_CORE_ASSERT(x, ...)
#endif