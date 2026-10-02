# Stage 1 – Project Introduction

## Project Title

**Host-Based Anti-Ransomware Canary File Integrity Monitor**
## 1. Introduction

Ransomware is a type of malicious software that can modify, encrypt, or delete files on a computer. Such activity can cause loss of important data and disrupt normal system operations.

This project proposes a Linux-based host monitoring system that uses specially created canary files as early-warning indicators of suspicious file activity. The system monitors these files for events such as modification, deletion, and movement. When a suspicious event is detected, the system verifies the file's integrity and generates a security alert.

The project is implemented using C/C++ on Linux and incorporates Linux system programming and relevant device-driver concepts. The main purpose of the project is to demonstrate how a lightweight host-based monitoring system can detect potential ransomware-related file activity at an early stage.

## 2. Problem Statement

Ransomware can affect a large number of files in a short period of time. Monitoring every user file continuously can introduce unnecessary overhead and may make it difficult to identify suspicious activity quickly.

A lightweight mechanism is therefore required to identify potentially malicious file activity at an early stage. This project addresses the problem by placing canary files in a monitored location and detecting unexpected changes to them.

If a canary file is modified, deleted, or moved unexpectedly, the system treats the event as a possible indication of suspicious activity. The event is then verified using file integrity information, reported to the user, and recorded in a security log.

## 3. Background and Motivation

Traditional file monitoring approaches may require checking a large number of files repeatedly. This can consume system resources and may not provide an efficient way to identify suspicious activity.

Canary files provide a lightweight alternative. Since these files are intentionally placed for monitoring purposes, legitimate applications normally have little reason to modify or delete them. An unexpected change to a canary file can therefore be treated as an early warning signal.

The project is also motivated by the concepts covered during the Linux, C/C++, system programming, and device-driver training. It provides an opportunity to combine these concepts into one practical system.

## 4. Objectives

The main objectives of the project are:

1. To develop a Linux-based host monitoring system using C/C++.
2. To create and maintain canary files that act as early-warning indicators.
3. To monitor filesystem events affecting the canary files in real time.
4. To detect suspicious modification, deletion, and movement of canary files.
5. To verify file integrity using cryptographic hashing.
6. To generate clear security alerts when integrity violations are detected.
7. To maintain logs of detected security events for analysis and debugging.
8. To demonstrate Linux system programming concepts.
9. To incorporate relevant Linux device-driver and kernel-space concepts.
10. To demonstrate communication between user-space software and a Linux kernel component where applicable.
11. To apply software development practices such as modular design, Git version control, testing, and documentation.

## 5. Proposed Solution

The proposed system will run as a monitoring application on a Linux host. The application will create or register a set of canary files in a protected monitoring location and establish an initial integrity baseline for these files.

The Linux filesystem monitoring mechanism will be used to receive relevant filesystem events. When an event involving a canary file is detected, the system will determine the type of event and perform an integrity check where applicable.

The system will compare the current integrity value of the file with its previously established baseline. If an unexpected modification is detected, the Alert Manager will generate a security alert containing information such as the affected file, event type, severity, and timestamp.

Detected events will also be recorded in a security log for later analysis.

A Linux character-device/kernel-module component will be incorporated to demonstrate relevant device-driver concepts and communication between user space and kernel space. The kernel component will remain limited to functionality that is technically relevant to the project and will not unnecessarily duplicate the user-space monitoring logic.

## 6. High-Level System Workflow

The system will operate according to the following high-level workflow:

1. Start the monitoring application.
2. Load the configured canary file locations.
3. Create or register the required canary files.
4. Calculate and store the initial integrity value of each canary file.
5. Start Linux filesystem event monitoring.
6. Wait for filesystem events involving the monitored canary files.
7. Identify the type of detected event.
8. Verify the integrity of the affected file when applicable.
9. Compare the current integrity value with the stored baseline.
10. Generate an appropriate security alert if suspicious activity is detected.
11. Record the event and alert information in the security log.
12. Continue monitoring until the user stops the application.

### High-Level Flow

Start
↓
Initialize Monitor
↓
Create/Register Canary Files
↓
Establish Integrity Baseline
↓
Start Filesystem Monitoring
↓
Wait for Event
↓
Event Detected
↓
Identify Event Type
↓
Verify Integrity
↓
Integrity Violation?
├── No → Record Normal/Informational Event → Continue Monitoring
└── Yes → Generate Alert → Log Security Event → Continue Monitoring

## 7. Project Scope

The project focuses on developing a lightweight Linux-based host monitoring system for detecting potential ransomware-related activity through canary file monitoring and integrity verification.

The system will operate locally on a Linux machine and will monitor a defined set of canary files. It will detect relevant filesystem events, verify file integrity, generate alerts, and maintain security logs.

The project will also demonstrate relevant Linux system programming and device-driver concepts through a limited kernel-space component and user-space/kernel-space communication.

The project is intended as an educational prototype and is not intended to replace a complete enterprise antivirus, Endpoint Detection and Response (EDR), or ransomware prevention solution.

## 8. In-Scope Features

The following features are included in the project:

- Creation and registration of canary files.
- Establishment of an initial integrity baseline for canary files.
- Real-time monitoring of relevant filesystem events.
- Detection of canary file modification.
- Detection of canary file deletion.
- Detection of canary file movement or rename where applicable.
- Cryptographic integrity verification.
- Security alert generation.
- Alert severity classification.
- Security event logging.
- Error handling and graceful shutdown.
- Modular C++ application design.
- Linux system programming APIs.
- Linux character-device/kernel-module demonstration.
- User-space and kernel-space communication.
- Git-based version control.
- Unit, integration, and system-level testing.

## 9. Out-of-Scope Features

The following features are intentionally excluded from the current project scope:

- Machine Learning or Artificial Intelligence based detection.
- Complete antivirus functionality.
- Complete ransomware prevention.
- Automatic recovery of encrypted files.
- Reverse engineering of real ransomware.
- Implementation of actual ransomware or malicious encryption behavior.
- Network-based threat detection.
- Cloud-based monitoring.
- Web-based dashboards.
- Enterprise-scale Endpoint Detection and Response functionality.
- Large-scale Security Information and Event Management (SIEM) integration.
- Mobile application development.
- Database-based storage.

## 10. Expected Outcomes

At the completion of the project, the system is expected to:

1. Successfully run on a Linux environment.
2. Create and monitor designated canary files.
3. Establish and maintain baseline integrity information.
4. Detect relevant filesystem changes affecting canary files.
5. Identify integrity violations.
6. Generate meaningful security alerts.
7. Record security events in log files.
8. Demonstrate Linux system programming concepts.
9. Demonstrate relevant Linux device-driver concepts.
10. Demonstrate communication between user-space and kernel-space components.
11. Provide a reproducible build and execution process.
12. Provide documented testing results and known limitations.

## 11. Intended Applications

The prototype can be used as an educational demonstration of host-based security monitoring and early detection techniques.

Possible application areas include:

- Monitoring important directories on Linux systems.
- Demonstrating file integrity monitoring.
- Demonstrating early-warning mechanisms for suspicious file activity.
- Security and operating-system education.
- Demonstrating Linux system programming.
- Demonstrating user-space and kernel-space interaction.
- Demonstrating basic security event logging and observability.

## 12. Technology Constraints

The project follows the technical requirements specified for the capstone project.

- Operating System: Linux only.
- Programming Languages: C and C++ only.
- Main Application: C++.
- Kernel component: C/C++ as appropriate for Linux kernel interfaces.
- Version Control: Git.
- Repository: GitHub.
- Development Environment: Linux/WSL2 during development.
- No Python, Java, JavaScript, TypeScript, or other programming languages will be used for project implementation.
- No Machine Learning or Artificial Intelligence components are required.
- The project will use Linux system interfaces and APIs relevant to filesystem monitoring and device-driver concepts.

## 13. Hardware and Software Requirements

### Hardware Requirements

- x86-64 computer.
- Minimum 4 GB RAM.
- Sufficient storage for the Linux development environment and project files.
- Standard keyboard and display.
- No specialized external hardware is required for the current prototype.

### Software Requirements

- Linux operating system.
- C compiler (GCC).
- C++ compiler (G++).
- GNU Make.
- Git.
- GDB for debugging.
- Linux development tools and required system libraries.
- Visual Studio Code or another suitable code editor.

## 14. Training Concept Mapping

The project combines several concepts covered during the 20-day training.

| Training Concept | Application in the Project |
|---|---|
| Linux | The complete system is designed and executed on Linux. |
| C++ Programming | The main monitoring application is implemented in C++. |
| C Programming | C may be used where appropriate for Linux kernel/device-driver interfaces. |
| System Programming | Linux system calls, filesystem APIs, event monitoring, file operations, and process/system interfaces are used. |
| Linux Filesystem | Canary files and filesystem events form the core of the monitoring mechanism. |
| Device Drivers | A Linux character-device/kernel-module component demonstrates relevant driver concepts. |
| User Space and Kernel Space | The C++ monitoring application communicates with the kernel component through an appropriate device interface. |
| Computer Architecture | The project demonstrates the relationship between applications, memory, CPU execution, operating-system services, and kernel-space components. |
| Hardware and Software | The project demonstrates how software running on a computer interacts with operating-system and hardware resources. |
| Git | Git is used for version control and tracking development progress. |
| Testing and Debugging | Unit, integration, and system testing are performed to verify functionality and reliability. |
| Observability | Security events and alerts are recorded in logs for analysis and troubleshooting. |

## 15. Expected Demonstration

During the final project demonstration, the following workflow will be shown:

1. Build the project on Linux.
2. Start the monitoring application.
3. Display the registered canary files.
4. Show the initial integrity baseline.
5. Demonstrate normal monitoring.
6. Modify a canary file manually.
7. Show the filesystem event being detected.
8. Show the integrity verification result.
9. Display the generated security alert.
10. Show the corresponding security log entry.
11. Demonstrate deletion or movement of a canary file.
12. Show the resulting alert and log entry.
13. Demonstrate the Linux kernel module and character device.
14. Demonstrate the relevant user-space/kernel-space interaction.
15. Show the project repository and documentation.
16. Explain the testing results, limitations, and future improvements.

## 16. Project Limitations

The project is an educational prototype and has several limitations:

- It focuses on canary-file-based detection rather than complete ransomware detection.
- It does not analyze every process running on the system.
- It does not guarantee detection of every type of ransomware.
- It does not automatically recover files affected by ransomware.
- It does not provide complete enterprise endpoint protection.
- The current prototype is designed for a controlled Linux environment.
- The effectiveness of detection depends on the placement and protection of the monitored canary files.
- The kernel component is intended to demonstrate relevant device-driver concepts rather than provide a complete kernel-level security solution.

## 17. Future Improvements

Possible future improvements include:

- Monitoring a larger number of protected locations.
- Adding configurable monitoring policies.
- Improving alert prioritization.
- Adding process-level correlation with filesystem events.
- Adding stronger security-event analysis.
- Improving tamper resistance of the monitoring system.
- Adding secure remote log collection.
- Supporting integration with security monitoring platforms.
- Adding controlled response mechanisms such as isolating a suspicious process.
- Improving performance for systems with large numbers of monitored files.

## 18. Conclusion

The Host-Based Anti-Ransomware Canary File Integrity Monitor is a Linux-based security monitoring prototype designed to provide an early indication of suspicious file activity.

The project combines canary files, filesystem event monitoring, integrity verification, security alerts, and event logging into a single system. It also provides an opportunity to apply Linux system programming and relevant device-driver concepts through interaction between user-space software and a kernel component.

The project is intentionally focused on the concepts covered during the training and avoids unnecessary technologies. The final implementation will demonstrate a complete development process from requirements and architecture through implementation, testing, documentation, and Git-based version control.

## 19. Roadmap to Stage 2

Stage 2 will focus on converting the project concept into detailed and measurable requirements.

The next stage will include:

- Preparation of the Project Requirements Document (PRD).
- Definition of functional requirements.
- Definition of non-functional requirements.
- Identification of system and software requirements.
- Definition of project modules and responsibilities.
- Identification of project deliverables.
- Preparation of the development roadmap.
- Definition of acceptance criteria.
- Identification of technical risks and mitigation strategies.

The requirements defined in Stage 2 will be used as the foundation for the system architecture and design in Stage 3.