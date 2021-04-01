#pragma once

#include "Spindel/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Spindel {
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define SP_CORE_TRACE(...) ::Spindel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SP_CORE_INFO(...) ::Spindel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SP_CORE_WARN(...) ::Spindel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SP_CORE_ERROR(...) ::Spindel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SP_CORE_FATAL(...) ::Spindel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define SP_TRACE(...) ::Spindel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SP_INFO(...) ::Spindel::Log::GetClientLogger()->info(__VA_ARGS__)
#define SP_WARN(...) ::Spindel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SP_ERR(...) ::Spindel::Log::GetClientLogger()->error(__VA_ARGS__)
#define SP_FATAL(...) ::Spindel::Log::GetClientLogger()->fatal(__VA_ARGS__)