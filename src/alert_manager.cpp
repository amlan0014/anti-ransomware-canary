#include "alert_manager.hpp"

#include <fcntl.h>
#include <iostream>
#include <unistd.h>

namespace {
    const char* DRIVER_DEVICE = "/dev/ransomguard";

    void sendToDriver(const std::string& event) {
        int fd = open(DRIVER_DEVICE, O_WRONLY);

        if (fd < 0) {
            std::cerr << "[WARNING] Could not open /dev/ransomguard.\n";
            return;
        }

        write(fd, event.c_str(), event.size());
        close(fd);
    }
}

AlertManager::AlertManager(EventLogger& logger)
    : logger(logger) {
}

void AlertManager::reportModification() {
    std::cout << "[ALERT] Canary file modified!\n";

    logger.log("Canary file modification detected.");

    sendToDriver("CANARY_MODIFIED");
}

void AlertManager::reportIntegrityViolation() {
    std::cout << "[CRITICAL] Integrity violation detected!\n";

    logger.log("CRITICAL: Canary integrity violation detected.");

    sendToDriver("INTEGRITY_VIOLATION");
}

void AlertManager::reportDeletion() {
    std::cout << "[CRITICAL] Canary file deleted!\n";

    logger.log("CRITICAL: Canary file deleted.");

    sendToDriver("CANARY_DELETED");
}

void AlertManager::reportMove() {
    std::cout << "[CRITICAL] Canary file moved or renamed!\n";

    logger.log("CRITICAL: Canary file moved or renamed.");

    sendToDriver("CANARY_MOVED");
}