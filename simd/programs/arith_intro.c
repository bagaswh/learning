#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "common.h"
#include "unions.h"

void calcz_cpp(float *z, float *x, float *y, size_t n) {
	for (size_t i = 0; i < n; i++) {
		z[i] = x[i] + y[i];
	}
}

void calcz_avx(float *z, const float *x, const float *y, size_t n) {
	size_t i = 0;
	const size_t num_simd_elements = 8;
	for (; n - i >= num_simd_elements; i += num_simd_elements) {
		__m256 x_vals = _mm256_loadu_ps(&x[i]);
		__m256 y_vals = _mm256_loadu_ps(&y[i]);
		__m256 z_vals = _mm256_add_ps(x_vals, y_vals);
		_mm256_storeu_ps(&z[i], z_vals);
	}
	for (; i < n; i += 1)
		z[i] = x[i] + y[i];
}

void *malloc_or_die(size_t size) {
	void *ptr = malloc(size);
	if (ptr != NULL) {
		return ptr;
	}
	perror("malloc");
	exit(1);
	return NULL;
}

int main(void) {
	size_t n = 1000000000;
	float *z = malloc_or_die(n * sizeof(float));
	float *x = malloc_or_die(n * sizeof(float));
	float *y = malloc_or_die(n * sizeof(float));

	BENCH_START("memset")
	memset(z, 0, n * sizeof(float));
	BENCH_END("memset");

	BENCH_START("fill_x_and_y")
	for (size_t i = 0; i < n; i++) {
		x[i] = 2;
		y[i] = 4;
	}
	BENCH_END("fill_x_and_y")

	BENCH_START("calcz_cpp")
	calcz_cpp(z, x, y, n);
	BENCH_END("calcz_cpp")

	BENCH_START("calcz_avx")
	calcz_avx(z, x, y, n);
	BENCH_END("calcz_avx")

	float temp;
	for (size_t i = 0; i < n; i++) {
		temp = z[i];
	}
	printf("temp: %f\n", temp);

	return 0;
}