#!/bin/bash

set -Eeuo pipefail

SOURCE_FILE="$1"
OUTPUT_FILE="$2"

nasm -f elf -o "${OUTPUT_FILE}.o" "$SOURCE_FILE"
ld -m elf_i386 -o "$OUTPUT_FILE" "${OUTPUT_FILE}.o"