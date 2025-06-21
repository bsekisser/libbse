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
int32_t _asr(const int32_t data, const unsigned shift)
{ return(data >> shift); }

__STATIC__ __INLINE__
unsigned _asr_c(const int32_t data, const unsigned shift)
{
	if(0 == shift)
		return(0);

	return((unsigned)_asr(data, shift - 1) & 1);
}

__STATIC__ __INLINE__
int32_t _asr_vc(const int32_t data, const unsigned shift, uint32_t *const carry_out)
{
	if(carry_out)
		*carry_out = _asr_c(data, shift);

	return(_asr(data, shift));
}

__STATIC__ __INLINE__
int32_t _asr_masked(const int32_t data, const unsigned shift)
{ return(_asr(data, shift & __SIZEOF_DATA_MASK__)); }

/* **** */

__STATIC__ __INLINE__
uint32_t _lsl(const uint32_t data, const unsigned shift)
{ return(data << shift); }

__STATIC__ __INLINE__
uint32_t _lsl_masked(const uint32_t data, const unsigned shift)
{ return(_lsl(data, shift & __SIZEOF_DATA_MASK__)); }

/* **** */

__STATIC__ __INLINE__
uint32_t _lsr(const uint32_t data, const unsigned shift)
{ return(data >> shift); }

__STATIC__ __INLINE__
uint32_t _lsr_masked(const uint32_t data, const unsigned shift)
{ return(_lsr(data, shift & __SIZEOF_DATA_MASK__)); }

/* **** */

__STATIC__ __INLINE__
unsigned _lsl_c(const uint32_t data, const unsigned shift)
{
	if(0 == shift)
		return(0);

	return(!!(_lsl(data, shift - 1) & (1U << __SIZEOF_DATA_MASK__)));
}

__STATIC__ __INLINE__
uint32_t _lsl_vc(const uint32_t data, const unsigned shift, uint32_t *const carry_out)
{
	if(carry_out)
		*carry_out = _lsl_c(data, shift);

	return(_lsl(data, shift));
}

__STATIC__ __INLINE__
unsigned _lsr_c(const uint32_t data, const unsigned shift)
{
	if(0 == shift)
		return(0);

	return(_lsr(data, shift - 1) & 1);
}

__STATIC__ __INLINE__
uint32_t _lsr_vc(const uint32_t data, const unsigned shift, uint32_t *const carry_out)
{
	if(carry_out)
		*carry_out = _lsr_c(data, shift);

	return(_lsr(data, shift));
}

/* **** */

__STATIC__ __INLINE__
uint32_t _rol(const uint32_t data, const unsigned shift)
{ return(_lsl(data, shift) | _lsr_masked(data, -shift)); }

__STATIC__ __INLINE__
uint32_t _ror(const uint32_t data, const unsigned shift)
{ return(_lsl_masked(data, -shift) | _lsr(data, shift)); }

/* **** */

__STATIC__ __INLINE__
uint32_t _rol_c(const uint32_t data, const unsigned shift)
{
	if(0 == shift)
		return(0);

	return(!!(_rol(data, shift - 1) & (1U << __SIZEOF_DATA_MASK__)));
}

__STATIC__ __INLINE__
uint32_t _rol_vc(const uint32_t data, const unsigned shift, uint32_t *const carry_out)
{
	if(carry_out)
		*carry_out = _rol_c(data, shift);

	return(_rol(data, shift));
}

__STATIC__ __INLINE__
uint32_t _ror_c(const uint32_t data, const unsigned shift)
{
	if(0 == shift)
		return(0);

	return(_ror(data, shift - 1) & 1);
}

__STATIC__ __INLINE__
uint32_t _ror_vc(const uint32_t data, const unsigned shift, uint32_t *const carry_out)
{
	if(carry_out)
		*carry_out = _ror_c(data, shift);

	return(_ror(data, shift));
}

/* **** */

__STATIC__ __INLINE__
uint32_t _rrx_c(const uint32_t data)
{ return(data & 1); }

__STATIC__ __INLINE__
uint32_t _rrx_v(const uint32_t data, uint32_t carry_in)
{ return(_lsl(!!carry_in, 31) | _lsr(data, 1)); }

__STATIC__ __INLINE__
uint32_t _rrx_vc(const uint32_t data, uint32_t carry_in, uint32_t *const carry_out)
{
	if(carry_out)
		*carry_out = _rrx_c(data);

	return(_rrx_v(data, carry_in));
}
