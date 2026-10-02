#ifndef INTEGRITY_MANAGER_HPP
#define INTEGRITY_MANAGER_HPP

#include <string>

class IntegrityManager {
public:
    explicit IntegrityManager(const std::string& filePath);

    std::string calculateHash() const;
    bool createBaseline();
    bool verifyIntegrity() const;

private:
    std::string filePath;
    std::string baselineHash;
};

#endif