#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint8_t u8;
typedef int8_t i8;

#define BENCH_START(name)                \
	{                                    \
		struct timespec __tsbench_start; \
		clock_gettime(CLOCK_MONOTONIC, &__tsbench_start);

#define BENCH_END(name)                                                                          \
	struct timespec __tsbench_end;                                                               \
	clock_gettime(CLOCK_MONOTONIC, &__tsbench_end);                                              \
	long __elapsed_ns = (__tsbench_end.tv_sec - __tsbench_start.tv_sec) * 1000000000L +          \
	                    (__tsbench_end.tv_nsec - __tsbench_start.tv_nsec);                       \
	printf("[bench %s] Took: %lu ns (%.3f ms)\n", name, __elapsed_ns, __elapsed_ns / 1000000.0); \
	}

#endif  // COMMON_H