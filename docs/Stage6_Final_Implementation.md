# Stage 6 — Final Implementation & Presentation

## 1. Project Overview

The Anti-Ransomware Canary File Integrity Monitor is a Linux-based cybersecurity prototype designed to detect suspicious activity affecting a protected canary file.

The system monitors the canary file, detects modification, deletion and movement, verifies file integrity using SHA-256, generates security alerts, logs events and communicates security events to a Linux kernel character device driver.

The project is implemented using C++ for the userspace monitoring application and C for the Linux kernel driver.


## 2. Final Architecture

The final system consists of the following major components:

- **Canary Manager** — creates and manages the protected canary file.
- **Filesystem Monitor** — uses Linux `inotify` to detect file activity.
- **Integrity Manager** — calculates and compares SHA-256 hashes.
- **Event Processor** — processes filesystem events and triggers appropriate actions.
- **Alert Manager** — generates alerts, logs events and sends security events to the kernel driver.
- **Event Logger** — records security events with timestamps.
- **Linux Kernel Driver** — provides the `/dev/ransomguard` character-device interface and receives security events from the userspace application.


## 3. Final Implementation

The final implementation provides the following functionality:

1. Creates a protected canary file at `runtime/canary.txt`.
2. Creates an initial SHA-256 integrity baseline.
3. Monitors the canary using Linux `inotify`.
4. Detects modification, deletion and move/rename events.
5. Recalculates the file hash after modification.
6. Generates alerts when suspicious activity or integrity violations are detected.
7. Records security events in `runtime/events.log`.
8. Sends security events to the Linux kernel driver through `/dev/ransomguard`.
9. The kernel driver receives and logs the events using the Linux kernel logging mechanism.


## 4. Final Testing Results

The final prototype was tested at unit, integration and system levels.

The tests confirmed:

- Successful canary file creation.
- Successful SHA-256 baseline generation.
- Detection of canary modification.
- Detection of integrity violations.
- Detection of canary deletion and movement.
- Successful event logging.
- Successful Linux kernel driver loading.
- Successful creation of `/dev/ransomguard`.
- Successful userspace-to-kernel communication.
- Successful kernel-to-userspace communication.
- Successful end-to-end integration between the C++ application and Linux kernel driver.

All documented tests passed during prototype validation.


## 5. Project Outcome

The completed prototype demonstrates a practical host-based approach for detecting suspicious activity using a canary file.

The system combines:

- C++ userspace monitoring.
- Linux filesystem event monitoring.
- SHA-256 integrity verification.
- Security event logging.
- Linux character-device driver integration.

The prototype provides a foundation that can be extended into a more comprehensive host-based ransomware detection and response system.


## 6. Limitations

- The current prototype focuses on a designated canary file.
- The kernel driver primarily provides event reception and logging.
- The prototype requires appropriate permissions for access to the character device.
- Additional hardening and testing would be required for production deployment.

## 7. Future Improvements

- Support multiple canary files.
- Add configurable monitoring paths.
- Improve driver access control.
- Add more detailed kernel-level event handling.
- Improve event reporting and visualization.
- Add automated testing scripts.
- Add stronger incident response and recovery mechanisms.


## 8. Conclusion

The final implementation successfully integrates the C++ userspace anti-ransomware monitor with a Linux kernel character device driver.

The prototype demonstrates canary-file monitoring, SHA-256 integrity verification, security event detection, event logging and userspace-to-kernel communication.

The project provides a working foundation for further development of host-based ransomware detection and response mechanisms.


