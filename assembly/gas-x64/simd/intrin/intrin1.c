#include <x86intrin.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdalign.h>

#define INTRIN1_ARR_SIZE 500000000

#define ALIGN4(val) (((val) + 0x3) & ~0x3)
#define ALIGN8(val) (((val) + 0x7) & ~0x7)
#define ALIGN16(val) (((val) + 0xF) & ~0xF)

/* --- OP1 --- */

#ifdef OP1_AVX2
void *op1(void *a, void *b, void *c, size_t step)
{
    double *aa = a;
    double *bb = b;
    double *cc = c;
    for (size_t i = 0; i < INTRIN1_ARR_SIZE; i += step)
    {
        __m256d x = _mm256_load_pd(&aa[i]);
        __m256d y = _mm256_load_pd(&bb[i]);
        __m256d z = _mm256_add_pd(x, y);
        _mm256_storeu_pd(&cc[i], z);
    }
    return &cc[INTRIN1_ARR_SIZE-step];
}
#else
void *op1(void *a, void *b, void *c, size_t step)
{
    char *aa = a;
    char *bb = b;
    char *cc = c;
    for (size_t i = 0; i < INTRIN1_ARR_SIZE; i += step)
    {
        cc[i] = aa[i] + bb[i];
    }
    return &cc[INTRIN1_ARR_SIZE-step];
}
#endif

/* --- OP1 --- */
/* ----------- */

/* --- SUMMATION --- */

int sum_simd(const int *a, int n) {
    __m256i sum = _mm256_setzero_si256();

    int i;
    for (i = 0; i + 7 < n; i += 8) {
        __m256i v = _mm256_loadu_si256((__m256i const *)(a + i)); // load 8 ints
        sum = _mm256_add_epi32(sum, v); // sum += v;
    }

    __m128i sum128 = _mm_add_epi32(
        _mm256_castsi256_si128(sum),       // lower 128
        _mm256_extracti128_si256(sum, 1)   // upper 128
    );
    sum128 = _mm_add_epi32(sum128, _mm_shuffle_epi32(sum128, _MM_SHUFFLE(1, 0, 3, 2)));
    sum128 = _mm_add_epi32(sum128, _mm_shuffle_epi32(sum128, _MM_SHUFFLE(2, 3, 0, 1)));

    int res = _mm_cvtsi128_si32(sum128); // extract final scalar sum

    for (; i < n; i++) {
        res += a[i];
    }

    return res;
}
/* --- SUMMATION --- */
/* ----------------- */


unsigned int g_seed;

void fast_srand(int);
int fast_rand(void);

inline void fast_srand(int seed) {
    g_seed = seed;
}

inline int fast_rand(void) {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}

void fill_rand(void *dst, size_t n, size_t step) {
    for (size_t i = 0; i < n; i+=step) {
        int r = fast_rand();
        memcpy(dst+i, &r, step < sizeof(r) ? step : sizeof(r));
    }
}

int main()
{
    // const int n = 1e6;
    // int a[n], s = 0;

    fast_srand(clock());

    size_t step = sizeof(__uint64_t);
    size_t malloc_sz = step * INTRIN1_ARR_SIZE;
    
    alignas(64) 
    __uint64_t *a = malloc(malloc_sz),
           *b = malloc(malloc_sz),
           *c = malloc(malloc_sz);
    fill_rand(a, INTRIN1_ARR_SIZE, step);
    // fill_rand(b, INTRIN1_ARR_SIZE, step);
    printf("%lu\n", a[INTRIN1_ARR_SIZE-step]);

    return 0;

    clock_t start_time = clock();
    // for (int t = 0; t < 100000; t++) {
    //     for (int i = 0; i < n; i++) {
    //         s += a[i];
    //     }
    // }
    double *result = (double*)op1(a, b, c, step);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Done in %f seconds\n", elapsed_time);
    printf("result: %f\n", *result);

    return 0;
}