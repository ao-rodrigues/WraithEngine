#include "wrpch.h"
#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace Wraith::Debug
{
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

	bool Logger::HasLogger() const
	{
		return spdlog::get(LOGGER_NAME) != nullptr;
	}
}
