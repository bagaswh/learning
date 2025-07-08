#!/bin/bash

set -Eeuo pipefail

usage() {
    echo "Usage: $0 [OPTIONS] -a <asm_file> -c <c_files...> -o <output>"
    echo ""
    echo "Options:"
    echo "  -a <file>     Assembly source file (.asm or .s)"
    echo "  -c <files>    C source files (space-separated)"
    echo "  -o <output>   Output executable name"
    echo "  -d            Debug mode (keep object files, add debug symbols)"
    echo "  -O <level>    Optimization level (0,1,2,3,s)"
    echo "  -I <dir>      Include directory for C files"
    echo "  -L <dir>      Library directory"
    echo "  -l <lib>      Link library"
    echo "  --clean       Clean object files after linking"
    echo "  -h, --help    Show this help"
    echo ""
    echo "Examples:"
    echo "  $0 -a main.s -c utils.c helper.c -o program"
    exit 1
}

ASM_FILE=""
C_FILES=()
OUTPUT_FILE=""
DEBUG=false
OPT_LEVEL=""
INCLUDE_DIRS=()
LIB_DIRS=()
LIBRARIES=()
CLEAN_OBJECTS=true

while [[ $# -gt 0 ]]; do
    case $1 in
        -a)
            ASM_FILE="$2"
            shift 2
            ;;
        -c)
            shift
            while [[ $# -gt 0 && ! "$1" =~ ^- ]]; do
                C_FILES+=("$1")
                shift
            done
            ;;
        -o)
            OUTPUT_FILE="$2"
            shift 2
            ;;
        -d)
            DEBUG=true
            CLEAN_OBJECTS=false
            shift
            ;;
        -O)
            OPT_LEVEL="$2"
            shift 2
            ;;
        -I)
            INCLUDE_DIRS+=("$2")
            shift 2
            ;;
        -L)
            LIB_DIRS+=("$2")
            shift 2
            ;;
        -l)
            LIBRARIES+=("$2")
            shift 2
            ;;
        --clean)
            CLEAN_OBJECTS=true
            shift
            ;;
        -h|--help)
            usage
            ;;
        *)
            echo "Unknown option: $1"
            usage
            ;;
    esac
done

if [[ -z "$ASM_FILE" ]]; then
    echo "Error: Assembly file (-a) is required"
    usage
fi

if [[ -z "$OUTPUT_FILE" ]]; then
    echo "Error: Output file (-o) is required"
    usage
fi

if [[ ! -f "$ASM_FILE" ]]; then
    echo "Error: Assembly file '$ASM_FILE' not found"
    exit 1
fi

for c_file in "${C_FILES[@]}"; do
    if [[ ! -f "$c_file" ]]; then
        echo "Error: C file '$c_file' not found"
        exit 1
    fi
done

ASM_OBJ="${ASM_FILE%.*}.o"
C_OBJS=()
ALL_OBJS=("$ASM_OBJ")

echo "Building $OUTPUT_FILE..."

# Assemble using clang instead of `as`
echo "Assembling $ASM_FILE..."
if ! clang -c -o "$ASM_OBJ" "$ASM_FILE"; then
    echo "Error: Failed to assemble $ASM_FILE"
    exit 1
fi

if [[ ${#C_FILES[@]} -gt 0 ]]; then
    echo "Compiling C files..."
    CLANG_FLAGS=(-no-pie -fsanitize=address)

    if [[ "$DEBUG" == true ]]; then
        CLANG_FLAGS+=(-g)
    fi

    if [[ -n "$OPT_LEVEL" ]]; then
        CLANG_FLAGS+=("-O$OPT_LEVEL")
    fi

    for include_dir in "${INCLUDE_DIRS[@]}"; do
        CLANG_FLAGS+=("-I$include_dir")
    done

    for lib_dir in "${LIB_DIRS[@]}"; do
        CLANG_FLAGS+=("-L$lib_dir")
    done

    for library in "${LIBRARIES[@]}"; do
        CLANG_FLAGS+=("-l$library")
    done

    echo "Linking $OUTPUT_FILE..."
    clang "${CLANG_FLAGS[@]}" "$ASM_OBJ" "${C_FILES[@]}" -o "$OUTPUT_FILE" -lc
fi

if [[ "$CLEAN_OBJECTS" == true ]]; then
    echo "Cleaning object files..."
    rm -f "${ALL_OBJS[@]}"
fi

echo "Successfully built $OUTPUT_FILE"

if command -v file >/dev/null 2>&1; then
    echo "File info: $(file "$OUTPUT_FILE")"
fi

if [[ "$DEBUG" == false && "$CLEAN_OBJECTS" == true ]]; then
    echo "Object files cleaned up"
elif [[ "$DEBUG" == true ]]; then
    echo "Debug mode: Object files preserved for debugging"
    echo "Object files: ${ALL_OBJS[*]}"
fi
