//
// Logger.h
// WraithEngine
//
// Created by Andre Rodrigues on 08/12/2022.
//

#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>

namespace Wraith {

    class Logger {
    public:
        static void Init();
        static void Shutdown();
        static bool HasLogger();
    };

}

#define WR_LOGGER_NAME "WraithLogger"

#ifdef WR_CONFIG_DEBUG

#define WR_LOG_DEBUG(...)       SPDLOG_LOGGER_DEBUG(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_LOG_INFO(...)        SPDLOG_LOGGER_INFO(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_LOG_TRACE(...)       SPDLOG_LOGGER_TRACE(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_LOG_WARNING(...)     SPDLOG_LOGGER_WARN(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_LOG_ERROR(...)       SPDLOG_LOGGER_ERROR(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_LOG_FATAL(...)       SPDLOG_LOGGER_CRITICAL(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);

#else

#define WR_LOG_DEBUG(...)
#define WR_LOG_INFO(...)
#define WR_LOG_TRACE(...)
#define WR_LOG_WARNING(...)
#define WR_LOG_ERROR(...)
#define WR_LOG_FATAL(...)

#endif

#define WR_RELEASE_LOG_DEBUG(...)           SPDLOG_LOGGER_DEBUG(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_RELEASE_LOG_INFO(...)            SPDLOG_LOGGER_INFO(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_RELEASE_LOG_TRACE(...)           SPDLOG_LOGGER_TRACE(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_RELEASE_LOG_WARNING(...)         SPDLOG_LOGGER_WARNING(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_RELEASE_LOG_ERROR(...)           SPDLOG_LOGGER_ERROR(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);
#define WR_RELEASE_LOG_FATAL(...)           SPDLOG_LOGGER_FATAL(spdlog::get(WR_LOGGER_NAME), __VA_ARGS__);