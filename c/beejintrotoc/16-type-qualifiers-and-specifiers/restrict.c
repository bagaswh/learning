#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/time.h>

double timespec_diff_ms(struct timespec *start, struct timespec *end) {
    return (double)(end->tv_sec - start->tv_sec) * 1000.0 +
           (double)(end->tv_nsec - start->tv_nsec) / 1000000.0;
}

void dostuff(
#ifdef WITH_RESTRICT
    uint64_t *restrict a
#else
    uint64_t *a
#endif
) {
    struct timespec start_time, end_time;

    // --- Corrected preprocessor logic for the print statement ---
    // The original "#ifdef WITH_RESTRICT && DEBUG" doesn't work as intended.
    // #ifdef only checks for one macro. Use #if for complex conditions.
#if defined(WITH_RESTRICT)
    printf("Pointer is 'restrict'. ");
#if defined(DEBUG)
    printf("(DEBUG mode)\n");
#else
    printf("\n");
#endif
#else
    printf("Pointer is NOT 'restrict'.\n");
#endif
    // --- End of corrected preprocessor logic ---

    if (clock_gettime(CLOCK_MONOTONIC, &start_time) == -1) {
        perror("clock_gettime start");
        // Decide how to handle error: exit, or proceed without timing
        // For simplicity here, we'll just print error and continue
    }

    for (long long i = 0; i < 1000000000LL; i++) { // Changed to long long for i to avoid overflow with *a if it grows large.
        // The loop counter itself is fine as int, but the sum can grow.
        // Max int (2*10^9) is fine for 10^9 iterations for the counter i.
        *a += i;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &end_time) == -1) {
        perror("clock_gettime end");
        // Handle error
    }

    // Calculate and print elapsed time
    double elapsed_ms = timespec_diff_ms(&start_time, &end_time);
    printf("Loop execution time: %.3f ms\n", elapsed_ms);

    printf("Final value of a: %lu\n", *a);

    printf("%lu\n", *a);

}

int main() {

    uint64_t a = 1;
    dostuff(&a);

}