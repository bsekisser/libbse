#include "callback_list.h"

/* **** */

#include "err_test.h"
#include "handle.h"
#include "log.h"

/* **** */

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* **** */

#undef DEBUG
//#define DEBUG(_x) _x
#define DEBUG(_x)

static callback_list_elem_p __callback_get(callback_list_p cbl, unsigned int index)
{
	return(&cbl->cble[index]);
}

static void __callback_set(callback_list_p cbl,
	callback_fn fn, void* param, unsigned int index)
{
	callback_list_elem_p cble = __callback_get(cbl, index);
	
	cble->fn = fn;
	cble->param = param;
}

static void __callback_move(callback_list_p cbl,
	unsigned int from, unsigned int to)
{
	assert(from != to);
	assert(to < cbl->limit);

	callback_list_elem_p cble = __callback_get(cbl, from);
	
	__callback_set(cbl, cble->fn, cble->param, to);
}

/* **** */

static void _callback_list_init(callback_list_p cbl,
	unsigned int additional, unsigned int type)
{
	if(!type)
		LOG_ACTION(abort());

	if(0 == additional)
		memset(cbl, 0, sizeof(callback_list_t));

	cbl->limit = __CALLBACK_LIST_COUNT;
	cbl->limit += additional;
	cbl->type = type;

	DEBUG(LOG_START("-->> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(_LOG_(", additional = 0x%08x", additional));
	DEBUG(_LOG_(", count = 0x%08x", cbl->count));
	DEBUG(_LOG_(", limit = 0x%08x", cbl->limit));
	DEBUG(LOG_END(", type = 0x%08x", cbl->type));
}

static void _register_callback_fifo(callback_list_p cbl,
	callback_fn fn, void* param)
{
	if(cbl->count >= (cbl->limit - 1))
		LOG_ACTION(abort());

	DEBUG(LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(_LOG_(", count = 0x%08x", cbl->count));
	DEBUG(LOG_END(", limit = 0x%08x", cbl->limit));

	__callback_set(cbl, fn, param, cbl->count);
	cbl->count++;

	DEBUG(LOG("<<"));
}

static void _register_callback_lifo(callback_list_p cbl,
	callback_fn fn, void* param)
{
	if(cbl->count >= (cbl->limit - 1))
		LOG_ACTION(abort());
		
	DEBUG(LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(_LOG_(", count = 0x%08x", cbl->count));
	DEBUG(LOG_END(", limit = 0x%08x", cbl->limit));

	if(cbl->count) {
		unsigned int i = cbl->count;
		do {
			DEBUG(LOG_START("-- cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
			DEBUG(_LOG_(", count = 0x%08x", cbl->count));
			DEBUG(_LOG_(", limit = 0x%08x", cbl->limit));
			DEBUG(LOG_END(", i = 0x%08x", i));

			__callback_move(cbl, i, i + 1);
		}while(i--);
	}

	__callback_set(cbl, fn, param, 0);
	cbl->count++;

	DEBUG(LOG("<<"));
}

/* **** */

void callback_list_init(callback_list_p cbl,
	unsigned int additional, unsigned int type)
{
	assert(0 == additional);
	
	_callback_list_init(cbl, 0, type);
}

void callback_list_alloc_init(callback_list_h h2cbl,
	unsigned int additional, unsigned int type)
{
	size_t size = sizeof(callback_list_t);
	
	if(additional) {
		size_t additional_size = (additional + 1) * sizeof(callback_list_elem_t);
		
		DEBUG(LOG_START("size = 0x%08zx", size));
		DEBUG(LOG_END(", additional_size = 0x%08zx", additional_size));
		
		size += additional_size;
	}

	callback_list_p cbl = handle_calloc((void**)h2cbl, 1, size);
	ERR_NULL(cbl);

	_callback_list_init(cbl, additional, type);
}

void callback_list_process(callback_list_p cbl)
{
	DEBUG(LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(_LOG_(", count = 0x%08x", cbl->count));
	DEBUG(LOG_END(", limit = 0x%08x", cbl->limit));
	
	for(unsigned int i = 0; i < cbl->count; i++) {
		callback_list_elem_p cble = &cbl->cble[i];

	DEBUG(LOG_START("-- cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(_LOG_(", cble = 0x%08" PRIxPTR, (uintptr_t)cble));
	DEBUG(_LOG_(", count = 0x%08x", cbl->count));
	DEBUG(_LOG_(", limit = 0x%08x", cbl->limit));
	DEBUG(LOG_END(", i = 0x%08x", i));

		if(cble->fn)
			cble->fn(cble->param);
	}

	DEBUG(LOG("<<"));
}

void callback_list_register_callback(callback_list_p cbl,
	callback_fn fn, void* param)
{
	assert(0 != cbl);
	assert(0 != cbl->type);
	
	switch(cbl->type) {
		case LIST_FIFO:
			_register_callback_fifo(cbl, fn, param);
			break;
		case LIST_LIFO:
			_register_callback_lifo(cbl, fn, param);
			break;
		default:
			LOG_ACTION(exit(-1));
	}
}
