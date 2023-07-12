#pragma once

/* **** */

#include <stdint.h>
#include <stdio.h>

/* **** */

#if 0
	#ifndef LOG
		#define LOG(_f, ...)
	#endif
#endif

#ifndef __INLINE__
	#define __INLINE__ inline
#endif

#ifndef __STATIC__
	#define __STATIC__ static
#endif

/* **** */

#define __SIZEOF_DATA__ (sizeof(data) << 3)
#define __SIZEOF_DATA_MASK__ (__SIZEOF_DATA__ - 1)

/* **** */

__STATIC__ __INLINE__
int32_t _asr(int32_t data, unsigned shift)
{
	return(data >> shift);
}

__STATIC__ __INLINE__
unsigned _asr_c(int32_t data, unsigned shift)
{
	if(0 == shift)
		return(0);

	return(_asr(data, shift - 1) & 1);
}

__STATIC__ __INLINE__
int32_t _asr_vc(int32_t data, unsigned shift, int32_t* carry_out)
{
	if(carry_out)
		*carry_out = _asr_c(data, shift);

	return(_asr(data, shift));
}

__STATIC__ __INLINE__
int32_t _asr_masked(int32_t data, unsigned shift)
{
	return(_asr(data, shift & __SIZEOF_DATA_MASK__));
}

/* **** */

__STATIC__ __INLINE__
uint32_t _lsl(uint32_t data, unsigned shift)
{
	return(data << shift);
}

__STATIC__ __INLINE__
uint32_t _lsl_masked(uint32_t data, unsigned shift)
{
	return(_lsl(data, shift & __SIZEOF_DATA_MASK__));
}

/* **** */

__STATIC__ __INLINE__ uint32_t _lsr(uint32_t data, unsigned shift)
{
	return(data >> shift);
}

__STATIC__ __INLINE__
uint32_t _lsr_masked(uint32_t data, unsigned shift)
{
	return(_lsr(data, shift & __SIZEOF_DATA_MASK__));
}

/* **** */

__STATIC__ __INLINE__
unsigned _lsl_c(uint32_t data, unsigned shift)
{
	if(0 == shift)
		return(0);

	return(!!(_lsl(data, shift - 1) & (1 << __SIZEOF_DATA_MASK__)));
}

__STATIC__ __INLINE__
uint32_t _lsl_vc(uint32_t data, unsigned shift, uint32_t* carry_out)
{
	if(carry_out)
		*carry_out = _lsl_c(data, shift);

	return(_lsl(data, shift));
}

__STATIC__ __INLINE__
unsigned _lsr_c(uint32_t data, unsigned shift)
{
	if(0 == shift)
		return(0);

	return(_lsr(data, shift - 1) & 1);
}

__STATIC__ __INLINE__
uint32_t _lsr_vc(uint32_t data, unsigned shift, uint32_t* carry_out)
{
	if(carry_out)
		*carry_out = _lsr_c(data, shift);

	return(_lsr(data, shift));
}

/* **** */

__STATIC__ __INLINE__
uint32_t _rol(uint32_t data, unsigned shift)
{
	return(_lsl(data, shift) | _lsr_masked(data, -shift));
}

__STATIC__ __INLINE__
uint32_t _ror(uint32_t data, unsigned shift)
{
	return(_lsl_masked(data, -shift) | _lsr_masked(data, shift));
}

/* **** */

__STATIC__ __INLINE__
uint32_t _rol_c(uint32_t data, unsigned shift)
{
	if(0 == shift)
		return(0);

	return(!!(_rol(data, shift - 1) & (1 << __SIZEOF_DATA_MASK__)));
}

__STATIC__ __INLINE__
uint32_t _rol_vc(uint32_t data, unsigned shift, uint32_t* carry_out)
{
	if(carry_out)
		*carry_out = _rol_c(data, shift);

	return(_rol(data, shift));
}

__STATIC__ __INLINE__
uint32_t _ror_c(uint32_t data, unsigned shift)
{
	if(0 == shift)
		return(0);

	return(_ror(data, shift - 1) & 1);
}

__STATIC__ __INLINE__
uint32_t _ror_vc(uint32_t data, unsigned shift, uint32_t* carry_out)
{
	if(carry_out)
		*carry_out = _ror_c(data, shift);

	return(_ror(data, shift));
}

/* **** */

__STATIC__ __INLINE__
uint32_t _rrx_c(uint32_t data)
{
	return(data & 1);
}

__STATIC__ __INLINE__
uint32_t _rrx_v(uint32_t data, uint32_t carry_in)
{
	return(_lsl(!!carry_in, 31) | _lsr(data, 1));
}

__STATIC__ __INLINE__
uint32_t _rrx_vc(uint32_t data, uint32_t carry_in, uint32_t* carry_out)
{
	if(carry_out)
		*carry_out = _rrx_c(data);

	return(_rrx_v(data, carry_in));
}
