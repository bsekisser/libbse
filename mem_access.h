#pragma once

#ifdef __int128_t__
static unsigned mem_128_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : *(uint128_t*)p2pat;

	if(write)
		*(uint128_t*)p2pat = data;

	return(data);
}
#endif

static unsigned mem_16_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : *(uint16_t*)p2pat;

	if(write)
		*(uint16_t*)p2pat = data;

	return(data);
}

static inline unsigned mem_16_access_endian(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : htole16(*(uint16_t*)p2pat);

	if(write)
		*(uint16_t*)p2pat = le16toh(data);

	return(data);
}


static unsigned mem_32_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : *(uint32_t*)p2pat;

	if(write)
		*(uint32_t*)p2pat = data;

	return(data);
}

static unsigned mem_32_access_endian(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : htole16(*(uint32_t*)p2pat);

	if(write)
		*(uint32_t*)p2pat = le32toh(data);

	return(data);
}

static unsigned mem_64_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : *(uint64_t*)p2pat;

	if(write)
		*(uint64_t*)p2pat = data;

	return(data);
}

static inline unsigned mem_64_access_endian(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : htole64(*(uint64_t*)p2pat);

	if(write)
		*(uint64_t*)p2pat = le64toh(data);

	return(data);
}

static unsigned mem_8_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : *(uint8_t*)p2pat;

	if(write)
		*(uint8_t*)p2pat = data;

	return(data);
}

/* **** */

static inline unsigned mem_access(void* p2pat, size_t size, unsigned* write) {
	switch(size) {
#ifdef __int128_t
		case 16:
			return(mem_128_access(p2pat, write));
#endif
		case 8:
			return(mem_64_access(p2pat, write));
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

static inline unsigned mem_access_endian(void* p2pat, size_t size, unsigned* write) {
	switch(size) {
		case 8:
			return(mem_64_access_endian(p2pat, write));
		case 4:
			return(mem_32_access_endian(p2pat, write));
		case 2:
			return(mem_16_access_endian(p2pat, write));
		case 1:
			return(mem_8_access(p2pat, write));
		default:
			abort();
			break;
	}

	return(0);
}
