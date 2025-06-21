#pragma once

/* **** */

#include "bitfield.h"
#include "log.h"

/* **** */

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

/* **** */

//#define DEBUG_IF_ELSE(_if, _else) _if
#ifndef DEBUG_IF_ELSE
	#define DEBUG_IF_ELSE(_if, _else) _else
#endif

#ifndef __INLINE__
	#define __INLINE__ inline
#endif

#ifndef __STATIC__
	#define __STATIC__ static
#endif

#ifdef __int128_t__
__STATIC__ __INLINE__
unsigned mem_128_access(void *const p2pat, const unsigned *const write) {
	if(write)
		*(uint128_t*)p2pat = *write;

	return(write ? *write : *p2pat);
}
#endif

__STATIC__ __INLINE__
unsigned mem_16_access(uint16_t *const p2pat, const unsigned *const write) {
	if(write)
		*p2pat = (uint16_t)*write;

	return(write ? *write : *p2pat);
}

__STATIC__ __INLINE__ int16_t mem_16i_access(int16_t *const p2pat, const unsigned *const write) {
	if(write)
		*p2pat = (int16_t)*write;

	return((int16_t)(write ? (int16_t)*write : *p2pat));
}

__STATIC__ __INLINE__
unsigned mem_32_access(uint32_t *const p2pat, const unsigned *const write) {
	if(write)
		*p2pat = *write;

	return(write ? *write : *p2pat);
}

__STATIC__ __INLINE__
unsigned mem_32i_access(int32_t *const p2pat, const unsigned *const write) {
	return(mem_32_access((uint32_t*)p2pat, write));
}

__STATIC__ __INLINE__
unsigned long long mem_64_access(uint64_t *const p2pat, const unsigned long long *const write) {
	if(write)
		*p2pat = *write;

	return(write ? *write : *p2pat);
}

__STATIC__ __INLINE__
unsigned mem_8_access(uint8_t *const p2pat, const unsigned *const write) {
	if(write)
		*p2pat = (uint8_t)*write;

	return(write ? *write : *p2pat);
}

/* **** */

__STATIC__ __INLINE__
unsigned mem_access(void *const p2pat, const size_t size, const unsigned *const write) {
	switch(size) {
#ifdef __int128_t__
		case 16:
			return(mem_128_access(p2pat, write));
#endif
#ifdef __int64_t__
		case 8:
			return(mem_64_access(p2pat, write));
#endif
		case 4:
			return(mem_32_access(p2pat, write));
		case 2:
			return(mem_16_access(p2pat, write));
		case 1:
			return(mem_8_access(p2pat, write));
		default:
			abort();
			break;
	}

	return(0);
}

/* **** */

#define _02u_(_x) #_x ": %02u", _x
#define _x08x_(_x) #_x ": 0x%08x", _x

#define LOG_02u_(_x) _LOG_(_02u_(_x))
#define LOG_x08x_(_x) _LOG_(_x08x_(_x))

#define _LOG_02u_(_x) _LOG_(", " _02u_(_x))
#define _LOG_x08x_(_x) _LOG_(", " _x08x_(_x))

__STATIC__ __INLINE__
int32_t mem_32ix_access(int32_t *const p2pat, const unsigned offset, const size_t size, const unsigned *const write) {
	const unsigned data_read = (unsigned)mem_32i_access(p2pat, 0);
	const unsigned offset_bits = offset << 3;
	const unsigned size_bits = size << 3;

	if(DEBUG_IF_ELSE(1, 0)) {
		LOG_START();
		LOG_x08x_(data_read);
		_LOG_02u_(offset_bits);
		_LOG_02u_(size_bits);
		LOG_END();
	}

	if(write) {
		const unsigned rmw_data_write = pbBFINS(data_read, *write, offset_bits, size_bits);

		if(DEBUG_IF_ELSE(1, 0)) {
			LOG_START();
			LOG_x08x_(rmw_data_write);
			LOG_END();
		}

		return((int32_t)mem_32i_access(p2pat, &rmw_data_write));
	}

	return((int32_t)pbBFEXT(data_read, offset_bits, size_bits));
}

__STATIC__ __INLINE__
unsigned mem_32x_access(uint32_t *const p2pat, const unsigned offset, const size_t size, const unsigned *const write) {
	const unsigned data_read = mem_32_access(p2pat, 0);
	const unsigned offset_bits = offset << 3;
	const unsigned size_bits = size << 3;

	if(DEBUG_IF_ELSE(1, 0)) {
		LOG_START();
		LOG_x08x_(data_read);
		_LOG_02u_(offset_bits);
		_LOG_02u_(size_bits);
		LOG_END();
	}

	if(write) {
		const unsigned rmw_data_write = pbBFINS(data_read, *write, offset_bits, size_bits);

		if(DEBUG_IF_ELSE(1, 0)) {
			LOG_START();
			LOG_x08x_(rmw_data_write);
			LOG_END();
		}

		return(mem_32_access(p2pat, &rmw_data_write));
	}

	return(pbBFEXT(data_read, offset_bits, size_bits));
}
