#pragma once

/* **** */

#include "test_assert_size.h"

#ifndef __test_assert_size
	#define __test_assert_size assert
#endif

/* **** */

#include <stddef.h>
#include <stdint.h>

/* **** */

static inline
unsigned mem_0x0le__access_read(void *const p2src, const size_t size) {
	__test_assert_size(sizeof(long) <= size);

	uint32_t res = 0;
	uint8_t* src = (uint8_t*)p2src;

	for(unsigned i = 0; i < size; i++)
		res |= ((*src++) << (i << 3));

	return(res);
}

static inline
void mem_0x0le__access_write(void *const p2dst, const size_t size, const uint32_t data) {
	__test_assert_size(sizeof(unsigned) <= size);

	uint8_t* dst = (uint8_t*)p2dst;

	for(unsigned i = 0; i < size; i++)
		*dst++ = (data >> (i << 3)) & 0xff;
}

static inline
unsigned mem_0x0le_access(void *const p2pat, const size_t size, const unsigned *const write) {
	const long data = write ? *write : mem_0x0le__access_read(p2pat, size);

	if(write)
		mem_0x0le__access_write(p2pat, size, data);

	return(data);
}

/* **** */

static inline
unsigned mem_16le_access(void *const p2pat, const unsigned *const write) {
	const uint16_t data = (uint16_t)(write ? *write : htole16(*(uint16_t*)p2pat));

	if(write)
		*(uint16_t*)p2pat = le16toh(data);

	return(data);
}

static
unsigned mem_32le_access(void *const p2pat, const unsigned *const write) {
	const long data = write ? *write : htole32(*(uint32_t*)p2pat);

	if(write)
		*(uint32_t*)p2pat = le32toh(data);

	return(data);
}

static inline
unsigned mem_64le_access(void *const p2pat, const unsigned *const write) {
	if(sizeof(unsigned) <= sizeof(uint64_t))
		return(mem_0x0le_access(p2pat, sizeof(uint64_t), write));

	const uint64_t data = (uint64_t)(write ? *write : htole64(*(uint64_t*)p2pat));

	if(write)
		*(uint64_t*)p2pat = le64toh(data);

	return((long)data);
}

/* **** */

static inline
unsigned mem_access_le(void *const p2pat, const size_t size, const unsigned *const write) {
	switch(size) {
//		case 8:
//			return(mem_64le_access(p2pat, write));
		case 4:
			return(mem_32le_access(p2pat, write));
		case 2:
			return(mem_16le_access(p2pat, write));
		default:
			return(mem_0x0le_access(p2pat, size, write));
	}

	return(0);
}
