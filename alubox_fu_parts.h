#pragma once

/* **** */

#include "bitfield.h"
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
unsigned __alubox_fu_adc(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(s1 + (s2 + carry_in));
	UNUSED(acc);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_add(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(__alubox_fu_adc(acc, s1, s2, 0));
	UNUSED(carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_and(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(s1 & s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_asr(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(_asr(s1, s2 & 0xff));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bclr(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(_BCLR(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bext(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(BEXT(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bic(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(__alubox_fu_and(acc, s1, ~s2, carry_in));
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bset(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(_BSET(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_btst(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(BTST(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_bxor(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(_BXOR(s1, s2));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_eor(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(s1 ^ s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_lsl(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(_lsl(s1, s2 & 0xff));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_lsr(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(_lsr(s1, s2 & 0xff));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mod(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(s1 % s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mov(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(s2);
	UNUSED(acc, s1, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mul(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(s1 * s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mul_acc(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(acc + __alubox_fu_mul(0, s1, s2, carry_in));
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_mvn(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(__alubox_fu_mov(acc, s1, ~s2, carry_in));
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_orr(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(s1 | s2);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_ror(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(_ror(s1, s2 & 0xff));
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_rrx(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(_lsr(s1, 1) | ((!!carry_in) << 31));
	UNUSED(acc, s2);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_rsb(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(s2 - s1);
	UNUSED(acc, carry_in);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_rsc(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(__alubox_fu_rsb(acc, s2, s1 + carry_in, 0));
	UNUSED(acc);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_sbc(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(s1 - (s2 + carry_in));
	UNUSED(acc);
}

UNUSED_FN __ALUBOX_STATIC__ __ALUBOX_INLINE__
unsigned __alubox_fu_sub(unsigned acc, unsigned s1, unsigned s2, unsigned carry_in)
{
	return(__alubox_fu_sbc(acc, s1, s2, 0));
	UNUSED(carry_in);
}
