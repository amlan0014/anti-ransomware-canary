#include "integrity_manager.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <sstream>

IntegrityManager::IntegrityManager(const std::string& path)
    : filePath(path) {
}

std::string IntegrityManager::calculateHash() const {

    std::ifstream file(filePath, std::ios::binary);

    if (!file) {
        return "";
    }

    SHA256_CTX context;
    SHA256_Init(&context);

    char buffer[4096];

    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        SHA256_Update(
            &context,
            buffer,
            static_cast<std::size_t>(file.gcount())
        );
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_Final(hash, &context);

    std::ostringstream result;

    for (unsigned char byte : hash) {
        result << std::hex
               << std::setw(2)
               << std::setfill('0')
               << static_cast<int>(byte);
    }

    return result.str();
}

bool IntegrityManager::createBaseline() {

    baselineHash = calculateHash();

    if (baselineHash.empty()) {
        return false;
    }

    std::cout << "[INFO] Integrity baseline created.\n";
    std::cout << "[INFO] SHA-256: " << baselineHash << "\n";

    return true;
}

bool IntegrityManager::verifyIntegrity() const {

    std::string currentHash = calculateHash();

    if (currentHash.empty()) {
        return false;
    }

    return currentHash == baselineHash;
}