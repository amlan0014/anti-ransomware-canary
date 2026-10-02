# Stage 2 – Project Requirements & Development Plan

## 1. Project Requirements Document (PRD)

### 1.1 Project Title

**Host-Based Anti-Ransomware Canary File Integrity Monitor**

### 1.2 Purpose

The purpose of this Project Requirements Document is to define the functional and non-functional requirements, system requirements, project modules, deliverables, development plan, risks, and acceptance criteria for the Host-Based Anti-Ransomware Canary File Integrity Monitor.

The requirements defined in this document will serve as the foundation for the system architecture, implementation, testing, and final evaluation.

### 1.3 Project Overview

The system is a Linux-based host monitoring prototype implemented using C/C++. It uses canary files as early-warning indicators of suspicious filesystem activity.

The system establishes an integrity baseline for monitored canary files and monitors relevant filesystem events. When a canary file is modified, deleted, or moved unexpectedly, the system identifies the event, performs integrity verification where applicable, generates an alert, and records the event in a security log.

A limited Linux character-device/kernel-module component will also be incorporated to demonstrate relevant Linux device-driver concepts and communication between user space and kernel space.

### 1.4 Project Constraints

The following constraints apply throughout the project:

- The project shall run exclusively on Linux.
- The implementation shall use only C and C++.
- Python, Java, JavaScript, TypeScript, and other programming languages shall not be used for project implementation.
- Machine Learning and Artificial Intelligence are outside the project scope.
- The project shall not implement actual ransomware.
- The project shall focus on detection and early warning rather than complete ransomware prevention.
- The project shall be developed as an individual project.
- The project shall maintain version control using Git.
- The complete project shall be documented and uploaded to GitHub.

## 2. Functional Requirements

Functional requirements describe what the system shall do.

### FR-01: Canary File Creation

The system shall create or register a configurable set of canary files in the selected monitoring location.

### FR-02: Canary File Registration

The system shall maintain information about registered canary files, including their paths and baseline integrity information.

### FR-03: Integrity Baseline

The system shall calculate and store an initial cryptographic integrity value for each registered canary file.

### FR-04: Filesystem Monitoring

The system shall monitor relevant filesystem events affecting registered canary files.

### FR-05: Modification Detection

The system shall detect unexpected modifications to monitored canary files.

### FR-06: Deletion Detection

The system shall detect when a monitored canary file is deleted.

### FR-07: Movement/Rename Detection

The system shall detect relevant movement or rename events involving monitored canary files.

### FR-08: Integrity Verification

The system shall calculate the current integrity value of an affected canary file when applicable and compare it with the stored baseline.

### FR-09: Security Alert

The system shall generate a security alert when a suspicious canary-file event or integrity violation is detected.

### FR-10: Alert Severity

The system shall assign an appropriate severity level to detected events.

### FR-11: Event Logging

The system shall record detected filesystem events and security alerts in a local security log.

### FR-12: Monitoring Status

The system shall provide clear information indicating whether monitoring is active or stopped.

### FR-13: Error Handling

The system shall report relevant errors and handle expected failures without crashing unnecessarily.

### FR-14: Graceful Shutdown

The system shall provide a controlled shutdown mechanism that releases resources and stops filesystem monitoring safely.

### FR-15: Kernel Module Interaction

The project shall include a relevant Linux kernel/device-driver component where technically applicable.

### FR-16: User-Space/Kernel-Space Communication

The system shall demonstrate an appropriate communication mechanism between the C++ user-space application and the Linux kernel component.

### FR-17: Configuration

The system should allow appropriate monitoring parameters to be configured without requiring changes to the core application source code.

### FR-18: Testability

The system shall provide a reproducible method for testing normal filesystem activity and simulated suspicious canary-file activity.


## 3. Non-Functional Requirements

Non-functional requirements describe how the system should behave.

### NFR-01: Performance

The monitoring application should consume reasonable CPU and memory resources during normal operation.

### NFR-02: Responsiveness

Filesystem events involving monitored canary files should be detected with minimal delay.

### NFR-03: Reliability

The system should continue monitoring after handling normal filesystem events and expected errors.

### NFR-04: Maintainability

The application shall use a modular design so that individual components can be developed, tested, and modified independently.

### NFR-05: Portability

The application should be designed for Linux environments using standard Linux system interfaces and C/C++ development tools.

### NFR-06: Security

The system should protect the integrity of its baseline information and security logs as far as practical within the scope of the educational prototype.

### NFR-07: Usability

Alerts and log messages should provide understandable information about the detected event.

### NFR-08: Scalability

The architecture should allow additional canary files and monitoring locations to be added without major changes to the overall system design.

### NFR-09: Resource Management

The application shall properly release file descriptors, allocated memory, monitoring resources, and other system resources during normal shutdown and error conditions.

### NFR-10: Documentation

The project shall maintain appropriate documentation covering requirements, architecture, implementation, testing, usage, limitations, and future improvements.

## 4. System Requirements

### 4.1 Operating System

The project shall be developed and executed on a Linux environment. The development environment currently uses Ubuntu through Windows Subsystem for Linux (WSL2).

### 4.2 Programming Languages

The implementation shall use only:

- C++
- C where required for Linux kernel/device-driver interfaces

No other programming languages shall be used for the project implementation.

### 4.3 Development Tools

The following tools will be used:

- GCC
- G++
- GNU Make
- GDB
- Git
- Visual Studio Code with WSL integration

### 4.4 Linux System Interfaces

The project may use appropriate Linux interfaces and APIs for:

- File operations
- Directory operations
- Filesystem event monitoring
- File descriptors
- Process and signal handling
- Device-file interaction
- User-space/kernel-space communication

### 4.5 Storage Requirements

The system shall store:

- Canary files
- Integrity baseline information
- Security event logs
- Configuration information where required

The prototype shall use local filesystem storage rather than a database.

### 4.6 Kernel Component

The project shall contain a limited Linux kernel/device-driver component to demonstrate:

- Kernel module concepts
- Character-device concepts
- Device-file interaction
- User-space/kernel-space communication
- Basic kernel resource management

The kernel component shall have a clearly defined responsibility and shall not be added only for demonstration purposes without a functional relationship to the project.

## 5. Project Modules

The system will be divided into the following major modules:

### 5.1 Canary Manager

Responsible for:

- Creating canary files.
- Registering canary files.
- Maintaining canary-file information.
- Managing the monitored locations.

### 5.2 Integrity Manager

Responsible for:

- Creating the initial integrity baseline.
- Calculating the current integrity value of a canary file.
- Comparing current and baseline values.
- Reporting integrity violations.

### 5.3 Filesystem Monitor

Responsible for:

- Monitoring filesystem events.
- Receiving relevant events from the Linux filesystem monitoring mechanism.
- Identifying modification, deletion, movement, and rename events.
- Passing detected events to the event-processing component.

### 5.4 Event Processor

Responsible for:

- Interpreting filesystem events.
- Determining whether an event requires integrity verification.
- Coordinating communication between the filesystem monitor, integrity manager, and alert manager.

### 5.5 Alert Manager

Responsible for:

- Generating security alerts.
- Assigning event severity.
- Preparing understandable alert messages.
- Sending alert information to the logging component.

### 5.6 Event Logger

Responsible for:

- Recording detected events.
- Recording security alerts.
- Recording timestamps and relevant event information.
- Maintaining readable local security logs.

### 5.7 Configuration Manager

Responsible for:

- Loading monitoring configuration.
- Managing canary-file locations.
- Managing appropriate monitoring parameters.
- Providing default configuration values.

### 5.8 Kernel/Device Module

Responsible for:

- Implementing the selected Linux character-device/kernel-module functionality.
- Providing a controlled kernel-space interface.
- Supporting communication between the user-space application and kernel component.
- Demonstrating relevant Linux device-driver concepts.

### 5.9 Application Controller

Responsible for:

- Initializing the application.
- Starting and stopping the required modules.
- Coordinating the overall monitoring lifecycle.
- Handling graceful shutdown.
- Managing major application errors.

## 6. Module Interaction

The major components will interact according to the following conceptual flow:

```text
                    +----------------------+
                    | Application Controller|
                    +----------+-----------+
                               |
              +----------------+----------------+
              |                |                |
              v                v                v
       +-------------+  +-------------+  +-------------+
       |   Canary    |  | Configuration|  |   Kernel    |
       |   Manager   |  |   Manager   |  |   Module    |
       +------+------+  +-------------+  +------+------+
              |                              |
              v                              |
       +-------------+                       |
       |  Integrity  |                       |
       |   Manager   |                       |
       +-------------+                       |
                                             |
       +-------------+                       |
       |  Filesystem |<----------------------+
       |   Monitor   |
       +------+------+
              |
              v
       +-------------+
       |    Event    |
       |  Processor  |
       +------+------+
              |
        +-----+------+
        |            |
        v            v
+---------------+ +---------------+
| Alert Manager | | Event Logger  |
+---------------+ +---------------+

## 8. Development Plan

The project will be developed incrementally according to the six stages specified for the capstone.

### Stage 1 – Project Introduction

Status: Completed

Activities:

- Define the project idea.
- Define the problem statement.
- Define objectives.
- Define project scope.
- Define expected outcomes.
- Identify training concepts used by the project.

Deliverable:

- Stage 1 Project Introduction document.

### Stage 2 – Requirements and Development Plan

Status: In Progress

Activities:

- Define functional requirements.
- Define non-functional requirements.
- Define system requirements.
- Identify project modules.
- Define module responsibilities.
- Define deliverables.
- Define development roadmap.
- Identify risks and mitigation strategies.

Deliverable:

- Stage 2 Project Requirements document.

### Stage 3 – System Design and Architecture

Activities:

- Finalize system architecture.
- Define module interfaces.
- Define data structures.
- Prepare architecture diagram.
- Prepare class diagram.
- Prepare sequence diagram.
- Prepare state machine diagram where applicable.
- Finalize kernel/user-space interaction.
- Define implementation plan.
- Prepare Git development structure.

Deliverables:

- Architecture documentation.
- UML diagrams.
- Implementation plan.

### Stage 4 – Initial Implementation and Prototype

Activities:

- Implement the canary manager.
- Implement integrity verification.
- Implement filesystem monitoring.
- Implement event processing.
- Implement logging and alerts.
- Implement the kernel/device component.
- Integrate the major components.
- Produce an initial working prototype.

Deliverable:

- Initial working prototype.

### Stage 5 – Testing, Integration and Improvement

Activities:

- Perform unit testing.
- Perform integration testing.
- Perform system testing.
- Test normal filesystem activity.
- Test canary modification.
- Test canary deletion.
- Test canary movement/rename.
- Test error conditions.
- Debug identified problems.
- Improve reliability and resource management.
- Update documentation.

Deliverable:

- Tested and improved implementation.

### Stage 6 – Final Implementation and Presentation

Activities:

- Complete the final implementation.
- Perform final testing.
- Prepare README.md.
- Complete project documentation.
- Organize GitHub repository.
- Prepare final demonstration.
- Document achievements and limitations.
- Document future improvements.
- Present the final working system.

Deliverables:

- Final source code.
- GitHub repository.
- README.md.
- Documentation.
- Test results.
- Final demonstration.

## 9. Acceptance Criteria

The project will be considered functionally complete when the following conditions are satisfied:

- [ ] The project builds successfully on Linux.
- [ ] The application can create/register canary files.
- [ ] An integrity baseline can be established.
- [ ] Filesystem events affecting canary files can be detected.
- [ ] Canary modification can be detected.
- [ ] Canary deletion can be detected.
- [ ] Canary movement/rename can be detected where supported by the implementation.
- [ ] Integrity violations can be identified.
- [ ] Security alerts are generated for relevant events.
- [ ] Security events are recorded in logs.
- [ ] The application handles expected errors.
- [ ] The application can shut down gracefully.
- [ ] The Linux kernel/device component builds successfully where supported by the development environment.
- [ ] User-space/kernel-space communication can be demonstrated.
- [ ] Unit and integration tests are completed.
- [ ] The final project can be built and executed using documented instructions.
- [ ] The GitHub repository contains the required source code and documentation.

## 10. Development Timeline

The project will be developed incrementally, with each stage producing a measurable output.

| Stage | Major Activities | Expected Output |
|---|---|---|
| Stage 1 | Project introduction, problem definition, objectives, scope | Project introduction document |
| Stage 2 | Requirements, modules, constraints, development plan | PRD and requirements document |
| Stage 3 | Architecture, UML, data structures, interfaces, implementation design | Architecture and design documentation |
| Stage 4 | C/C++ implementation, filesystem monitoring, integrity checking, alerts, logging, kernel component | Working prototype |
| Stage 5 | Unit testing, integration testing, system testing, debugging, optimization | Tested implementation |
| Stage 6 | Final integration, README, documentation, GitHub organization, demonstration | Final project and presentation |

The implementation will prioritize core functionality first. The kernel/device-driver component will be developed and integrated after the user-space architecture has been validated.

## 11. Risks and Mitigation

| Risk | Impact | Mitigation |
|---|---|---|
| Linux kernel-module compatibility issues in WSL2 | High | Verify kernel-module support early and keep a suitable Linux environment available for driver testing if required. |
| Filesystem monitoring events behave differently across environments | Medium | Test the monitoring mechanism using controlled filesystem operations. |
| Incorrect integrity verification | High | Use controlled test files and compare known file changes against expected results. |
| Resource leaks in the monitoring application | Medium | Use systematic resource management and perform repeated start/stop tests. |
| Unexpected filesystem events | Medium | Validate event types and paths before processing them. |
| Kernel/user-space communication errors | High | Define a small and well-tested interface between the application and kernel component. |
| Excessive project scope | High | Follow the defined in-scope and out-of-scope requirements. |
| Insufficient testing time | Medium | Develop and test modules incrementally rather than waiting until the end. |
| Documentation falling behind implementation | Medium | Update documentation and Git commits throughout development. |


## 12. Requirements-to-Module Traceability

The following mapping connects the functional requirements with the modules responsible for implementing them.

| Requirement | Description | Responsible Module |
|---|---|---|
| FR-01 | Canary file creation | Canary Manager |
| FR-02 | Canary registration | Canary Manager |
| FR-03 | Integrity baseline | Integrity Manager |
| FR-04 | Filesystem monitoring | Filesystem Monitor |
| FR-05 | Modification detection | Filesystem Monitor / Event Processor |
| FR-06 | Deletion detection | Filesystem Monitor / Event Processor |
| FR-07 | Movement/rename detection | Filesystem Monitor / Event Processor |
| FR-08 | Integrity verification | Integrity Manager |
| FR-09 | Security alerts | Alert Manager |
| FR-10 | Alert severity | Alert Manager |
| FR-11 | Event logging | Event Logger |
| FR-12 | Monitoring status | Application Controller |
| FR-13 | Error handling | Application Controller / Individual Modules |
| FR-14 | Graceful shutdown | Application Controller |
| FR-15 | Kernel module interaction | Kernel/Device Module |
| FR-16 | User-space/kernel-space communication | Kernel/Device Module / Application Controller |
| FR-17 | Configuration | Configuration Manager |
| FR-18 | Testability | All relevant modules / Test Framework |


## 13. Stage 2 Conclusion

Stage 2 converts the project concept defined in Stage 1 into a structured set of requirements and an implementation roadmap.

The functional requirements define what the system must do, while the non-functional requirements define expected characteristics such as performance, reliability, maintainability, and resource management.

The project has been divided into clearly defined modules so that implementation and testing can be performed incrementally. The development timeline, acceptance criteria, risks, and requirements-to-module traceability provide a structured foundation for the architecture and implementation stages.

The outputs of Stage 2 will be used directly during Stage 3 to design the system architecture, module interfaces, data structures, UML diagrams, and kernel/user-space interaction.
