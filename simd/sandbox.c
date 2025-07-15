#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

typedef uint32_t u32;

int main() {
	u32 value = 1;
	size_t type_size = sizeof(value);

	uint8_t byte_val = (value >> (0 * 8)) & 0xFF;
	printf("%c", (byte_val & (1 << 0)) ? '1' : '0');

	// for (int byte_idx = type_size - 1; byte_idx >= 0; byte_idx--) {
	// 	uint8_t byte_val = (value >> (byte_idx * 8)) & 0xFF;
	// 	for (int bit = 7; bit >= 0; bit--) {
	// 		printf("%c", (byte_val & (1 << bit)) ? '1' : '0');
	// 	}
	// 	if (byte_idx > 0) printf(" ");
	// }
}
