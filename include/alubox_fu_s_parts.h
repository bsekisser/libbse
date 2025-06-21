#pragma once

/* **** */

#include "alubox_fu_parts.h"

/* **** */

#include "bitfield.h"
#include "shift_roll.h"

/* **** */

#include <stdlib.h>

/* **** */

#define __unsigned_bits ((sizeof(unsigned) << 3) - 1)

typedef struct alubox_psr_tag* alubox_psr_ptr;
typedef alubox_psr_ptr const alubox_psr_ref;

typedef struct alubox_psr_tag {
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

typedef struct alubox_tag* alubox_ptr;
typedef alubox_ptr const alubox_ref;

typedef struct alubox_tag {
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

static inline
unsigned __alubox_fu__flags_nz(alubox_ref alu, const unsigned result)
{
	if(alu && alu->flags.s) {
		alu->result = result;

		alu->psr.n = BEXT(result, __unsigned_bits);
		alu->psr.z = (0 == result);
	}

	return(result);
}

static inline void __alubox_fu__flags_s_wb(alubox_ref alu, const unsigned s, const unsigned wb)
{
	if(alu) {
		alu->flags.s = s;
		alu->flags.wb = wb;
	}
}

/*
 * Credit to:
 * 		http://www.emulators.com/docs/nx11_flags.htm
 *
 * OF(A+B) = ((A XOR D) AND NOT (A XOR B)) < 0
 * OF(A-B) = ((A XOR D) AND (A XOR B)) < 0
 *
 * CF(A+B) = (((A XOR B) XOR D) < 0) XOR (((A XOR D) AND NOT (A XOR B)) < 0)
 * CF(A-B) = (((A XOR B) XOR D) < 0) XOR (((A XOR D) AND (A XOR B)) < 0)
 *
 */

static inline
unsigned __alubox_fu__flags_add(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	const unsigned result = s1 + s2;

	if(alu && alu->flags.s) {
		const unsigned xvec = (s1 ^ s2);
		const unsigned ovec = (s1 ^ result) & ~xvec;

		alu->psr.c = BEXT((xvec ^ ovec ^ result), __unsigned_bits);
		alu->psr.v = BEXT(ovec, __unsigned_bits);
	}

	return(__alubox_fu__flags_nz(alu, result));
}

static inline
unsigned __alubox_fu__flags_sub(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_add(alu, s1, -s2));
}

/* **** */

static inline
unsigned __alubox_fu_s_adc(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;
	return(__alubox_fu__flags_add(alu, s1, s2 + carry_in));
}

static inline
unsigned __alubox_fu_s_add(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_add(alu, s1, s2));
}

static inline
unsigned __alubox_fu_s_and(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;
	return(__alubox_fu__flags_nz(alu, __alubox_fu_and(0, s1, s2, carry_in)));
}

static inline
unsigned __alubox_fu_s_asr(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	int carry_out = 0;
	const unsigned result = _asr_vc(s1, s2, &carry_out);

	if(alu && alu->flags.s)
		alu->psr.c = (0 != carry_out);

	return(__alubox_fu__flags_nz(alu, result));
}

static inline
unsigned __alubox_fu_s_bclr(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_bclr(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_bext(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_bext(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_bic(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu_s_and(alu, s1, ~s2));
}

static inline
unsigned __alubox_fu_s_bset(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_bset(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_btst(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_btst(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_bxor(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_bxor(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_eor(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_eor(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_lsl(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	unsigned carry_out = 0;
	const unsigned result = _lsl_vc(s1, s2, &carry_out);

	if(alu && alu->flags.s)
		alu->psr.c = (0 != carry_out);

	return(__alubox_fu__flags_nz(alu, result));
}

static inline
unsigned __alubox_fu_s_lsr(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	unsigned carry_out = 0;
	const unsigned result = _lsr_vc(s1, s2, &carry_out);

	if(alu && alu->flags.s)
		alu->psr.c = (0 != carry_out);

	return(__alubox_fu__flags_nz(alu, result));
}

static inline
unsigned __alubox_fu_s_mod(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mod(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_mov(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mov(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_mul(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mul(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_mul_acc(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	unsigned acc = alu ? alu->result : 0;
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mul_acc(acc, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_mvn(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_mvn(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_orr(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_orr(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_ror(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_nz(alu, __alubox_fu_ror(0, s1, s2, 0)));
}

static inline
unsigned __alubox_fu_s_rrx(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;

	if(alu && alu->flags.s)
		alu->psr.c = s1 & 1;

	return(__alubox_fu__flags_nz(alu, __alubox_fu_rrx(0, s1, s2, carry_in)));
}

static inline
unsigned __alubox_fu_s_rsb(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_sub(alu, s2, s1));
}

static inline
unsigned __alubox_fu_s_rsc(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;
	return(__alubox_fu__flags_sub(alu, s2, s1 + carry_in));
}

static inline
unsigned __alubox_fu_s_sbc(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	const unsigned carry_in = alu ? alu->psr.c : 0;
	return(__alubox_fu__flags_sub(alu, s1, s2 + carry_in));
}

static inline
unsigned __alubox_fu_s_sub(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	return(__alubox_fu__flags_sub(alu, s1, s2));
}

/* **** */

static inline
unsigned __alubox_fu_s_cmn(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	__alubox_fu__flags_s_wb(alu, 1, 0);
	return(__alubox_fu_s_add(alu, s1, s2));
}

static inline
unsigned __alubox_fu_s_cmp(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	__alubox_fu__flags_s_wb(alu, 1, 0);
	return(__alubox_fu_s_sub(alu, s1, s2));
}

static inline
unsigned __alubox_fu_s_teq(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	__alubox_fu__flags_s_wb(alu, 1, 0);
	return(__alubox_fu_s_eor(alu, s1, s2));
}

static inline
unsigned __alubox_fu_s_tst(alubox_ref alu, const unsigned s1, const unsigned s2)
{
	__alubox_fu__flags_s_wb(alu, 1, 0);
	return(__alubox_fu_s_and(alu, s1, s2));
}
