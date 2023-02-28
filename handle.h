#include <stdlib.h>

#define HANDLE_CALLOC(_h, _nmemb, _size) handle_calloc((void**)_h, _nmemb, _size)
static inline void* handle_calloc(void** h, size_t nmemb, size_t size) {
	if(0 == h)
		return(0);

	void* p = calloc(nmemb, size);
	*h = p;

	return(p);
}

#define HANDLE_MALLOC(_h, _size) handle_malloc((void**)_h, _size)
static inline void* handle_malloc(void** h, size_t size) {
	if(0 == h)
		return(0);

	void* p = malloc(size);
	*h = p;

	return(p);
}

#define HANDLE_FREE(_h) handle_free((void**)_h)
static inline void handle_free(void** h) {
	assert(0 != h);
	assert(0 != *h);

	free(*h);
	*h = 0;
}
