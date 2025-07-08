#include <immintrin.h>

#include "unions.h"

//----Conventions-----------------------------
// - c1 to store unsaturated & signed results
// - c2 to store saturated & signed results
// - c3 to store saturated & unsigned results
//--------------------------------------------

//------------------------------------------------
//               Begin SSE
//------------------------------------------------

void add_i16_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1, union xmm_val *c2, union xmm_val *c3) {
	__m128i a_vals = _mm_loadu_si128((__m128i *)a);
	__m128i b_vals = _mm_loadu_si128((__m128i *)b);

	__m128i c1_vals = _mm_add_epi16(a_vals, b_vals);
	_mm_storeu_si128((__m128i *)c1, c1_vals);
	__m128i c2_vals = _mm_adds_epi16(a_vals, b_vals);
	_mm_storeu_si128((__m128i *)c2, c2_vals);
	__m128i c3_vals = _mm_adds_epu16(a_vals, b_vals);
	_mm_storeu_si128((__m128i *)c3, c3_vals);
}

void add_i32_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1) {
	__m128i a_vals = _mm_loadu_si128((__m128i *)a);
	__m128i b_vals = _mm_loadu_si128((__m128i *)b);

	__m128i c1_vals = _mm_add_epi32(a_vals, b_vals);
	_mm_storeu_si128((__m128i *)c1, c1_vals);
}

void sub_i16_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1, union xmm_val *c2, union xmm_val *c3) {
	__m128i a_vals = _mm_loadu_si128((__m128i *)a);
	__m128i b_vals = _mm_loadu_si128((__m128i *)b);

	__m128i c1_vals = _mm_sub_epi16(a_vals, b_vals);
	_mm_storeu_si128((__m128i *)c1, c1_vals);
	__m128i c2_vals = _mm_subs_epi16(a_vals, b_vals);
	_mm_storeu_si128((__m128i *)c2, c2_vals);
	__m128i c3_vals = _mm_subs_epu16(a_vals, b_vals);
	_mm_storeu_si128((__m128i *)c3, c3_vals);
}

//------------------------------------------------
//               End SSE
//------------------------------------------------