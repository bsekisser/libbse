#pragma once

/* **** */

#include "bitop_macros.h"
#include "shift_roll_macros.h"
#include "unused.h"

/* **** */

//#include <stdlib.h>

/* **** */

#ifndef __ALUBOX_INLINE__
	#define __ALUBOX_INLINE__ inline
#endif

#ifndef __ALUBOX_STATIC__
	#define __ALUBOX_STATIC__ static
#endif

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_adc(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(s1 + (s2 + carry_in));
	UNUSED(acc);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_add(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(__alubox_fu_adc(acc, s1, s2, 0 & carry_in));
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_and(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(s1 & s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_asr(const signed acc, const signed s1, const unsigned s2, const unsigned carry_in)
{
	return(_ASR(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bclr(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(_BCLR(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bext(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(_BEXT(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bic(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(__alubox_fu_and(acc, s1, ~s2, carry_in));
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bset(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(_BSET(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_btst(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(_BTST(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bxor(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(_BXOR(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_eor(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(s1 ^ s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_lsl(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(_LSL(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_lsr(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(_LSR(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mod(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(s1 % s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mov(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(s2);
	UNUSED(acc, s1, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mul(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(s1 * s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mul_acc(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(acc + __alubox_fu_mul(0, s1, s2, carry_in));
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mvn(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(__alubox_fu_mov(acc, s1, ~s2, carry_in));
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_orr(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(s1 | s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_ror(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(_ROR(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_rrx(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(_RRX_V(s1, carry_in));
	UNUSED(acc, s2);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_rsb(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(s2 - s1);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_rsc(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(__alubox_fu_rsb(acc, s2, s1 + carry_in, 0));
	UNUSED(acc);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_sbc(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(s1 - (s2 + carry_in));
	UNUSED(acc);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_sub(const unsigned acc, const unsigned s1, const unsigned s2, const unsigned carry_in)
{
	return(__alubox_fu_sbc(acc, s1, s2, 0 & carry_in));
}
