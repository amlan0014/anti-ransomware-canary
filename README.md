# Host-Based Anti-Ransomware Canary File Integrity Monitor

A Linux-based cybersecurity prototype that detects suspicious activity affecting a protected canary file.

The system monitors the canary file, detects modification, deletion and movement, verifies file integrity using SHA-256, generates security alerts, records events and communicates security events to a Linux kernel character device driver.

The userspace monitoring application is implemented in C++17, while the Linux kernel driver is implemented in C.

## Features

- Canary file creation and protection
- Real-time filesystem monitoring using Linux inotify
- SHA-256 file integrity verification
- Detection of file modification, deletion and movement
- Security alert generation
- Timestamped event logging
- Linux kernel character-device driver integration
- Userspace-to-kernel event communication
- Kernel event logging through dmesg

## Project Structure

    anti-ransomware-canary/
    ├── include/
    │   ├── alert_manager.hpp
    │   ├── canary_manager.hpp
    │   ├── event_logger.hpp
    │   ├── event_processor.hpp
    │   ├── filesystem_monitor.hpp
    │   └── integrity_manager.hpp
    ├── src/
    │   ├── alert_manager.cpp
    │   ├── canary_manager.cpp
    │   ├── event_logger.cpp
    │   ├── event_processor.cpp
    │   ├── filesystem_monitor.cpp
    │   ├── integrity_manager.cpp
    │   └── main.cpp
    ├── driver/
    │   ├── ransomguard.c
    │   └── Makefile
    └── docs/

## Requirements

### Software

- Ubuntu Linux / WSL2
- GCC / G++
- GNU Make
- OpenSSL development libraries
- Linux kernel headers/source
- Git

### Build Dependencies

Install the required packages:

    sudo apt update
    sudo apt install build-essential libssl-dev git

The kernel driver is built against the configured Linux kernel source tree.

## Build and Run

### 1. Build the userspace application

    make

### 2. Build the kernel driver

    cd driver
    make
    cd ..

### 3. Load the kernel driver

    sudo insmod driver/ransomguard.ko

### 4. Verify the device

    ls -l /dev/ransomguard

### 5. Configure device permissions for testing

    sudo chmod 666 /dev/ransomguard

### 6. Run the application

    ./anti_ransomware

Keep the application running while testing the canary file.

## Testing

The canary file is created at:

    runtime/canary.txt

To test modification detection:

    echo "RANSOMWARE_TEST" >> runtime/canary.txt

The application should report:

    [ALERT] Canary file modified!
    [CRITICAL] Integrity violation detected!

Check the kernel log with:

    sudo dmesg | tail

Check application logs with:

    cat runtime/events.log

## Kernel Driver Testing

Send a test event directly to the driver:

    echo "TEST_EVENT" | sudo tee /dev/ransomguard

Read the event back:

    sudo cat /dev/ransomguard

Check the kernel log:

    sudo dmesg | tail

## Stopping the Driver

When testing is complete, the driver can be unloaded with:

    sudo rmmod ransomguard

## Documentation

Project documentation is available in the docs directory:

- Stage1_Project_Introduction.md
- Stage2_Project_Requirements.md
- Stage3_System_Design.md
- Stage4_Initial_Implementation.md
- Stage5_Testing.md
- Stage6_Final_Implementation.md

## Technology Stack

| Component | Technology |
|---|---|
| Userspace application | C++17 |
| Kernel driver | C |
| Filesystem monitoring | Linux inotify |
| Integrity verification | SHA-256 |
| Kernel interface | Linux character device |
| Build system | GNU Make |
| Operating system | Ubuntu Linux / WSL2 |
| Version control | Git |

## Project Outcome

The completed prototype demonstrates a host-based approach for detecting suspicious activity using a canary file.

The system combines C++ userspace monitoring, Linux filesystem event monitoring, SHA-256 integrity verification, security event logging and Linux kernel driver integration.

## Limitations

- The current prototype focuses on a designated canary file.
- The kernel driver primarily provides event reception and logging.
- The prototype requires appropriate permissions for access to the character device.
- Additional hardening and testing would be required for production deployment.

## Future Improvements

- Support multiple canary files.
- Add configurable monitoring paths.
- Improve driver access control.
- Add more detailed kernel-level event handling.
- Improve event reporting and visualization.
- Add automated testing scripts.
- Add stronger incident response and recovery mechanisms.

## Conclusion

The final implementation successfully integrates the C++ userspace anti-ransomware monitor with a Linux kernel character device driver.

The prototype demonstrates canary-file monitoring, SHA-256 integrity verification, security event detection, event logging and userspace-to-kernel communication.

The project provides a working foundation for further development of host-based ransomware detection and response mechanisms.
