#include <iostream>

#include "alert_manager.hpp"
#include "canary_manager.hpp"
#include "event_logger.hpp"
#include "event_processor.hpp"
#include "filesystem_monitor.hpp"
#include "integrity_manager.hpp"

int main() {

    const std::string canaryPath = "runtime/canary.txt";
    const std::string logPath = "runtime/events.log";

    std::cout << "====================================\n";
    std::cout << " Anti-Ransomware Canary Monitor\n";
    std::cout << "====================================\n";

    CanaryManager canary(canaryPath);

    if (!canary.createCanary()) {
        std::cerr << "[ERROR] Failed to create canary.\n";
        return 1;
    }

    std::cout << "[INFO] Canary file ready.\n";
    std::cout << "[INFO] Path: "
              << canary.getCanaryPath() << "\n";

    IntegrityManager integrity(canaryPath);

    if (!integrity.createBaseline()) {
        std::cerr << "[ERROR] Failed to create integrity baseline.\n";
        return 1;
    }

    EventLogger logger(logPath);

    AlertManager alerts(logger);

    EventProcessor processor(
        integrity,
        alerts
    );

    FileSystemMonitor monitor(
        canaryPath,
        processor
    );

    monitor.start();

    return 0;
}