#!/bin/bash

echo "======================================"
echo " Anti-Ransomware Canary Test"
echo "======================================"

echo "[1] Checking application..."
if [ -x "./anti_ransomware" ]; then
    echo "PASS: anti_ransomware exists"
else
    echo "FAIL: anti_ransomware not found"
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

echo "[3] Checking canary file..."
if [ -f "runtime/canary.txt" ]; then
    echo "PASS: Canary file exists"
else
    echo "FAIL: Canary file not found"
    exit 1
fi

echo "[4] Checking event log..."
if [ -f "runtime/events.log" ]; then
    echo "PASS: Event log exists"
else
    echo "FAIL: Event log not found"
    exit 1
fi

echo
echo "All basic checks passed."
echo "Run ./anti_ransomware in another terminal"
echo "and modify runtime/canary.txt to perform the live test."
