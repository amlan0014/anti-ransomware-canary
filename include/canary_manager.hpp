#ifndef CANARY_MANAGER_HPP
#define CANARY_MANAGER_HPP

#include <string>

class CanaryManager {
public:
    CanaryManager(const std::string& canaryPath);

    bool createCanary();
    bool canaryExists() const;
    std::string getCanaryPath() const;

private:
    std::string canaryPath;
};

#endif