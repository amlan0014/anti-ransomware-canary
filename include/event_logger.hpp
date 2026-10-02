#ifndef EVENT_LOGGER_HPP
#define EVENT_LOGGER_HPP

#include <string>

class EventLogger {
public:
    explicit EventLogger(const std::string& logPath);

    void log(const std::string& message);

private:
    std::string logPath;
};

#endif