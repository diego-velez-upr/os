#!/bin/bash

# Define the source file to check
# SOURCE_FILE="../src/main.c"
SOURCE_FILE="../worker/src/main.c"
# HEADER_FILE="../include/functions.h"
HEADER_FILE="../main_program/src/main.c"
# FUNCTIONS_FILE="../src/functions.c"
FUNCTIONS_FILE=""

echo "--- Running static analysis with cpplint ---"
./cpplint.py --root=.. --filter=-whitespace/ending_newline,-runtime/threadsafe_fn,-build/include_subdir,-readability/copyright,-legal/copyright ${SOURCE_FILE} ${HEADER_FILE} ${FUNCTIONS_FILE} > cpplint_report.txt 2>&1

# Sum the severity values (numbers in square brackets at the end of each error line)
SEVERITY_SUM=$(grep -o '\[[0-9]\+\]$' cpplint_report.txt | grep -o '[0-9]\+' | awk '{s+=$1} END {print s+0}')

# Calculate the style score (100 minus 5 points per severity, minimum 0)
STYLE_SCORE=$(( 100 - SEVERITY_SUM * 2))
if [ $STYLE_SCORE -lt 0 ]; then
    STYLE_SCORE=0
fi

echo "--- Style Check Report ---"
cat cpplint_report.txt
echo "--------------------------"
echo "Style Score: $STYLE_SCORE out of 100"

# Clean up
#rm cpplint_report.txt
