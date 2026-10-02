#ifndef EVENT_PROCESSOR_HPP
#define EVENT_PROCESSOR_HPP

#include "alert_manager.hpp"
#include "integrity_manager.hpp"

class EventProcessor {
public:
    EventProcessor(
        IntegrityManager& integrity,
        AlertManager& alerts
    );

    void processModification();
    void processDeletion();
    void processMove();

private:
    IntegrityManager& integrity;
    AlertManager& alerts;
};

#endif