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
__STATIC__ __INLINE__ unsigned mem_128_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : *(uint128_t*)p2pat;

	if(write)
		*(uint128_t*)p2pat = data;

	return(data);
}
#endif

__STATIC__ __INLINE__ unsigned mem_16_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : *(uint16_t*)p2pat;

	if(write)
		*(uint16_t*)p2pat = data;

	return(data);
}

__STATIC__ __INLINE__ unsigned mem_32_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : *(uint32_t*)p2pat;

	if(write)
		*(uint32_t*)p2pat = data;

	return(data);
}

__STATIC__ __INLINE__ unsigned long long mem_64_access(void* p2pat, unsigned long long* write) {
	assert(sizeof(unsigned long long) >= sizeof(uint64_t));

	const unsigned long long data = write ? *write : *(uint64_t*)p2pat;

	if(write)
		*(uint64_t*)p2pat = data;

	return(data);
}

__STATIC__ __INLINE__ unsigned mem_8_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : *(uint8_t*)p2pat;

	if(write)
		*(uint8_t*)p2pat = data;

	return(data);
}

/* **** */

__STATIC__ __INLINE__ unsigned mem_access(void* p2pat, size_t size, unsigned* write) {
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

__STATIC__ __INLINE__ unsigned mem_32x_access(void* p2pat, unsigned offset, size_t size, unsigned* write) {
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
		unsigned rmw_data_write = pbBFINS(data_read, *write, offset_bits, size_bits);

		if(DEBUG_IF_ELSE(1, 0)) {
			LOG_START();
			LOG_x08x_(rmw_data_write);
			LOG_END();
		}

		return(mem_32_access(p2pat, &rmw_data_write));
	}

	return(pbBFEXT(data_read, offset_bits, size_bits));
}
