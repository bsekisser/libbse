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
int32_t _asr(int32_t data, uint shift)
{
	return(data >> shift);
}

__STATIC__ __INLINE__
uint _asr_c(int32_t data, uint shift)
{
	return(shift ? (_asr(data, shift - 1) & 1) : 0);
}

__STATIC__ __INLINE__
int32_t _asr_masked(int32_t data, uint shift)
{
	return(_asr(data, shift & __SIZEOF_DATA_MASK__));
}

/* **** */

__STATIC__ __INLINE__
uint32_t _lsl(uint32_t data, uint shift)
{
	return(data << shift);
}

__STATIC__ __INLINE__
uint32_t _lsl_masked(uint32_t data, uint shift)
{
	return(_lsl(data, shift & __SIZEOF_DATA_MASK__));
}

/* **** */

__STATIC__ __INLINE__ uint32_t _lsr(uint32_t data, uint shift)
{
	return(data >> shift);
}

__STATIC__ __INLINE__
uint32_t _lsr_masked(uint32_t data, uint shift)
{
	return(_lsr(data, shift & __SIZEOF_DATA_MASK__));
}

/* **** */

__STATIC__ __INLINE__
uint _lsl_c(uint32_t data, uint shift)
{
	return(_lsr(data, shift - 1) & 1);
}

__STATIC__ __INLINE__
uint _lsr_c(uint32_t data, uint shift)
{
	return(_lsr(data, shift - 1) & 1);
}

/* **** */

__STATIC__ __INLINE__
uint32_t _rol(uint32_t data, uint shift)
{
	return(_lsl(data, shift) | _lsr_masked(data, -shift));
}

__STATIC__ __INLINE__
uint32_t _ror(uint32_t data, uint shift)
{
	return(_lsl_masked(data, -shift) | _lsr_masked(data, shift));
}

/* **** */
