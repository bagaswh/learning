#ifndef UNIONS_H
#define UNIONS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

enum val_type {
	VAL_TYPE_ALL = 0xffff,
	VAL_TYPE_I8 = 0x1,
	VAL_TYPE_I16 = 0x2,
	VAL_TYPE_I32 = 0x4,
	VAL_TYPE_I64 = 0x8,
	VAL_TYPE_U8 = 0x10,
	VAL_TYPE_U16 = 0x20,
	VAL_TYPE_U32 = 0x40,
	VAL_TYPE_U64 = 0x80,
	VAL_TYPE_F32 = 0x100,
	VAL_TYPE_F64 = 0x200,
};

union xmm_val {
	u64 m_u64[2];
	i64 m_i64[2];
	u32 m_u32[4];
	i32 m_i32[4];
	u16 m_u16[8];
	i16 m_i16[8];
	u8 m_u8[16];
	i8 m_i8[16];
	float m_f32[4];
	double m_f64[2];
};

union ymm_val {
	u64 m_u64[4];
	i64 m_i64[4];
	u32 m_u32[8];
	i32 m_i32[8];
	u16 m_u16[16];
	i16 m_i16[16];
	u8 m_u8[32];
	i8 m_i8[32];
	float m_f32[8];
	double m_f64[4];
};

union zmm_val {
	u64 m_u64[8];
	i64 m_i64[8];
	u32 m_u32[16];
	i32 m_i32[16];
	u16 m_u16[32];
	i16 m_i16[32];
	u8 m_u8[64];
	i8 m_i8[64];
	float m_f32[16];
	double m_f64[8];
};

#endif  // UNIONS_H