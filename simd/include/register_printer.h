#ifndef REGISTER_PRINTER_H
#define REGISTER_PRINTER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "unions.h"

// Visual theme enumeration
enum xmm_theme {
	THEME_DEFAULT = 0,
	THEME_OPERAND_A,     // Blue theme
	THEME_OPERAND_B,     // Green theme
	THEME_OPERAND_C,     // Yellow theme
	THEME_RESULT,        // Red theme
	THEME_INPUT,         // Cyan theme
	THEME_OUTPUT,        // Magenta theme
	THEME_INTERMEDIATE,  // White theme
	THEME_DEBUG          // Gray theme
};

// Display format flags
enum display_format {
	DISPLAY_BASE10 = 1 << 0,  // Show decimal values
	DISPLAY_BASE16 = 1 << 1,  // Show hexadecimal values
	DISPLAY_BASE2 = 1 << 2    // Show binary values (grouped by bytes)
};

// Theme configuration structure
struct theme_config {
	const char *border_color;  // Border color
	const char *text_color;    // Text color
	const char *value_color;   // Value color
	const char *index_color;   // Index color
	const char *field_color;   // Field name color
	const char *accent_char;   // Single character accent
};

// Theme definitions - clean and subtle
static const struct theme_config themes[] = {
    [THEME_DEFAULT] = {
        .border_color = "\033[35m",
        .text_color = "\033[37m",
        .value_color = "\033[1;32m",
        .index_color = "\033[1;33m",
        .field_color = "\033[1;36m",
        .accent_char = "●"},
    [THEME_OPERAND_A] = {.border_color = "\033[34m",   // Blue
                         .text_color = "\033[1;34m",   // Bright blue
                         .value_color = "\033[1;36m",  // Bright cyan
                         .index_color = "\033[94m",    // Light blue
                         .field_color = "\033[1;34m",  // Bright blue
                         .accent_char = "▲"},
    [THEME_OPERAND_B] = {.border_color = "\033[32m",   // Green
                         .text_color = "\033[1;32m",   // Bright green
                         .value_color = "\033[1;92m",  // Bright light green
                         .index_color = "\033[92m",    // Light green
                         .field_color = "\033[1;32m",  // Bright green
                         .accent_char = "■"},
    [THEME_OPERAND_C] = {.border_color = "\033[33m",   // Yellow
                         .text_color = "\033[1;33m",   // Bright yellow
                         .value_color = "\033[1;93m",  // Bright light yellow
                         .index_color = "\033[93m",    // Light yellow
                         .field_color = "\033[1;33m",  // Bright yellow
                         .accent_char = "♦"},
    [THEME_RESULT] = {.border_color = "\033[31m",   // Red
                      .text_color = "\033[1;31m",   // Bright red
                      .value_color = "\033[1;91m",  // Bright light red
                      .index_color = "\033[91m",    // Light red
                      .field_color = "\033[1;31m",  // Bright red
                      .accent_char = "★"},
    [THEME_INPUT] = {.border_color = "\033[36m",   // Cyan
                     .text_color = "\033[1;36m",   // Bright cyan
                     .value_color = "\033[1;96m",  // Bright light cyan
                     .index_color = "\033[96m",    // Light cyan
                     .field_color = "\033[1;36m",  // Bright cyan
                     .accent_char = "→"},
    [THEME_OUTPUT] = {.border_color = "\033[35m",   // Magenta
                      .text_color = "\033[1;35m",   // Bright magenta
                      .value_color = "\033[1;95m",  // Bright light magenta
                      .index_color = "\033[95m",    // Light magenta
                      .field_color = "\033[1;35m",  // Bright magenta
                      .accent_char = "←"},
    [THEME_INTERMEDIATE] = {.border_color = "\033[37m",   // White
                            .text_color = "\033[1;37m",   // Bright white
                            .value_color = "\033[1;97m",  // Bright light white
                            .index_color = "\033[97m",    // Light white
                            .field_color = "\033[1;37m",  // Bright white
                            .accent_char = "○"},
    [THEME_DEBUG] = {.border_color = "\033[90m",   // Dark gray
                     .text_color = "\033[1;90m",   // Bright dark gray
                     .value_color = "\033[1;93m",  // Bright yellow for visibility
                     .index_color = "\033[90m",    // Dark gray
                     .field_color = "\033[1;95m",  // Bright magenta
                     .accent_char = "?"}};

#include <inttypes.h>
#include <string.h>

// Helper function to print binary representation grouped by bytes
static void print_binary_grouped(uint64_t value, size_t type_size) {
	for (int byte_idx = type_size - 1; byte_idx >= 0; byte_idx--) {
		uint8_t byte_val = (value >> (byte_idx * 8)) & 0xFF;
		for (int bit = 7; bit >= 0; bit--) {
			printf("%c", (byte_val & (1 << bit)) ? '1' : '0');
		}
		if (byte_idx > 0) printf(" ");
	}
}

static size_t calculate_display_width(size_t type_size, int display_flags) {
	size_t max_width = 0;
	size_t current_width = 0;

	// Calculate width for decimal display
	if (display_flags & DISPLAY_BASE10) {
		// For decimal, we need to consider the maximum digits possible
		// Plus potential negative sign for signed types
		switch (type_size) {
		case 1:  // 8-bit: -128 to 255 (4 chars max)
			current_width = 4;
			break;
		case 2:  // 16-bit: -32768 to 65535 (6 chars max)
			current_width = 6;
			break;
		case 4:  // 32-bit: -2147483648 to 4294967295 (11 chars max)
			current_width = 11;
			break;
		case 8:  // 64-bit: very large numbers (20 chars should be sufficient)
			current_width = 20;
			break;
		default:
			current_width = type_size * 3;  // Conservative estimate
			break;
		}
		if (current_width > max_width) max_width = current_width;
	}

	// Calculate width for hexadecimal display
	if (display_flags & DISPLAY_BASE16) {
		// Hex format: "0x" + (2 chars per byte)
		current_width = 2 + (type_size * 2);
		if (current_width > max_width) max_width = current_width;
	}

	// Calculate width for binary display
	if (display_flags & DISPLAY_BASE2) {
		// Binary format: 8 bits per byte + spaces between bytes
		// For n bytes: (n * 8) + (n - 1) spaces
		current_width = (type_size * 8) + (type_size - 1);
		if (current_width > max_width) max_width = current_width;
	}

	return max_width;
}

static void xmm_val_print(union xmm_val *v, enum val_type type, const char *title, bool with_title, enum xmm_theme theme, int display_flags) {
	size_t n = 0;
	const char *field_name;
	const struct theme_config *t = &themes[theme];

	// Box drawing characters for clean table borders
	const char *top_left = "┌";
	const char *top_right = "┐";
	const char *bottom_left = "└";
	const char *bottom_right = "┘";
	const char *horizontal = "─";
	const char *vertical = "│";
	const char *cross = "┼";
	const char *top_tee = "┬";
	const char *bottom_tee = "┴";
	const char *left_tee = "├";
	const char *right_tee = "┤";

#define PRINT_SEPARATOR(width, count)                                    \
	do {                                                                 \
		printf("%s%s", t->border_color, top_left);                       \
		for (size_t i = 0; i < count; i++) {                             \
			for (size_t j = 0; j < width; j++) printf("%s", horizontal); \
			if (i < count - 1) printf("%s", top_tee);                    \
		}                                                                \
		printf("%s\033[0m\n", top_right);                                \
	} while (0)

#define PRINT_BOTTOM_SEPARATOR(width, count)                             \
	do {                                                                 \
		printf("%s%s", t->border_color, bottom_left);                    \
		for (size_t i = 0; i < count; i++) {                             \
			for (size_t j = 0; j < width; j++) printf("%s", horizontal); \
			if (i < count - 1) printf("%s", bottom_tee);                 \
		}                                                                \
		printf("%s\033[0m\n", bottom_right);                             \
	} while (0)

#define PRINT_MIDDLE_SEPARATOR(width, count)                             \
	do {                                                                 \
		printf("%s%s", t->border_color, left_tee);                       \
		for (size_t i = 0; i < count; i++) {                             \
			for (size_t j = 0; j < width; j++) printf("%s", horizontal); \
			if (i < count - 1) printf("%s", cross);                      \
		}                                                                \
		printf("%s\033[0m\n", right_tee);                                \
	} while (0)

#define FIELD_INFO(field, ctype, fmt, base_width)                                                                    \
	do {                                                                                                             \
		n = sizeof(((union xmm_val *)0)->field) / sizeof(((union xmm_val *)0)->field[0]);                            \
		field_name = #field;                                                                                         \
		size_t type_size = sizeof(((union xmm_val *)0)->field[0]);                                                   \
		size_t width = calculate_display_width(type_size, display_flags);                                            \
		if (width < base_width) width = base_width;                                                                  \
                                                                                                                     \
		printf("\n%s%s (%zu elements):\033[0m\n", t->field_color, field_name, n);                                    \
                                                                                                                     \
		/* Print top border */                                                                                       \
		PRINT_SEPARATOR(width, n);                                                                                   \
                                                                                                                     \
		/* Print index header */                                                                                     \
		printf("%s%s", t->border_color, vertical);                                                                   \
		for (size_t i = 0; i < n; i++) {                                                                             \
			printf("%s%*zu\033[0m%s", t->index_color, (int)width, i, t->border_color);                               \
			printf("%s", vertical);                                                                                  \
		}                                                                                                            \
		printf("\033[0m\n");                                                                                         \
                                                                                                                     \
		/* Print middle separator */                                                                                 \
		PRINT_MIDDLE_SEPARATOR(width, n);                                                                            \
                                                                                                                     \
		/* Print decimal values if requested */                                                                      \
		if (display_flags & DISPLAY_BASE10) {                                                                        \
			printf("%s%s", t->border_color, vertical);                                                               \
			for (size_t i = 0; i < n; i++) {                                                                         \
				printf("%s%*" fmt "\033[0m%s", t->value_color, (int)width, ((ctype *)v->field)[i], t->border_color); \
				printf("%s", vertical);                                                                              \
			}                                                                                                        \
			printf("\033[0m\n");                                                                                     \
			if ((display_flags & (DISPLAY_BASE16 | DISPLAY_BASE2))) {                                                \
				PRINT_MIDDLE_SEPARATOR(width, n);                                                                    \
			}                                                                                                        \
		}                                                                                                            \
                                                                                                                     \
		/* Print hexadecimal values if requested */                                                                  \
		if (display_flags & DISPLAY_BASE16) {                                                                        \
			printf("%s%s", t->border_color, vertical);                                                               \
			for (size_t i = 0; i < n; i++) {                                                                         \
				uint64_t val = 0;                                                                                    \
				memcpy(&val, &((ctype *)v->field)[i], sizeof(ctype));                                                \
				printf("%s0x%0*" PRIx64 "\033[0m%s", t->value_color, (int)(type_size * 2), val, t->border_color);    \
				/* Pad to width */                                                                                   \
				for (size_t pad = 2 + (type_size * 2); pad < width; pad++) printf(" ");                              \
				printf("%s", vertical);                                                                              \
			}                                                                                                        \
			printf("\033[0m\n");                                                                                     \
			if (display_flags & DISPLAY_BASE2) {                                                                     \
				PRINT_MIDDLE_SEPARATOR(width, n);                                                                    \
			}                                                                                                        \
		}                                                                                                            \
                                                                                                                     \
		/* Print binary values if requested */                                                                       \
		if (display_flags & DISPLAY_BASE2) {                                                                         \
			printf("%s%s", t->border_color, vertical);                                                               \
			for (size_t i = 0; i < n; i++) {                                                                         \
				uint64_t val = 0;                                                                                    \
				memcpy(&val, &((ctype *)v->field)[i], sizeof(ctype));                                                \
				printf("%s", t->value_color);                                                                        \
				print_binary_grouped(val, type_size);                                                                \
				printf("\033[0m");                                                                                   \
				/* Pad to width */                                                                                   \
				size_t bin_len = (type_size * 8) + (type_size - 1);                                                  \
				for (size_t pad = bin_len; pad < width; pad++) printf(" ");                                          \
				printf("%s%s", t->border_color, vertical);                                                           \
			}                                                                                                        \
			printf("\033[0m\n");                                                                                     \
		}                                                                                                            \
                                                                                                                     \
		/* Print bottom border */                                                                                    \
		PRINT_BOTTOM_SEPARATOR(width, n);                                                                            \
                                                                                                                     \
	} while (0)

	// Print title header
	if (with_title && title) {
		printf("\n%s%s %s\033[0m\n", t->text_color, t->accent_char, title);
	}

	// Default to base10 if no flags specified
	if (display_flags == 0) {
		display_flags = DISPLAY_BASE10;
	}

	if (type & VAL_TYPE_I8) {
		FIELD_INFO(m_i8, int8_t, "d", 6);
	}
	if (type & VAL_TYPE_I16) {
		FIELD_INFO(m_i16, int16_t, "d", 8);
	}
	if (type & VAL_TYPE_I32) {
		FIELD_INFO(m_i32, int32_t, "d", 12);
	}
	if (type & VAL_TYPE_I64) {
		FIELD_INFO(m_i64, int64_t, "ld", 20);
	}
	if (type & VAL_TYPE_U8) {
		FIELD_INFO(m_u8, uint8_t, "u", 6);
	}
	if (type & VAL_TYPE_U16) {
		FIELD_INFO(m_u16, uint16_t, "u", 8);
	}
	if (type & VAL_TYPE_U32) {
		FIELD_INFO(m_u32, uint32_t, "u", 12);
	}
	if (type & VAL_TYPE_U64) {
		FIELD_INFO(m_u64, uint64_t, "lu", 20);
	}
	if (type & VAL_TYPE_F32) {
		FIELD_INFO(m_f32, float, ".6f", 14);
	}
	if (type & VAL_TYPE_F64) {
		FIELD_INFO(m_f64, double, ".6lf", 18);
	}

	printf("\n");

#undef FIELD_INFO
#undef PRINT_SEPARATOR
#undef PRINT_BOTTOM_SEPARATOR
#undef PRINT_MIDDLE_SEPARATOR
}

#endif  // REGISTER_PRINTER_H