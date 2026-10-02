# Stage 5 — Testing, Integration & Improvement

## 1. Testing Objective

The objective of testing is to verify that the Anti-Ransomware Canary File Integrity Monitor correctly detects suspicious changes to the canary file, validates file integrity, generates alerts and communicates security events to the Linux kernel driver.

## 2. Test Environment

- Operating System: Ubuntu 26.04 LTS on WSL2
- Kernel: Custom WSL Linux kernel 6.18.40.1
- Programming Language: C++17
- Kernel Driver Language: C
- Compiler: GCC/G++
- Build System: GNU Make
- Integrity Algorithm: SHA-256
- Filesystem Monitoring: Linux inotify
- Kernel Interface: Linux character device
- Device: `/dev/ransomguard`

## 3. Unit-Level Tests

### Test 1 — Canary File Creation

**Action:** Start the application.

**Expected Result:** The canary file is created and the application reports that the file is ready.

**Result:** PASS

---

### Test 2 — Integrity Baseline Creation

**Action:** Start the application and create the initial integrity baseline.

**Expected Result:** A SHA-256 hash is calculated and stored as the baseline.

**Result:** PASS

---

### Test 3 — Canary Modification Detection

**Action:**
Modify the canary file using:

```bash
echo "RANSOMWARE_TEST" >> runtime/canary.txt

**Expected Result:**

[ALERT] Canary file modified!

**Result:** PASS


---

### Test 4 — Integrity Violation Detection

**Action:** Modify the canary file after the baseline has been created.
**Expected Result:**

[CRITICAL] Integrity violation detected!

**Result:** PASS


---

### Test 5 — Event Logging

**Action:** Trigger a canary modification.

**Expected Result:** The event is written to `runtime/events.log`.

**Result:** PASS

## 4. Kernel Driver Tests


### Test 6 — Driver Loading	

**Action:**

sudo insmod driver/ransomguard.ko

**Expected Result:** The kernel driver loads successfully.

**Observed Result:**
ransomguard: kernel driver loaded

**Result:** PASS


### Test 7 — Device Creation

**Action:**
Check whether the character device exists:

```bash
ls -l /dev/ransomguard
Expected Result: The /dev/ransomguard device is present.
Observed Result:
/dev/ransomguard was created successfully.
Result: PASS


### Test 8 — Userspace to Kernel Communication

**Action:**

Send a test event to the driver:

```bash
echo "TEST_EVENT" | sudo tee /dev/ransomguard
Expected Result: The kernel driver receives the event.
Observed Result:
ransomguard: event received: TEST_EVENT
Result: PASS


### Test 9 — Kernel to Userspace Communication

**Action:**

Read the stored event from the device:

```bash
sudo cat /dev/ransomguard
Expected Result: The previously written event is returned to userspace.
Observed Result:
TEST_EVENT
Result: PASS


### Test 10 — End-to-End Alert Integration

**Action:**

1. Start the anti-ransomware application.
2. Modify the canary file:

```bash
echo "RANSOMWARE_TEST" >> runtime/canary.txt

```text
3. Check the kernel log:

```bash
sudo dmesg | tail


**Expected Result:** The application detects the modification and integrity violation, while the kernel driver receives the corresponding security events.


**Observed Result:**

Application:
```text
[ALERT] Canary file modified!
[CRITICAL] Integrity violation detected!
```text

Kernel:
ransomguard: event received: CANARY_MODIFIED
ransomguard: event received: INTEGRITY_VIOLATION

**Result:** PASS


## 5. Reliability and Negative Testing


### Test 11 — Canary Deletion

**Action:**

Delete the canary file while the monitor is running:

```bash
rm runtime/canary.txt
Expected Result: The monitor detects the deletion and generates a critical alert.
Result: PASS


### Test 12 — Canary Move/Rename

**Action:**

Rename the canary file while the monitor is running.

**Expected Result:** The monitor detects the move/rename operation and generates a critical alert.

**Result:** PASS


## 6. Testing Summary

| Test | Description | Result |
|------|-------------|--------|
| 1 | Canary file creation | PASS |
| 2 | Integrity baseline creation | PASS |
| 3 | Modification detection | PASS |
| 4 | Integrity violation detection | PASS |
| 5 | Event logging | PASS |
| 6 | Driver loading | PASS |
| 7 | Device creation | PASS |
| 8 | Userspace to kernel communication | PASS |
| 9 | Kernel to userspace communication | PASS |
| 10 | End-to-end integration | PASS |
| 11 | Canary deletion | PASS |
| 12 | Canary move/rename | PASS |


## 7. Known Limitations

- The current prototype monitors a designated canary file rather than an entire filesystem.
- The kernel driver currently receives and logs security events but does not independently perform ransomware detection.
- Device permissions may need to be configured appropriately for userspace communication.
- The current prototype is intended as a proof-of-concept and requires further hardening for production deployment.

## 8. Improvements

Future improvements include:

- Monitoring multiple canary files.
- Adding configurable monitoring paths.
- Improving driver access permissions.
- Adding more detailed kernel-level event handling.
- Improving event logging and reporting.
- Adding automated test scripts.
- Improving recovery and response mechanisms.

## 9. Conclusion

Testing confirmed that the Anti-Ransomware Canary File Integrity Monitor can detect suspicious canary-file activity, verify file integrity using SHA-256, generate security alerts, record events, and communicate security events to a Linux kernel character device driver.

The integrated prototype successfully demonstrates the interaction between the C++ userspace monitoring application and the Linux kernel driver.
