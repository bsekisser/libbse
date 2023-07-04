#pragma once

/* **** */

#include <assert.h>

/* **** */

static inline unsigned mem_16le_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : htole16(*(uint16_t*)p2pat);

	if(write)
		*(uint16_t*)p2pat = le16toh(data);

	return(data);
}

static unsigned mem_32le_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : htole32(*(uint32_t*)p2pat);

	if(write)
		*(uint32_t*)p2pat = le32toh(data);

	return(data);
}

static inline unsigned mem_64le_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : htole64(*(uint64_t*)p2pat);

	if(write)
		*(uint64_t*)p2pat = le64toh(data);

	return(data);
}

#define STRINGIFY(_x) #_x
#define _assert(_test) \
	{ \
		if((_test)) { \
			printf("%s -- size = 0x%08zx", STRINGIFY(_test), size); \
			assert((_test)); \
		} \
	}

static inline unsigned mem_0x0le__access_read(void* p2src, size_t size) {
	_assert(sizeof(unsigned) <= size);

	uint32_t res = 0;
	uint8_t* src = (uint8_t*)p2src;

	for(unsigned i = 0; i < size; i++)
		res |= ((*src++) << (i << 3));

	return(res);
}	

static inline void mem_0x0le__access_write(void* p2dst, size_t size, uint32_t data) {
	_assert(sizeof(unsigned) <= size);

	uint8_t* dst = (uint8_t*)p2dst;

	for(unsigned i = 0; i < size; i++)
		*dst++ = (data >> (i << 3)) & 0xff;
}

static inline unsigned mem_0x0le_access(void* p2pat, size_t size, unsigned* write) {
	const unsigned data = write ? *write : mem_0x0le__access_read(p2pat, size);

	if(write)
		mem_0x0le__access_write(p2pat, size, data);

	return(data);
}

static inline unsigned mem_access_le(void* p2pat, size_t size, unsigned* write) {
	switch(size) {
		case 8:
			return(mem_64le_access(p2pat, write));
		case 4:
			return(mem_32le_access(p2pat, write));
		case 2:
			return(mem_16le_access(p2pat, write));
		default:
			return(mem_0x0le_access(p2pat, size, write));
	}

	return(0);
}
