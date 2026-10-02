#include "alert_manager.hpp"

#include <iostream>

AlertManager::AlertManager(EventLogger& eventLogger)
    : logger(eventLogger) {
}

void AlertManager::reportModification() {

    std::cout << "[ALERT] Canary file modified!\n";

    logger.log("Canary file modification detected.");
}

void AlertManager::reportIntegrityViolation() {

    std::cout << "[CRITICAL] Integrity violation detected!\n";

    logger.log("CRITICAL: Canary integrity violation detected.");
}

void AlertManager::reportDeletion() {

    std::cout << "[CRITICAL] Canary file deleted!\n";

    logger.log("CRITICAL: Canary file deleted.");
}

void AlertManager::reportMove() {

    std::cout << "[CRITICAL] Canary file moved or renamed!\n";

    logger.log("CRITICAL: Canary file moved or renamed.");
}