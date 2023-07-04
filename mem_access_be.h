#pragma once

/* **** */

static inline unsigned mem_16be_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : htobe16(*(uint16_t*)p2pat);

	if(write)
		*(uint16_t*)p2pat = be16toh(data);

	return(data);
}

static unsigned mem_32be_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : htobe32(*(uint32_t*)p2pat);

	if(write)
		*(uint32_t*)p2pat = be32toh(data);

	return(data);
}

static inline unsigned mem_64be_access(void* p2pat, unsigned* write) {
	const unsigned data = write ? *write : htobe64(*(uint64_t*)p2pat);

	if(write)
		*(uint64_t*)p2pat = be64toh(data);

	return(data);
}

static inline unsigned mem_access_be(void* p2pat, size_t size, unsigned* write) {
	switch(size) {
		case 8:
			return(mem_64be_access(p2pat, write));
		case 4:
			return(mem_32be_access(p2pat, write));
		case 2:
			return(mem_16be_access(p2pat, write));
		case 1:
			return(mem_8_access(p2pat, write));
		default:
			abort();
			break;
	}

	return(0);
}
