#include "callback_qlist.h"

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

#ifndef DEBUG
	#define DEBUG(_x)
#endif

/* **** */

static void _callback_qlist_init(callback_qlist_p cbl, unsigned int type)
{
	if(!type)
		LOG_ACTION(abort());

	cbl->count = 0;
	cbl->head = 0;
	cbl->tail = 0;
	cbl->type = type;

	DEBUG(LOG_START("-->> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(_LOG_(", count = 0x%08x", cbl->count));
	DEBUG(LOG_END(", type = 0x%08x", cbl->type));
}

static void _register_callback_fifo(callback_qlist_p cbl,
	callback_qlist_elem_p cble)
{
	DEBUG(LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(LOG_END(", count = 0x%08x", cbl->count));

	cble->next = 0;
	cble->prev = cbl->tail;

	if(cbl->tail)
		cbl->tail->next = cble;

	if(!cbl->head)
		cbl->head = cble;

	cbl->tail = cble;

	cbl->count++;
	DEBUG(LOG_START("-- cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(LOG_END(", count = 0x%08x", cbl->count));

	DEBUG(LOG("<<"));
}

static void _register_callback_lifo(callback_qlist_p cbl,
	callback_qlist_elem_p cble)
{
	DEBUG(LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(LOG_END(", count = 0x%08x", cbl->count));

	cble->next = cbl->head;
	cble->prev = 0;
	
	if(cbl->head)
		cbl->head->prev = cble;
	
	cbl->head = cble;

	if(!cbl->tail)
		cbl->tail = cble;

	cbl->count++;
	DEBUG(LOG_START("-- cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(LOG_END(", count = 0x%08x", cbl->count));

	DEBUG(LOG("<<"));
}

/* **** */

void callback_qlist_init(callback_qlist_p cbl, unsigned int type)
{
	_callback_qlist_init(cbl, type);
}

void callback_qlist_alloc_init(callback_qlist_h h2cbl, unsigned int type)
{
	callback_qlist_p cbl = handle_calloc((void**)h2cbl, 1, sizeof(callback_qlist_t));
	ERR_NULL(cbl);

	_callback_qlist_init(cbl, type);
}

void callback_qlist_process(callback_qlist_p cbl)
{
	DEBUG(LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	DEBUG(LOG_END(", count = 0x%08x", cbl->count));
	
	callback_qlist_elem_p cble = cbl->head;
	if(!cble)
		return;
	
	DEBUG(unsigned i = 0);
	do{
		DEBUG(LOG_START("-- cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
		DEBUG(_LOG_(", cble = 0x%08" PRIxPTR, (uintptr_t)cble));
		DEBUG(_LOG_(", count = 0x%08x", cbl->count));
		DEBUG(LOG_END(", i = 0x%08x", i++));

		if(cble->fn)
			cble->fn(cble->param);
		
		cble = cble->next;
	}while(cble);

	DEBUG(LOG("<<"));
}

void callback_qlist_register_callback(callback_qlist_p cbl,
	callback_qlist_elem_p cble)
{
	assert(0 != cbl);
	assert(0 != cbl->type);
	assert(0 != cble);

	switch(cbl->type) {
		case LIST_FIFO:
			_register_callback_fifo(cbl, cble);
			break;
		case LIST_LIFO:
			_register_callback_lifo(cbl, cble);
			break;
		default:
			LOG_ACTION(exit(-1));
	}
}
