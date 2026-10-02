# Stage 4 — Initial Implementation & Prototype

## 1. Implementation Objective

The objective of the initial implementation was to develop a working prototype of the Host-Based Anti-Ransomware Canary File Integrity Monitor using C++17 and Linux kernel driver concepts.

The prototype focuses on detecting suspicious activity on a protected canary file and generating alerts through both userspace and kernel-level components.

## 2. Implemented Modules

The initial prototype was developed using the following modules:

### 2.1 Canary Manager

Creates and manages the protected canary file used for monitoring.

### 2.2 Filesystem Monitor

Uses the Linux `inotify` API to detect modification, deletion and movement events affecting the canary file.

### 2.3 Integrity Manager

Calculates the SHA-256 hash of the canary file and compares the current hash against the original baseline.

### 2.4 Event Processor

Processes filesystem events and determines whether integrity verification or a security alert is required.

### 2.5 Alert Manager

Generates security alerts, records security events and communicates events to the Linux kernel driver through `/dev/ransomguard`.

### 2.6 Event Logger

Stores security events with timestamps in the application log.

### 2.7 Linux Kernel Driver

The `ransomguard` character-device driver provides `/dev/ransomguard` and receives security event messages from the userspace application.

## 3. Prototype Build

The userspace application was compiled using GNU Make and G++ with C++17 support.

The Linux kernel driver was compiled using the Linux kernel build system against the custom WSL2 kernel source.

Both components were successfully built and integrated.

## 4. Initial Prototype Execution

The application successfully performs the following startup sequence:

1. Creates the canary file.
2. Creates the SHA-256 integrity baseline.
3. Starts Linux `inotify` monitoring.
4. Waits for filesystem events.
5. Processes detected events.
6. Generates security alerts.
7. Sends security events to the kernel driver.

Example startup output:

[INFO] Canary file ready.
[INFO] Integrity baseline created.
[INFO] Monitoring: runtime/canary.txt
[INFO] Waiting for filesystem events...

## 5. Kernel Driver Integration

The kernel driver was successfully loaded into the custom WSL2 Linux kernel.

The driver creates the character device:

/dev/ransomguard

The userspace application opens this device and sends security event messages whenever suspicious canary activity is detected.

The driver receives the messages and records them in the Linux kernel log.

## 6. Prototype Demonstration

The prototype was tested by modifying the protected canary file.

Test command:

echo "RANSOMWARE_TEST" >> runtime/canary.txt

The application detected the modification and reported:

[ALERT] Canary file modified!
[CRITICAL] Integrity violation detected!

The kernel driver also received the corresponding events.

Example kernel log:

ransomguard: event received: CANARY_MODIFIED
ransomguard: event received: INTEGRITY_VIOLATION

This demonstrated successful end-to-end communication between the userspace monitoring application and the Linux kernel driver.

## 7. Progressive Integration

The implementation was developed incrementally.

The initial userspace modules were implemented and tested independently. Filesystem monitoring, integrity verification, event processing and logging were then integrated.

After the userspace prototype was working, the Linux character-device driver was implemented and tested independently.

Finally, the userspace Alert Manager was integrated with `/dev/ransomguard`, completing the userspace-to-kernel event flow.

## 8. Version Control

Git was used throughout development to track implementation progress.

Major features and development stages were committed separately using descriptive commit messages.

Generated build artifacts were excluded using `.gitignore`.

The source code and documentation were maintained in the GitHub repository.

## 9. Initial Prototype Outcome

The initial prototype successfully demonstrated the core anti-ransomware monitoring workflow:

Canary File
→ Linux inotify
→ Event Processor
→ SHA-256 Integrity Verification
→ Alert Manager
→ /dev/ransomguard
→ Linux Kernel Driver

The prototype provided a working foundation for further testing, integration and final implementation.

## 10. Issues and Solutions

### Issue 1: Kernel Module Compatibility

The external kernel driver initially failed to load because of a kernel symbol version mismatch.

Solution:

The driver was rebuilt against the same custom WSL2 kernel source and matching kernel symbol information. After rebuilding and booting into the matching custom kernel, the driver loaded successfully.

### Issue 2: Userspace-to-Kernel Communication

The userspace application initially required access permission to `/dev/ransomguard`.

Solution:

The device permissions were configured during testing so that the userspace application could communicate with the character device.

### Issue 3: IDE Diagnostics

Visual Studio Code initially displayed incorrect diagnostics for Linux kernel headers.

Solution:

The VS Code C/C++ configuration was adjusted to include the required Linux kernel header directories. The actual driver compilation was verified using the Linux kernel build system.

## 11. Conclusion

The initial implementation successfully produced a functional prototype of the Host-Based Anti-Ransomware Canary File Integrity Monitor.

The prototype demonstrates filesystem event detection, SHA-256 integrity verification, security alert generation, event logging and Linux kernel driver integration.
