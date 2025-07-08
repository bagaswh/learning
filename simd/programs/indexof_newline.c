#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef uint64_t u64;

int index_of_newline_sse(char *data, size_t off, size_t size) {
	if (size == 0) return -1;

	const __m128i newline_vec = _mm_set1_epi8('\n');
	size_t i = 0;

	// Process 16 bytes at a time
	for (i = off; i <= size - 16; i += 16) {
		__m128i chunk = _mm_loadu_si128((__m128i *)(data + i));
		__m128i cmp = _mm_cmpeq_epi8(chunk, newline_vec);

		int mask = _mm_movemask_epi8(cmp);
		if (mask != 0) {
			// Found a newline, find the first one
			int offset = __builtin_ctz(mask);
			return i + offset;
		}
	}

	// Handle remaining bytes (less than 16)
	for (; i < size; i++) {
		if (data[i] == '\n') {
			return i;
		}
	}

	return -1;
}

// AVX2 version (processes 32 bytes at a time)
int index_of_newline_avx2(char *data, size_t off, size_t size) {
	if (size == 0) return -1;

	const __m256i newline_vec = _mm256_set1_epi8('\n');
	size_t i = 0;

	// Process 32 bytes at a time
	for (i = off; i <= size - 32; i += 32) {
		__m256i chunk = _mm256_loadu_si256((__m256i *)(data + i));
		__m256i cmp = _mm256_cmpeq_epi8(chunk, newline_vec);

		int mask = _mm256_movemask_epi8(cmp);
		if (mask != 0) {
			// Found a newline, find the first one
			int offset = __builtin_ctz(mask);
			return i + offset;
		}
	}

	// Handle remaining bytes (less than 32)
	for (; i < size; i++) {
		if (data[i] == '\n') {
			return i;
		}
	}

	return -1;
}

u64 align32(u64 x) {
	return (x + 31) & ~31;
}

// Optimized AVX2 version with aligned access when possible
int index_of_newline_avx2_aligned(char *data, size_t off, size_t size) {
	if (size == 0) return -1;

	const __m256i newline_vec = _mm256_set1_epi8('\n');
	size_t i = 0;

	// Handle unaligned prefix to reach 32-byte boundary
	uintptr_t addr = (uintptr_t)data;

	/*
	    Calculate bytes needed to reach next 32-byte boundary.
	    - addr & 31 gives offset within current 32-byte block
	    - 32 - offset gives bytes to boundary, but we mask with 31
	      to handle the case where addr is already aligned (avoids 32).

	    My initial solution to prefix_len was to
	        1) take 32 aligned addr
	        2) subtract 32 aligned addr from size

	    size_t prefix_len = align32(addr) - addr;

	    Produces this asm (with clang -O0):

	        mov     rax, qword ptr [rbp - 16]
	        mov     qword ptr [rbp - 8], rax
	        mov     rax, qword ptr [rbp - 8]
	        add     rax, 31
	        and     rax, -32
	        mov     rcx, qword ptr [rbp - 16]
	        sub     rax, rcx
	        mov     qword ptr [rbp - 24], rax

	    It yields more instructions and more mem move ops.

	    Remember, even L1 access is slower than register access.

	    This final solution produces (clang -O0):

	        mov     rax, qword ptr [rbp - 8]
	        and     rcx, 31
	        mov     eax, 32
	        sub     rax, rcx
	        and     rax, 31
	        mov     qword ptr [rbp - 16], rax.

	    Now, of course, -O2 will optimize those away to a single mov possibly.
	*/
	size_t prefix_len = (32 - (addr & 31)) & 31;

	if (prefix_len > 0 && prefix_len < size) {
		for (i = 0; i < prefix_len; i++) {
			if (data[i] == '\n') {
				return i;
			}
		}
	}

	// Process 32 bytes at a time with aligned access
	for (; i <= size - 32; i += 32) {
		__m256i chunk;
		if ((addr + i) & 31) {
			chunk = _mm256_loadu_si256((__m256i *)(data + i));
		} else {
			chunk = _mm256_load_si256((__m256i *)(data + i));
		}

		__m256i cmp = _mm256_cmpeq_epi8(chunk, newline_vec);
		int mask = _mm256_movemask_epi8(cmp);

		if (mask != 0) {
			int offset = __builtin_ctz(mask);
			return i + offset;
		}
	}

	// Handle remaining bytes
	for (; i < size; i++) {
		if (data[i] == '\n') {
			return i;
		}
	}

	return -1;
}

int index_of_newline(char *data, size_t off, size_t size) {
	size_t i = off;
	for (; i < size; i++) {
		if (data[i] == '\n') {
			return i;
		}
	}
	return -1;
}

int index_of_newline_auto(char *data, size_t off, size_t size) {
	if (size < 32) {
		return index_of_newline(data, off, size);
	} else if (size < 128) {
		return index_of_newline_sse(data, off, size);
	} else {
		return index_of_newline_avx2(data, off, size);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return 1;
	}

	FILE *in = fopen(argv[1], "r");
	if (in == NULL) {
		fprintf(stderr, "Failed to open %s\n", argv[1]);
		return 1;
	}

	struct stat st;
	fstat(fileno(in), &st);
	size_t size = st.st_size;

	char *data = malloc(size);
	fread(data, 1, size, in);
	fclose(in);

	// test index of implementations
	size_t off = 0;
	while (off < size) {
		int index_scalar = index_of_newline(data, off, size);
		int index_sse = index_of_newline_sse(data, off, size);
		int index_avx2 = index_of_newline_avx2(data, off, size);
		if (index_scalar != index_sse || index_scalar != index_avx2 || index_sse != index_avx2) {
			fprintf(stderr, "Mismatch! index_scalar: %d, index_sse: %d, index_avx2: %d\n", index_scalar, index_sse, index_avx2);
			return 1;
		}
		off = index_scalar + 1;
	}
}
