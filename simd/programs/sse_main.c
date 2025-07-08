#include <immintrin.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "register_printer.h"
#include "unions.h"

extern void add_i16_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1, union xmm_val *c2, union xmm_val *c3);
extern void add_i32_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1);
extern void sub_i16_sse(union xmm_val *a, union xmm_val *b, union xmm_val *c1, union xmm_val *c2, union xmm_val *c3);

int main(void) {
	union xmm_val a, b, c1, c2, c3;

	memset(&a, 0, sizeof(a));
	memset(&b, 0, sizeof(b));
	memset(&c1, 0, sizeof(c1));
	memset(&c2, 0, sizeof(c2));
	memset(&c3, 0, sizeof(c3));

	// For additions
	a.m_i16[0] = 100;
	b.m_i16[0] = 200;

	a.m_i16[1] = 1000;
	b.m_i16[1] = 5000;

	a.m_i16[2] = 50;
	b.m_i16[2] = 80;

	a.m_i16[3] = 80;
	b.m_i16[3] = 100;

	a.m_i16[4] = 90;
	b.m_i16[4] = 100;

	a.m_i16[5] = 32760;
	b.m_i16[5] = 10;

	add_i16_sse(&a, &b, &c1, &c2, &c3);

	xmm_val_print(&a, VAL_TYPE_I16, "Operand: A", true, THEME_OPERAND_A, DISPLAY_BASE10);
	xmm_val_print(&b, VAL_TYPE_I16, "Operand: B", true, THEME_OPERAND_B, DISPLAY_BASE10);

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

	return 0;
}