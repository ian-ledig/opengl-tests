#include "logger.h"
#include <iostream>

Logger::Logger() {
    std::time_t t = std::time(nullptr);
    char mbstr[100];
    if (!std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d", std::localtime(&t))) {
        std::cerr << "Error: Could not find the date for file logging" << std::endl;
    }

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);
    console_sink->set_pattern("[rtvr] [%^%l%$] [%H:%M:%S] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/" + std::string(mbstr) + ".txt", false);
    file_sink->set_level(spdlog::level::trace);
    file_sink->set_pattern("[rtvr] [%^%l%$] [%H:%M:%S] [thread %t] %v");

    _logger = std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list {console_sink, file_sink});
    _logger->set_level(spdlog::level::debug);

    spdlog::flush_every(std::chrono::seconds(5));
}

spdlog::logger& Logger::logger() {
    static Logger __logger;
    return *__logger._logger;
}
