#include "event_processor.hpp"

EventProcessor::EventProcessor(
    IntegrityManager& integrityManager,
    AlertManager& alertManager
)
    : integrity(integrityManager),
      alerts(alertManager) {
}

void EventProcessor::processModification() {

    alerts.reportModification();

    if (!integrity.verifyIntegrity()) {
        alerts.reportIntegrityViolation();
    }
}

void EventProcessor::processDeletion() {

    alerts.reportDeletion();
}

void EventProcessor::processMove() {

    alerts.reportMove();
}