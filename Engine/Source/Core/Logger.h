#pragma once

#include <string>

namespace Wraith::Debug
{
	class Logger
	{
	public:
		static void LogDebug(const std::string& msg);
		static void LogInfo(const std::string& msg);
		static void LogTrace(const std::string& msg);
		static void LogWarning(const std::string& msg);
		static void LogError(const std::string& msg);
		static void LogCritical(const std::string& msg);

	private:
		friend class Engine;
		static void Init();
		static void Shutdown();

		static bool HasLogger();
	};
}

#ifdef WRAITH_DEBUG

#define LOG_DEBUG(msg) ::Wraith::Debug::Logger::LogDebug(msg)
#define LOG_INFO(msg) ::Wraith::Debug::Logger::LogInfo(msg)
#define LOG_TRACE(msg) ::Wraith::Debug::Logger::LogTrace(msg)
#define LOG_WARNING(msg) ::Wraith::Debug::Logger::LogWarning(msg)
#define LOG_ERROR(msg) ::Wraith::Debug::Logger::LogError(msg)
#define LOG_CRITICAL(msg) ::Wraith::Debug::Logger::LogCritical(msg)

#else

#define LOG_DEBUG(msg)
#define LOG_INFO(msg)
#define LOG_TRACE(msg)
#define LOG_WARNING(msg)
#define LOG_ERROR(msg)
#define LOG_CRITICAL(msg)

#endif

