#include "filesystem_monitor.hpp"

#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>

FileSystemMonitor::FileSystemMonitor(
    const std::string& monitoredPath,
    EventProcessor& eventProcessor
)
    : path(monitoredPath),
      processor(eventProcessor) {
}

void FileSystemMonitor::start() {

    int fd = inotify_init1(0);

    if (fd < 0) {
        std::cerr << "[ERROR] Failed to initialize inotify.\n";
        return;
    }

    int watch = inotify_add_watch(
        fd,
        path.c_str(),
        IN_MODIFY | IN_DELETE_SELF | IN_MOVE_SELF
    );

    if (watch < 0) {
        std::cerr << "[ERROR] Failed to watch canary file.\n";
        close(fd);
        return;
    }

    std::cout << "[INFO] Monitoring: " << path << "\n";
    std::cout << "[INFO] Waiting for filesystem events...\n";

    char buffer[4096];

    while (true) {

        int length = read(fd, buffer, sizeof(buffer));

        if (length <= 0) {
            break;
        }

        int position = 0;

        while (position < length) {

            auto* event =
                reinterpret_cast<struct inotify_event*>(
                    &buffer[position]
                );

            if (event->mask & IN_MODIFY) {
                processor.processModification();
            }

            if (event->mask & IN_DELETE_SELF) {
                processor.processDeletion();

                close(fd);
                return;
            }

            if (event->mask & IN_MOVE_SELF) {
                processor.processMove();

                close(fd);
                return;
            }

            position += sizeof(struct inotify_event) + event->len;
        }
    }

    close(fd);
}