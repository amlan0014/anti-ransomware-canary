#!/bin/bash

echo "======================================"
echo " Anti-Ransomware Functional Test"
echo "======================================"

APP="./anti_ransomware"
CANARY="runtime/canary.txt"
LOG="runtime/events.log"

PASS=0
FAIL=0

cleanup() {
    if [ -n "$APP_PID" ] && kill -0 "$APP_PID" 2>/dev/null; then
        kill "$APP_PID" 2>/dev/null
        wait "$APP_PID" 2>/dev/null
    fi

    rm -f runtime/canary_moved.txt
}

run_test() {
    TEST_NAME="$1"
    ACTION="$2"
    EXPECTED_OUTPUT="$3"
    EXPECTED_LOG="$4"

    echo
    echo "[TEST] $TEST_NAME"

    rm -f "$CANARY" runtime/canary_moved.txt

    "$APP" > /tmp/anti_ransomware_test.log 2>&1 &
    APP_PID=$!

    sleep 2

    bash -c "$ACTION"

    sleep 2

    if grep -q "$EXPECTED_OUTPUT" /tmp/anti_ransomware_test.log &&
       grep -q "$EXPECTED_LOG" "$LOG"; then
        echo "PASS: $TEST_NAME"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $TEST_NAME"
        echo "--- Application output ---"
        cat /tmp/anti_ransomware_test.log
        echo "--- Recent event log ---"
        tail -n 5 "$LOG"
        FAIL=$((FAIL + 1))
    fi

    cleanup
}

echo "[1] Checking application..."
if [ -x "$APP" ]; then
    echo "PASS: Application exists"
else
    echo "FAIL: Application not found"
    exit 1
fi

echo "[2] Checking kernel driver..."
if [ -e "/dev/ransomguard" ]; then
    echo "PASS: /dev/ransomguard exists"
else
    echo "FAIL: /dev/ransomguard not found"
    echo "Run: sudo insmod driver/ransomguard.ko"
    exit 1
fi

echo "[3] Checking canary directory..."
if [ -d "runtime" ]; then
    echo "PASS: Runtime directory exists"
else
    echo "FAIL: Runtime directory not found"
    exit 1
fi

run_test \
    "Canary modification detection" \
    "echo 'TEST_MODIFICATION' >> '$CANARY'" \
    "Canary file modified!" \
    "Canary file modification detected."

run_test \
    "Canary move detection" \
    "mv '$CANARY' runtime/canary_moved.txt" \
    "Canary file moved or renamed!" \
    "CRITICAL: Canary file moved or renamed."

run_test \
    "Canary deletion detection" \
    "rm -f '$CANARY'" \
    "Canary file deleted!" \
    "CRITICAL: Canary file deleted."

echo
echo "======================================"
echo " Test Summary"
echo "======================================"
echo "Passed: $PASS"
echo "Failed: $FAIL"

rm -f /tmp/anti_ransomware_test.log

if [ "$FAIL" -eq 0 ]; then
    echo "ALL FUNCTIONAL TESTS PASSED"
    exit 0
else
    echo "SOME TESTS FAILED"
    exit 1
fi
