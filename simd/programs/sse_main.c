#include <immintrin.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "register_printer.h"
#include "unions.h"

extern void add_i16_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1, union xmm_val *c2, union xmm_val *c3);
extern void add_i32_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1);
extern void sub_i16_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1, union xmm_val *c2, union xmm_val *c3);
extern void mul_i16_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1, union xmm_val *c2, union xmm_val *c3);

void additions() {
	union xmm_val a, b, c1, c2, c3;

	memset(&a, 0, sizeof(a));
	memset(&b, 0, sizeof(b));
	memset(&c1, 0, sizeof(c1));
	memset(&c2, 0, sizeof(c2));
	memset(&c3, 0, sizeof(c3));

	// For additions and subtractions
	a.m_u16[0] = 100;
	b.m_u16[0] = 200;

	a.m_u16[1] = 1000;
	b.m_u16[1] = 5000;

	a.m_u16[2] = 50;
	b.m_u16[2] = 80;

	a.m_u16[3] = 80;
	b.m_u16[3] = 100;

	a.m_u16[4] = 90;
	b.m_u16[4] = 100;

	// _mm_adds_epi16 treats as signed integer
	// this, before even added, it's already wrapped-around due to interpretation by _mm_adds_epi16
	// the result will be clipped at -32768 instead of 32767
	a.m_u16[5] = 40000;
	b.m_u16[5] = 50000;

	// this however will be clipped to 32767
	// since all operands are < 32768
	a.m_u16[6] = 30000;
	b.m_u16[6] = 20000;

	add_i16_sse(&a, &b, &c1, &c2, &c3);

	xmm_val_print(&a, VAL_TYPE_U16, "Operand: A", true, THEME_OPERAND_A, DISPLAY_BASE10);
	xmm_val_print(&b, VAL_TYPE_U16, "Operand: B", true, THEME_OPERAND_B, DISPLAY_BASE10);

	char *title = "add_i16_sse\n\tc1 (wraparound & signed)";
	xmm_val_print(&c1, VAL_TYPE_I16, title, true, THEME_RESULT, DISPLAY_BASE10 | DISPLAY_BASE2);
	title = "add_i16_sse\nc2 (saturated & signed)";
	xmm_val_print(&c2, VAL_TYPE_I16, title, true, THEME_OUTPUT, DISPLAY_BASE10 | DISPLAY_BASE2);
	title = "add_i16_sse\nc3 (saturated & unsigned)";
	xmm_val_print(&c3, VAL_TYPE_U16, title, true, THEME_RESULT, DISPLAY_BASE10 | DISPLAY_BASE2);

	memset(&c1, 0, sizeof(c1));
	memset(&c2, 0, sizeof(c2));
	memset(&c3, 0, sizeof(c3));

	sub_i16_sse(&a, &b, &c1, &c2, &c3);

	title = "sub_i16_sse\nc1 (wraparound & signed)";
	xmm_val_print(&c1, VAL_TYPE_I16, title, true, THEME_RESULT, DISPLAY_BASE10 | DISPLAY_BASE2);
	title = "sub_i16_sse\nc2 (saturated & signed)";
	xmm_val_print(&c2, VAL_TYPE_I16, title, true, THEME_OUTPUT, DISPLAY_BASE10 | DISPLAY_BASE2);
	title = "sub_i16_sse\nc2 (saturated & unsigned)";
	xmm_val_print(&c3, VAL_TYPE_U16, title, true, THEME_RESULT, DISPLAY_BASE10 | DISPLAY_BASE2);
}

void multiplications() {
	union xmm_val a, b, c1, c2, c3;

	memset(&a, 0, sizeof(a));
	memset(&b, 0, sizeof(b));
	memset(&c1, 0, sizeof(c1));
	memset(&c2, 0, sizeof(c2));
	memset(&c3, 0, sizeof(c3));

	// For multiplications
	a.m_i16[0] = 10;
	a.m_i16[1] = 3000;
	a.m_i16[2] = -2000;
	a.m_i16[3] = 42;
	a.m_i16[4] = -5000;
	a.m_i16[5] = 8;
	a.m_i16[6] = 10000;
	a.m_i16[7] = -6000;

	b.m_i16[0] = -5;
	b.m_i16[1] = 100;
	b.m_i16[2] = -9000;
	b.m_i16[3] = 1000;
	b.m_i16[4] = 25000;
	b.m_i16[5] = 16384;
	b.m_i16[6] = 3500;
	b.m_i16[7] = 6000;

	xmm_val_print(&a, VAL_TYPE_I16, "Operand: A", true, THEME_OPERAND_A, DISPLAY_BASE2 | DISPLAY_BASE10 | DISPLAY_BASE16);
	xmm_val_print(&b, VAL_TYPE_I16, "Operand: B", true, THEME_OPERAND_B, DISPLAY_BASE2 | DISPLAY_BASE10 | DISPLAY_BASE16);

	mul_i16_sse(&a, &b, &c1, &c2, &c3);

	char *title = "mul_i16_sse\n\tc1 (low)";
	xmm_val_print(&c1, VAL_TYPE_I16, title, true, THEME_RESULT, DISPLAY_BASE10 | DISPLAY_BASE2);
	title = "mul_i16_sse\nc2 (high)";
	xmm_val_print(&c2, VAL_TYPE_I16, title, true, THEME_OUTPUT, DISPLAY_BASE10 | DISPLAY_BASE2);
}

int main(void) {
	multiplications();
	return 0;
}