/* **** */

#include "log.h"

/* **** */

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* **** */

#undef DEBUG
//#define DEBUG(_x) _x 
#define DEBUG(_x)

#define HANDLE_CALLOC(_h, _nmemb, _size) handle_calloc((void**)_h, _nmemb, _size)
static inline void* handle_calloc(void** h, size_t nmemb, size_t size) {
	if(0 == h) {
//		LOG_ACTION(return);
		LOG_ACTION(exit(-1));
	}

	void* p = calloc(nmemb, size);
	*h = p;

	DEBUG(LOG("h = 0x%08" PRIxPTR ", p = 0x%08" PRIxPTR ", nmemb = 0x%08zx, size = 0x%08zx",
		(uintptr_t)h, (uintptr_t)p, nmemb, size));

	return(p);
}

#define HANDLE_MALLOC(_h, _size) handle_malloc((void**)_h, _size)
static inline void* handle_malloc(void** h, size_t size) {
	if(0 == h) {
//		LOG_ACTION(return);
		LOG_ACTION(exit(-1));
	}

	void* p = malloc(size);
	*h = p;

	return(p);
}

#define HANDLE_FREE(_h) handle_free((void**)_h)
static inline void handle_free(void** h) {
	if(0 == h)
		LOG_ACTION(return);

	if(0 == *h)
		LOG_ACTION(return);

	free(*h);
	*h = 0;
}
