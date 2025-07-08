#!/bin/bash

set -Eeuo pipefail

SOURCE_FILE="$1"
OUTPUT_FILE="$2"
LD_FLAGS="$3"

set -x
as -o "${OUTPUT_FILE}.o" "$SOURCE_FILE"
gcc -nostartfiles -no-pie "$OUTPUT_FILE.o" -o "$OUTPUT_FILE" -lc