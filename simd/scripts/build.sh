#!/bin/bash

set -Eeuo pipefail

PROGRAM_NAME="$1"

clang \
    -g \
    -std=c17 \
    -march=native \
    -mavx \
    -msse \
    -fsanitize=address \
    -fno-omit-frame-pointer \
    -fsanitize-address-use-after-scope \
    -I./include/ \
    -I./external/tuibox/ \
    "programs/${PROGRAM_NAME}.c" \
    lib/*.c \
    -lm \
    -lpthread \
    -o "build/bin/${PROGRAM_NAME}"