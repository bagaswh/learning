#!/bin/bash

PROGRAM="$1"

if [[ "$PROGRAM" == *.zig ]]; then
    PROGRAM="${PROGRAM%.zig}"
fi

zig cc "$PROGRAM.zig" -o "$PROGRAM"  && ./"$PROGRAM"