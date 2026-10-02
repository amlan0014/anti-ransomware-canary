#ifndef FILESYSTEM_MONITOR_HPP
#define FILESYSTEM_MONITOR_HPP

#include <string>

#include "event_processor.hpp"

class FileSystemMonitor {
public:
    FileSystemMonitor(
        const std::string& path,
        EventProcessor& processor
    );

    void start();

private:
    std::string path;
    EventProcessor& processor;
};

#endif