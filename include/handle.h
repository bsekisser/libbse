#pragma once

/* **** */

#include "err_test.h"
#include "log.h"

/* **** */

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* **** */

#define _DEBUG 0
#include "debug.h"

/* **** */

static inline
void* _handle_calloc(void *const h0, void* *const p0)
{
	STDERR_NULL(p0);

	void** *const p = (void***)&p0[1];
	*p0 = h0;

	if(h0) *(void**)h0 = p;

	DEBUG(
		LOG_START("h0: 0x%016" PRIxPTR, (uintptr_t)h0);
		_LOG_("->(p = 0x%016" PRIxPTR ")", (uintptr_t)p);
		LOG_END(", p0: 0x%016" PRIxPTR, (uintptr_t)p0);
	);

	return(p);
}

static inline
void* handle_calloc(void *const h0, const size_t nmemb, const size_t size)
{
	void* *const p0 = (void**)calloc(nmemb, sizeof(void*) + (nmemb * size));

	return(_handle_calloc(h0, p0));
}

static inline
void* handle_malloc(void *const h0, const size_t size)
{
	void* *const p0 = (void**)malloc(sizeof(void*) + size);

	return(_handle_calloc(h0, p0));
}

static inline
void handle_ptrfree(void *const p)
{
	if(!p) return;

	void* *const p0 = &((void**)p)[-1];

	void* *const h0 = (void**)*p0;

	DEBUG(
		LOG_START("h0: 0x%016" PRIxPTR, (uintptr_t)h0);
		_LOG_("->(p = 0x%016" PRIxPTR ")", (uintptr_t)p);
		LOG_END(", p0: 0x%016" PRIxPTR, (uintptr_t)p0);
	);

	if(h0) {
		DEBUG(LOG("*h0: 0x%016" PRIxPTR, (uintptr_t)*h0));
		if(*h0 == p) {
			free(p0);
			*h0 = 0;
		}
	}
}
