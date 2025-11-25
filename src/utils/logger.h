#pragma once

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>

class Logger {
private:
    std::shared_ptr<spdlog::logger> _logger;

    Logger();

public:
    static spdlog::logger& logger();
};
