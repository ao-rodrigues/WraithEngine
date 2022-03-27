#pragma once

#include <spdlog/spdlog.h>

#include "Core/Singleton.h"

namespace Wraith::Debug
{

#define LOGGER_NAME "WraithLogger"

	class Logger final : public Singleton<Logger>
	{
	public:
		void Init();
		void Shutdown();
		bool HasLogger() const;
	};

#define WRAITH_LOGGER ::Wraith::Debug::Logger::Instance()

#ifdef WR_CONFIG_DEBUG

#define WR_LOG_DEBUG(...) if (WRAITH_LOGGER.HasLogger()) { spdlog::get(LOGGER_NAME)->debug(__VA_ARGS__); }
#define WR_LOG_INFO(...) if (WRAITH_LOGGER.HasLogger()) { spdlog::get(LOGGER_NAME)->info(__VA_ARGS__); }
#define WR_LOG_TRACE(...) if (WRAITH_LOGGER.HasLogger()) { spdlog::get(LOGGER_NAME)->trace(__VA_ARGS__); }
#define WR_LOG_WARNING(...) if (WRAITH_LOGGER.HasLogger()) { spdlog::get(LOGGER_NAME)->warn(__VA_ARGS__); }
#define WR_LOG_ERROR(...) if (WRAITH_LOGGER.HasLogger()) { spdlog::get(LOGGER_NAME)->error(__VA_ARGS__); }
#define WR_LOG_FATAL(...) if (WRAITH_LOGGER.HasLogger()) { spdlog::get(LOGGER_NAME)->critical(__VA_ARGS__); }

#else

#define WR_LOG_DEBUG(...)
#define WR_LOG_INFO(...)
#define WR_LOG_TRACE(...)
#define WR_LOG_WARNING(...)
#define WR_LOG_ERROR(...)
#define WR_LOG_FATAL(...)

#endif

}
