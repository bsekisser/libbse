#pragma once

/* **** */

#include "alubox_fu_parts.h"

/* **** */

#include "bitfield.h"
#include "shift_roll.h"

/* **** */

#include <stdlib.h>

/* **** */

typedef struct alubox_psr_t* alubox_psr_p;
typedef struct alubox_psr_t {
	union {
		unsigned raw_flags;
		struct {
			unsigned c:1;
			unsigned n:1;
			unsigned s:1;
			unsigned v:1;
			unsigned z:1;
		};
	};
}alubox_psr_t;

typedef struct alubox_t* alubox_p;
typedef struct alubox_t {
	unsigned result;
	alubox_psr_t psr;
	union {
		unsigned raw;
		struct {
			unsigned s:1;
			unsigned wb:1;
		};
	}flags;
}alubox_t;

/* **** */

static inline unsigned __alubox_fu__flags_nz(alubox_p alu, unsigned result)
{
	if(alu && alu->flags.s) {
		alu->result = result;
		
		alu->psr.n = BEXT(result, 31);
		alu->psr.z = (0 == result);
	}

	return(result);
}

static inline unsigned __alubox_fu__flags_nz_s_wb(alubox_p alu, unsigned result, unsigned s, unsigned wb)
{
	if(alu) {
		alu->flags.s = s;
		alu->flags.wb = wb;
	}

	return(__alubox_fu__flags_nz(alu, result));
}

static inline unsigned __alubox_fu__flags_add(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned result = s1 + s2;

	if(alu && alu->flags.s) {
		const unsigned long long int usum = s1 + s2;
		const long long int ssum = (int)s1 + (int)s2;

		alu->psr.c = (usum != result);
		alu->psr.v = (ssum != (signed)result);
	}

	return(__alubox_fu__flags_nz(alu, result));
}

static inline unsigned __alubox_fu__flags_sub(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_add(alu, s1, -s2));
}

/* **** */

extern inline unsigned __alubox_fu_s_adc(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;
	return(__alubox_fu__flags_add(alu, s1, s2 + carry_in));
}

extern inline unsigned __alubox_fu_s_add(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_add(alu, s1, s2));
}

extern inline unsigned __alubox_fu_s_and(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;
	return(__alubox_fu__flags_nz(alu, __alubox_fu_and(0, s1, s2, carry_in)));
}

extern inline unsigned __alubox_fu_s_asr(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_asr(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_bclr(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_bclr(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_bext(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_bext(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_bic(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu_s_and(alu, s1, ~s2));
}

extern inline unsigned __alubox_fu_s_bset(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_bset(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_btst(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_btst(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_bxor(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_bxor(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_eor(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_eor(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_lsl(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_lsl(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_lsr(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_lsr(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_mod(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mod(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_mov(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mov(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_mul(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mul(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_mul_acc(alubox_p alu, unsigned s1, unsigned s2)
{
	unsigned acc = alu ? alu->result : 0;
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mul_acc(acc, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_mvn(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mvn(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_orr(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_orr(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_ror(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_ror(0, s1, s2, 0)));
}

extern inline unsigned __alubox_fu_s_rrx(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;

	if(alu && alu->flags.s)
		alu->psr.c = s1 & 1;
		
	return(__alubox_fu__flags_nz(alu, __alubox_fu_rrx(0, s1, s2, carry_in)));
}

extern inline unsigned __alubox_fu_s_rsb(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_sub(alu, s2, s1));
}

extern inline unsigned __alubox_fu_s_rsc(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;
	return(__alubox_fu__flags_sub(alu, s2, s1 + carry_in));
}

extern inline unsigned __alubox_fu_s_sbc(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;
	return(__alubox_fu__flags_sub(alu, s1, s2 + carry_in));
}

extern inline unsigned __alubox_fu_s_sub(alubox_p alu, unsigned s1, unsigned s2)
{
	return(__alubox_fu__flags_sub(alu, s1, s2));
}

/* **** */

extern inline unsigned __alubox_fu_s_cmn(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned result = __alubox_fu_add(0, s1, s2, 0);
	return(__alubox_fu__flags_nz_s_wb(alu, result, 1, 0));
}

extern inline unsigned __alubox_fu_s_cmp(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned result = __alubox_fu_sub(0, s1, s2, 0);
	return(__alubox_fu__flags_nz_s_wb(alu, result, 1, 0));
}

extern inline unsigned __alubox_fu_s_teq(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned result = __alubox_fu_eor(0, s1, s2, 0);
	return(__alubox_fu__flags_nz_s_wb(alu, result, 1, 0));
}

extern inline unsigned __alubox_fu_s_tst(alubox_p alu, unsigned s1, unsigned s2)
{
	const unsigned result = __alubox_fu_and(0, s1, s2, 0);
	return(__alubox_fu__flags_nz_s_wb(alu, result, 1, 0));
}
