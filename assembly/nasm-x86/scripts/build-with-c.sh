#!/bin/bash

set -Eeuo pipefail

# Usage function
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
    echo "  $0 -a main.asm -c utils.c helper.c -o program"
    echo "  $0 -a lexer.asm -c lexerutils.c -o lexer -d"
    echo "  $0 -a main.asm -c file1.c file2.c -o app -O2 -I./include -lm"
    exit 1
}

# Default values
ASM_FILE=""
C_FILES=()
OUTPUT_FILE=""
DEBUG=false
OPT_LEVEL=""
INCLUDE_DIRS=()
LIB_DIRS=()
LIBRARIES=()
CLEAN_OBJECTS=true

# Parse command line arguments
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

# Validate required arguments
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

# Check if C files exist
for c_file in "${C_FILES[@]}"; do
    if [[ ! -f "$c_file" ]]; then
        echo "Error: C file '$c_file' not found"
        exit 1
    fi
done

# Create object file names
ASM_OBJ="${ASM_FILE%.*}.o"
C_OBJS=()
ALL_OBJS=("$ASM_OBJ")

echo "Building $OUTPUT_FILE..."

# Compile assembly file
echo "Assembling $ASM_FILE..."
if ! nasm -f elf -o "$ASM_OBJ" "$ASM_FILE"; then
    echo "Error: Failed to assemble $ASM_FILE"
    exit 1
fi

# Compile C files
if [[ ${#C_FILES[@]} -gt 0 ]]; then
    echo "Compiling C files..."
    
    # Build GCC flags
    GCC_FLAGS+=(-fpic -m32)
    
    if [[ "$DEBUG" == true ]]; then
        GCC_FLAGS+=(-g)
    fi
    
    if [[ -n "$OPT_LEVEL" ]]; then
        GCC_FLAGS+=("-O$OPT_LEVEL")
    fi
    
    for include_dir in "${INCLUDE_DIRS[@]}"; do
        GCC_FLAGS+=("-I$include_dir")
    done
    
    # Compile each C file
    # for c_file in "${C_FILES[@]}"; do
    #     c_obj="${c_file%.*}.o"
    #     C_OBJS+=("$c_obj")
    #     ALL_OBJS+=("$c_obj")
        
    #     echo "  Compiling $c_file -> $c_obj"
    #     if !  then
    #         echo "Error: Failed to compile $c_file"
    #         exit 1
    #     fi
    # done

    gcc "${GCC_FLAGS[@]}" "$ASM_OBJ" -c "$C_FILES";
fi

# Link everything together
# echo "Linking..."
# LINK_FLAGS=(-no-pie -m32)

# if [[ "$DEBUG" == true ]]; then
#     LINK_FLAGS+=(-g)
# fi

# for lib_dir in "${LIB_DIRS[@]}"; do
#     LINK_FLAGS+=("-L$lib_dir")
# done

# for library in "${LIBRARIES[@]}"; do
#     LINK_FLAGS+=("-l$library")
# done

# if ! gcc "${LINK_FLAGS[@]}" "${ALL_OBJS[@]}" -o "$OUTPUT_FILE"; then
#     echo "Error: Failed to link"
#     exit 1
# fi

# Clean up object files if requested
if [[ "$CLEAN_OBJECTS" == true ]]; then
    echo "Cleaning object files..."
    rm -f "${ALL_OBJS[@]}"
fi

echo "Successfully built $OUTPUT_FILE"

# Show file info
if command -v file >/dev/null 2>&1; then
    echo "File info: $(file "$OUTPUT_FILE")"
fi

if [[ "$DEBUG" == false && "$CLEAN_OBJECTS" == true ]]; then
    echo "Object files cleaned up"
elif [[ "$DEBUG" == true ]]; then
    echo "Debug mode: Object files preserved for debugging"
    echo "Object files: ${ALL_OBJS[*]}"
fi