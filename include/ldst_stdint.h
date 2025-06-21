#pragma once

/* **** */

#include <stddef.h>
#include <stdint.h>

/* **** */

typedef void* (*ldst_stdint_fn)(void* *const p, size_t size);

/* **** */

static inline
void* _ldst_ea(void* *const p, const size_t size, ldst_stdint_fn fn)
{ return(fn ? fn(p, size) : *p); }

static inline
void* ldst_ia(void* *const p, const size_t size)
{
	void *const ea = *p;
	*p += size;

	return(ea);
}

/* **** */

static inline
uint16_t uint16le(void* *const p, ldst_stdint_fn fn)
{ return(le16toh(*(uint16_t*)_ldst_ea(p, sizeof(uint16_t), fn))); }

static inline
uint32_t uint32le(void* *const p, ldst_stdint_fn fn)
{ return(le32toh(*(uint32_t*)_ldst_ea(p, sizeof(uint32_t), fn))); }
