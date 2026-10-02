#include "event_logger.hpp"

#include <fstream>
#include <iostream>
#include <ctime>

EventLogger::EventLogger(const std::string& path)
    : logPath(path) {
}

void EventLogger::log(const std::string& message) {

    std::ofstream logFile(logPath, std::ios::app);

    if (!logFile) {
        std::cerr << "[ERROR] Unable to open log file.\n";
        return;
    }

    std::time_t currentTime = std::time(nullptr);

    logFile << "[" << std::ctime(&currentTime) << "] "
            << message << "\n";
}