#include "canary_manager.hpp"

#include <filesystem>
#include <fstream>

CanaryManager::CanaryManager(const std::string& path)
    : canaryPath(path) {
}

bool CanaryManager::createCanary() {
    try {
        std::filesystem::path filePath(canaryPath);

        std::filesystem::create_directories(filePath.parent_path());

        if (std::filesystem::exists(filePath)) {
            return true;
        }

        std::ofstream file(canaryPath);

        if (!file.is_open()) {
            return false;
        }

        file << "ANTI_RANSOMWARE_CANARY\n";
        file.close();

        return true;
    }
    catch (...) {
        return false;
    }
}

bool CanaryManager::canaryExists() const {
    return std::filesystem::exists(canaryPath);
}

std::string CanaryManager::getCanaryPath() const {
    return canaryPath;
}