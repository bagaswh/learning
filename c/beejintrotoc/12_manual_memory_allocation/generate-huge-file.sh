#!/bin/bash

# Default values
DEFAULT_LINES=50
DEFAULT_OUTPUT="generated_text.txt"
MIN_LINE_SIZE=10240  # 10 KiB in bytes

# Function to display usage
usage() {
    echo "Usage: $0 [OPTIONS]"
    echo "Generate a text file with variable-length lines (minimum 10 KiB each)"
    echo ""
    echo "OPTIONS:"
    echo "  -l, --lines NUM     Number of lines to generate (default: $DEFAULT_LINES)"
    echo "  -o, --output FILE   Output filename (default: $DEFAULT_OUTPUT)"
    echo "  -h, --help         Show this help message"
    echo ""
    echo "Example: $0 -l 100 -o myfile.txt"
}

# Function to generate random text
generate_random_text() {
    local size=$1
    # Generate random alphanumeric characters and spaces
    tr -dc 'A-Za-z0-9 \n' < /dev/urandom | head -c "$size"
}

# Function to generate a line with at least MIN_LINE_SIZE bytes
generate_line() {
    local line_num=$1
    local base_size=$MIN_LINE_SIZE
    # Add random variation (0-2048 additional bytes)
    local extra_size=$((RANDOM % 2048))
    local total_size=$((base_size + extra_size))

    # Create line content with some structure
    local prefix="Line $line_num: "
    local remaining_size=$((total_size - ${#prefix}))

    echo -n "$prefix"
    generate_random_text "$remaining_size"
}

# Parse command line arguments
LINES=$DEFAULT_LINES
OUTPUT=$DEFAULT_OUTPUT

while [[ $# -gt 0 ]]; do
    case $1 in
        -l|--lines)
            LINES="$2"
            if ! [[ "$LINES" =~ ^[0-9]+$ ]] || [ "$LINES" -lt 1 ]; then
                echo "Error: Lines must be a positive integer"
                exit 1
            fi
            shift 2
            ;;
        -o|--output)
            OUTPUT="$2"
            shift 2
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Error: Unknown option $1"
            usage
            exit 1
            ;;
    esac
done

# Validate output directory exists
OUTPUT_DIR=$(dirname "$OUTPUT")
if [ ! -d "$OUTPUT_DIR" ]; then
    echo "Error: Output directory '$OUTPUT_DIR' does not exist"
    exit 1
fi

# Generate the file
echo "Generating $LINES lines of text (minimum 10 KiB each)..."
echo "Output file: $OUTPUT"

# Remove existing file if it exists
> "$OUTPUT"

# Generate lines
for ((i=1; i<=LINES; i++)); do
    echo "Generating line $i of $LINES..."
    generate_line "$i" >> "$OUTPUT"
    echo "" >> "$OUTPUT"  # Add newline after each line
done

# Display file information
FILE_SIZE=$(stat -f%z "$OUTPUT" 2>/dev/null || stat -c%s "$OUTPUT" 2>/dev/null)
if [ $? -eq 0 ]; then
    FILE_SIZE_MB=$(echo "scale=2; $FILE_SIZE / 1024 / 1024" | bc 2>/dev/null || echo "$(($FILE_SIZE / 1024 / 1024))")
    echo ""
    echo "File generation complete!"
    echo "File: $OUTPUT"
    echo "Lines: $LINES"
    echo "Size: $FILE_SIZE bytes (~${FILE_SIZE_MB} MB)"
else
    echo ""
    echo "File generation complete!"
    echo "File: $OUTPUT"
    echo "Lines: $LINES"
fi