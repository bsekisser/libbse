#pragma once

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

//__STATIC__ __INLINE__ unsigned long int _asr(unsigned long int data, unsigned long int shift);
/*FAIL*///#define _asr _asr_v1
/*PASS:BEST*/#define _asr _asr_v2

//__STATIC__ __INLINE__ unsigned long int _asr_c(unsigned long int data, unsigned long int shift, long int* cout);
/*PASS*///#define _asr_c _asr_c_v1
/*PASS*///#define _asr_c _asr_c_v2
/*PASS*///#define _asr_c _asr_c_v3
/*PASS*///#define _asr_c _asr_c_v4
/*PASS:BEST*/#define _asr_c _asr_c_v5

//__STATIC__ __INLINE__ unsigned long int _lsl(unsigned long int data, unsigned long int shift);
/*FAIL*///#define _lsl _lsl_v1
/*PASS:BEST*/#define _lsl _lsl_v2

//__STATIC__ __INLINE__ unsigned long int _lsl_c(long int data, unsigned long int shift, long int* cout);
/*PASS*///#define _lsl_c _lsl_c_v1
/*PASS*///#define _lsl_c _lsl_c_v2
/*PASS:BEST*/#define _lsl_c _lsl_c_v3
/*PASS*///#define _lsl_c _lsl_c_v4

//__STATIC__ __INLINE__ unsigned long int _lsr(unsigned long int data, unsigned long int shift);
__STATIC__ __INLINE__ unsigned long int _lsr_v1(unsigned long int data, unsigned long int shift);
__STATIC__ __INLINE__ unsigned long int _lsr_v2(unsigned long int data, unsigned long int shift);
/*FAIL*///#define _lsr _lsr_v1
/*PASS:BEST*/#define _lsr _lsr_v2

__STATIC__ __INLINE__ unsigned long int _lsr_c_v2(unsigned long int data, unsigned long int shift, unsigned long int* cout);
#define _lsr_c _lsr_c_v2

/* **** */

#define __SIZEOF_DATA__ (sizeof(data) << 3)
#define __SIZEOF_DATA_MASK__ (__SIZEOF_DATA__ - 1)

__STATIC__ __INLINE__ int _asr_v1(long int data, unsigned long int shift)
{
	return(data >> (shift & __SIZEOF_DATA_MASK__));
}

__STATIC__ __INLINE__ int _asr_v2(long int data, unsigned long int shift)
{
	return(data >> shift);
}

/* **** */

__STATIC__ __INLINE__ int _asr_c_v1(long int data,
	unsigned long int shift,
	long int* cout)
{
	if(shift) {
		if(shift < __SIZEOF_DATA__) {
			*cout = (data >> (shift - 1));
		} else
			*cout = !!(data & (1 << __SIZEOF_DATA_MASK__));
	} else
		*cout = 0;

	*cout &= 1;

	return(_asr(data, shift));
}

__STATIC__ __INLINE__ int _asr_c_v2(long int data,
	unsigned long int shift,
	long int* cout)
{
	unsigned long int dout = data;

	if(shift) {
		if(shift < __SIZEOF_DATA__)
			dout >>= shift - 1;
		else
			dout >>= __SIZEOF_DATA_MASK__;

		*cout = dout & 1;

		if(shift < __SIZEOF_DATA__)
			dout >>= 1;
	}

	return(dout);
}

__STATIC__ __INLINE__ int _asr_c_v3(int data,
	unsigned long int shift,
	long int* cout)
{
	*cout = data;
	unsigned long int dout = data;

	if(shift) {
		if(shift < __SIZEOF_DATA__) {
			*cout >>= shift - 1;
			dout >>= shift;
		} else {
			*cout >>= __SIZEOF_DATA_MASK__;
			dout >>= __SIZEOF_DATA_MASK__;
		}

		*cout &= 1;
	}

	return(dout);
}

__STATIC__ __INLINE__ int _asr_c_v4(int data,
	unsigned long int shift,
	int* cout)
{
	*cout = shift ? data : 0;
	int dout = data;

	*cout >>= shift - 1;
	dout >>= shift;

	*cout &= 1;

	return(dout);
}

__STATIC__ __INLINE__ int _asr_c_v5(int data,
	unsigned long int shift,
	int* cout)
{
	*cout = shift ? data : 0;
	*cout = _asr_v2(*cout, shift - 1) & 1;

	return(_asr_v2(data, shift));
}

/* **** */

__STATIC__ __INLINE__ unsigned long int _lsl_v1(unsigned long int data,
	unsigned long int shift)
{
	return(data << (shift & 0x1f));
}

__STATIC__ __INLINE__ unsigned long int _lsl_v2(unsigned long int data,
	unsigned long int shift)
{
	return(data << shift);
}

/* **** */

__STATIC__ __INLINE__ unsigned long int _lsl_c_v1(unsigned long int data,
	unsigned long int shift,
	unsigned long int* cout)
{
	if(shift && (shift <= __SIZEOF_DATA__))
		*cout = (data >> (-shift & __SIZEOF_DATA_MASK__)) & 1;
	else
		*cout = 0;

	return(_lsl(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _lsl_c_v2(unsigned long int data,
	unsigned long int shift,
	unsigned long int* cout)
{
	if(shift && (shift <= __SIZEOF_DATA__))
		*cout = _lsr_v1(data, shift - 1) & 1;
	else
		*cout = 0;

	return(_lsl(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _lsl_c_v3(unsigned long int data,
	unsigned long int shift,
	unsigned long int* cout)
{
	*cout = _lsr_v2(data, shift - 1) & 1;

	return(_lsl_v2(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _lsl_c_v4(unsigned long int data,
	unsigned long int shift,
	unsigned long int* cout)
{
	*cout = !!(data & (1 << (shift - 1)));

	return(_lsl_v2(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _lsl_c_v5(unsigned long int data,
	unsigned long int shift,
	unsigned long int* cout)
{
	_lsr_c(data, shift - 1, cout);

	return(_lsl_v2(data, shift));
}

/* **** */

__STATIC__ __INLINE__ unsigned long int _lsr_v1(unsigned long int data,
	unsigned long int shift)
{
	return(data >> (shift & __SIZEOF_DATA_MASK__));
}

__STATIC__ __INLINE__ unsigned long int _lsr_v2(unsigned long int data,
	unsigned long int shift)
{
	return(data >> shift);
}

__STATIC__ __INLINE__ unsigned long int _lsr_c_v1(unsigned long int data,
	unsigned long int shift,
	unsigned long int* cout)
{
	if(cout)
		*cout = _lsr_v1(data, shift - 1) & 1;

	return(_lsr_v1(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _lsr_c_v2(unsigned long int data,
	unsigned long int shift,
	unsigned long int* cout)
{
	if(cout)
		*cout = _lsr_v2(data, shift - 1) & 1;

	return(_lsr_v2(data, shift));
}

/* **** */

#define _rol _rol_v2
__STATIC__ __INLINE__ unsigned long int _rol_v1(unsigned long int data,
	unsigned long int shift)
{
	return(_lsl_v2(data, shift) | _lsr_v1(data, -shift));
}

__STATIC__ __INLINE__ unsigned long int _rol_v2(unsigned long int data,
	unsigned long int shift)
{
	return(_lsl_v2(data, shift) | _lsr_v2(data, __SIZEOF_DATA__ - shift));
}

__STATIC__ __INLINE__ unsigned long int _rol_v3(unsigned long int data,
	unsigned long int shift)
{
	return((data << shift) | (data >> -shift));
}

__STATIC__ __INLINE__ unsigned long int _rol_c(unsigned long int data,
	unsigned shift,
	unsigned long int cin,
	unsigned long int* cout)
{
	unsigned long int cmask = _lsl_v2(!!cin, shift - 1);
	unsigned long int dout = _rol_v1(data, shift);

	if(cout)
		*cout = !!(dout & cmask);

	return((dout & ~cin) | cin);
}

/* **** */

#define _ror _ror_v9
__STATIC__ __INLINE__ unsigned long int _ror_v1(unsigned long int data,
	unsigned long int shift)
{
	return(_lsl_v1(data, -shift) | _lsr_v1(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _ror_v2(unsigned long int data,
	unsigned long int shift)
{
	return(_lsl_v2(data, -shift) | _lsr_v2(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _ror_v3(unsigned long int data,
	unsigned long int shift)
{
	return(_lsr_v2(data, shift) | _lsl_v2(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _ror_v4(unsigned long int data,
	unsigned long int shift)
{
	return((data >> shift) | (data << -shift));
}

__STATIC__ __INLINE__ unsigned long int _ror_v5(unsigned long int data,
	unsigned long int shift)
{
	return((data << -shift) | (data >> shift));
}

__STATIC__ __INLINE__ unsigned long int _ror_v6(unsigned long int data,
	unsigned long int shift)
{
	shift &= 0x1f;
	return(_lsl_v2(data, -shift) | _lsr_v2(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _ror_v7(unsigned long int data,
	unsigned long int shift)
{
	shift &= 0x1f;
	return(_lsl_v2(data, __SIZEOF_DATA__ - shift) | _lsr_v2(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _ror_v8(unsigned long int data,
	unsigned long int shift)
{
	return(_rol(data, -shift));
}

__STATIC__ __INLINE__ unsigned long int _ror_v9(unsigned long int data,
	unsigned long int shift)
{
	return(_lsl_v1(data, __SIZEOF_DATA__ - shift) | _lsr_v1(data, shift));
}

__STATIC__ __INLINE__ unsigned long int _ror_c(unsigned long int data,
	unsigned long int shift,
	unsigned long int cin,
	unsigned long int* cout)
{
	unsigned long int cmask = _lsl_v1(!!cin, (-shift) - 1);
	unsigned long int dout = _ror_v1(data, shift);

	if(cout)
		*cout = !!(dout & cmask);

	return((dout & ~cin) | cin);
}

__STATIC__ __INLINE__ unsigned long int _ror_c_v2(unsigned long int data,
	unsigned long int shift,
	unsigned long int cin,
	unsigned long int* cout)
{
	*cout = 0;

	if(shift) {
		unsigned long int bits = __SIZEOF_DATA__;
		unsigned long int cbit = bits - shift;
		
		unsigned long int lhs = _lsl(data, 1 + cbit);
		unsigned long int rhs = _lsr_c(data, shift, cout);
		unsigned long int ccc = _lsl((cin ? 1 : 0), cbit);

//		if(0) LOG("cin = 0x%08lx -- 0x%08lx, 0x%08lx, 0x%08lx -- cout = 0x%08lx", cin, lhs, ccc, rhs, *cout);

		return(lhs | ccc | rhs);
	} else
		return(data);
}
