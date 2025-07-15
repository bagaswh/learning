#include <immintrin.h>

#include "register_printer.h"
#include "unions.h"

//----Conventions-----------------------------
// - for additions and subtractions:
//      - c1 to store unsaturated & signed results
//      - c2 to store saturated & signed results
//      - c3 to store saturated & unsigned results
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

void mul_i16_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1, union xmm_val *c2, union xmm_val *c3) {
	__m128i a_vals = _mm_loadu_si128((__m128i *)a);
	__m128i b_vals = _mm_loadu_si128((__m128i *)b);

	__m128i temp_lo = _mm_mullo_epi16(a_vals, b_vals);
	__m128i temp_hi = _mm_mulhi_epi16(a_vals, b_vals);
	union xmm_val xmm_val_temp_lo;
	_mm_store_si128((__m128i *)&xmm_val_temp_lo, temp_lo);
	union xmm_val xmm_val_temp_hi;
	_mm_store_si128((__m128i *)&xmm_val_temp_hi, temp_hi);
	xmm_val_print(&xmm_val_temp_lo, VAL_TYPE_I16, "temp_lo", true, THEME_INTERMEDIATE, DISPLAY_BASE10 | DISPLAY_BASE2 | DISPLAY_BASE16);
	xmm_val_print(&xmm_val_temp_hi, VAL_TYPE_I16, "temp_hi", true, THEME_INTERMEDIATE, DISPLAY_BASE10 | DISPLAY_BASE2 | DISPLAY_BASE16);

	__m128i result_lo = _mm_unpacklo_epi16(temp_lo, temp_hi);
	__m128i result_hi = _mm_unpackhi_epi16(temp_lo, temp_hi);
	union xmm_val xmm_val_result_lo;
	_mm_store_si128((__m128i *)&xmm_val_result_lo, result_lo);
	union xmm_val xmm_val_result_hi;
	_mm_store_si128((__m128i *)&xmm_val_result_hi, result_hi);
	xmm_val_print(&xmm_val_result_lo, VAL_TYPE_I32, "result_lo", true, THEME_INTERMEDIATE, DISPLAY_BASE10 | DISPLAY_BASE2 | DISPLAY_BASE16);
	xmm_val_print(&xmm_val_result_hi, VAL_TYPE_I32, "result_hi", true, THEME_INTERMEDIATE, DISPLAY_BASE10 | DISPLAY_BASE2 | DISPLAY_BASE16);

	_mm_store_si128((__m128i *)c1, result_lo);
	_mm_store_si128((__m128i *)c2, result_hi);
}
//------------------------------------------------
//               End SSE
//------------------------------------------------