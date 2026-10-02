#ifndef ALERT_MANAGER_HPP
#define ALERT_MANAGER_HPP

#include <string>

#include "event_logger.hpp"

class AlertManager {
public:
    explicit AlertManager(EventLogger& logger);

    void reportModification();
    void reportIntegrityViolation();
    void reportDeletion();
    void reportMove();

private:
    EventLogger& logger;
};

#endif