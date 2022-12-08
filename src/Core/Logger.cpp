//
// Log.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 08/12/2022.
//

#include "wrpch.h"

#include "Wraith/Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

// [Log Type] [Date] [File:Line] <message>
#define LOGGER_PATTERN "%^[%l] [%H:%M:%S] [%s:%#]%$ %v"

namespace Wraith {

    void Logger::Init() {
        const auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sink->set_pattern(LOGGER_PATTERN);

        std::vector<spdlog::sink_ptr> sinks{sink};
        const auto logger = std::make_shared<spdlog::logger>(WR_LOGGER_NAME, sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(logger);
    }

    void Logger::Shutdown() {
        spdlog::shutdown();
    }

    bool Logger::HasLogger() {
        return spdlog::get(WR_LOGGER_NAME) != nullptr;
    }

}