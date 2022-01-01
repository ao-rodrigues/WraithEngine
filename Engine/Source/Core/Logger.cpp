#include "Logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace Wraith::Debug
{
	constexpr auto LOGGER_NAME =  "WraithLogger";

	void Logger::Init()
	{
		const auto sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
		sink->set_pattern("%^[%l] [%H:%M:%S]%$ %v");

		std::vector<spdlog::sink_ptr> sinks{sink};
		const auto logger = std::make_shared<spdlog::logger>(LOGGER_NAME, sinks.begin(), sinks.end());
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(logger);
	}

	void Logger::Shutdown()
	{
		spdlog::shutdown();
	}

	bool Logger::HasLogger()
	{
		return spdlog::get(LOGGER_NAME) != nullptr;
	}

	void Logger::LogDebug(const std::string& msg)
	{
		if (!HasLogger()) return;
		spdlog::get(LOGGER_NAME)->debug(msg);
	}

	void Logger::LogInfo(const std::string& msg)
	{
		if (!HasLogger()) return;
		spdlog::get(LOGGER_NAME)->info(msg);
	}

	void Logger::LogTrace(const std::string& msg)
	{
		if (!HasLogger()) return;
		spdlog::get(LOGGER_NAME)->trace(msg);
	}

	void Logger::LogWarning(const std::string& msg)
	{
		if (!HasLogger()) return;
		spdlog::get(LOGGER_NAME)->warn(msg);
	}

	void Logger::LogError(const std::string& msg)
	{
		if (!HasLogger()) return;
		spdlog::get(LOGGER_NAME)->error(msg);
	}

	void Logger::LogCritical(const std::string& msg)
	{
		if (!HasLogger()) return;
		spdlog::get(LOGGER_NAME)->critical(msg);
	}
}
