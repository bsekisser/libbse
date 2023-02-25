#include "callback_list.h"

/* **** */

#include "log.h"

/* **** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* **** */

//#define DEBUG(_x) _x
#define DEBUG(_x)

static callback_list_elem_p __callback_get(callback_list_p cbl, int index)
{
	return(&cbl->cble[index]);
}

static void __callback_set(callback_list_p cbl, callback_fn fn, void* param, int index)
{
	callback_list_elem_p cble = __callback_get(cbl, index);
	
	cble->fn = fn;
	cble->param = param;
}

static void __callback_move(callback_list_p cbl, int from, int to)
{
	callback_list_elem_p cble = __callback_get(cbl, from);
	
	__callback_set(cbl, cble->fn, cble->param, to);
}

/* **** */

static void _register_callback_fifo(callback_list_p cbl, callback_fn fn, void* param)
{
	if(cbl->count >= cbl->limit)
		LOG_ACTION(abort());

	DEBUG(LOG(">> cbl = 0x%08x, count = 0x%08x, limit = 0x%08x", cbl, cbl->count, cbl->limit));

	__callback_set(cbl, fn, param, cbl->count);
	cbl->count++;

	DEBUG(LOG("<< cbl = 0x%08x, count = 0x%08x, limit = 0x%08x", cbl, cbl->count, cbl->limit));
}

static void _register_callback_lifo(callback_list_p cbl, callback_fn fn, void* param)
{
	if(cbl->count >= (cbl->limit - 1))
		LOG_ACTION(abort());
		
	DEBUG(LOG(">> cbl = 0x%08x, count = 0x%08x, limit = 0x%08x", cbl, cbl->count, cbl->limit));

	for(int i = cbl->count; i >= 0; i--) {
	DEBUG(LOG("-- cbl = 0x%08x, count = 0x%08x, limit = 0x%08x, i = 0x%08x", cbl, cbl->count, cbl->limit, i));
		__callback_move(cbl, i, i + 1);
	}

	__callback_set(cbl, fn, param, 0);
	cbl->count++;

	DEBUG(LOG("<< cbl = 0x%08x, count = 0x%08x, limit = 0x%08x", cbl, cbl->count, cbl->limit));
}

/* **** */

void callback_list_init(callback_list_p cbl, int additional, int type)
{
	if(!type)
		LOG_ACTION(abort());

	size_t size = sizeof(callback_list_t);
	
	if(additional)
		size += sizeof(callback_list_elem_t);

	memset(cbl, 0, size);

	cbl->limit = __CALLBACK_LIST_COUNT + additional;
	cbl->type = type;
}

void callback_list_process(callback_list_p cbl)
{
	DEBUG(LOG(">> cbl = 0x%08x, count = 0x%08x, limit = 0x%08x", cbl, cbl->count, cbl->limit));
	
	for(int i = 0; i < cbl->count; i++) {
		callback_list_elem_p cble = &cbl->cble[i];

	DEBUG(LOG("-- cbl = 0x%08x, count = 0x%08x, limit = 0x%08x, i = 0x%08x", cbl, cbl->count, cbl->limit, i));

		if(cble->fn)
			cble->fn(cble->param);
	}

	DEBUG(LOG("<< cbl = 0x%08x, count = 0x%08x, limit = 0x%08x", cbl, cbl->count, cbl->limit));
}

void callback_list_register_callback(callback_list_p cbl, callback_fn fn, void* param)
{
	switch(cbl->type) {
		case LIST_FIFO:
			return(_register_callback_fifo(cbl, fn, param));
		case LIST_LIFO:
			return(_register_callback_lifo(cbl, fn, param));
		default:
			LOG_ACTION(abort());
	}
}
