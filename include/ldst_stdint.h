#pragma once

/* **** */

#include <stddef.h>
#include <stdint.h>

/* **** */

typedef void* (*ldst_stdint_fn)(void* *const p, size_t size);

/* **** */

static inline
void* ldst_ia(void* *const p, size_t size)
{
	void *const ea = *p;
	*p += size;

	return(ea);
}

/* **** */

static inline
uint16_t uint16le(void* *const p, ldst_stdint_fn fn)
{
	uint16_t *const ea = fn ? fn(p, sizeof(uint16_t)) : *p;

	return(le16toh(*ea));
}

static inline
uint32_t uint32le(void* *const p, ldst_stdint_fn fn)
{
	uint32_t *const ea = fn ? fn(p, sizeof(uint32_t)) : *p;

	return(le32toh(*ea));
}
