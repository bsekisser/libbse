#include "callback_qlist.h"

/* **** */

#include "err_test.h"
#include "handle.h"
#include "log.h"
#include "unused.h"

/* **** */

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* **** */

#define _DEBUG 0
#include "debug.h"

/* **** */

static const char* callback_qlist_type[_LIST_TYPE_COUNT] = {
	[LIST_NULL] = "XXX",
	[LIST_FIFO] = "FIFO",
	[LIST_LIFO] = "LIFO",
};

/* **** */

static void _callback_qlist_init(callback_qlist_ref cbl, const unsigned int type)
{
	ERR_NULL(cbl);

	if(!type)
		LOG_ACTION(abort());

	cbl->count = 0;

	ERR_IF(cbl->head);
	cbl->head = 0;

	ERR_IF(cbl->tail);
	cbl->tail = 0;

	cbl->type = type;

	DEBUG(
		LOG_START("-->> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl);
		_LOG_(", count = 0x%08x", cbl->count);
		LOG_END(", type = 0x%08x -- %s", cbl->type, callback_qlist_type[cbl->type])
	);

	UNUSED(callback_qlist_type); /* squelch warning when not debugging */
}

static void _register_callback_fifo(callback_qlist_ref cbl,
	callback_qlist_elem_ref cble)
{
	DEBUG(
		LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl);
		_LOG_(", cble = 0x%08" PRIxPTR, (uintptr_t)cble);
		LOG_END(", count = 0x%08x", cbl->count)
	);

	cble->next = 0;
	cble->prev = cbl->tail;

	if(cbl->tail) {
		ERR_IF(cbl->tail->next);
		cbl->tail->next = cble;
	}

	if(!cbl->head)
		cbl->head = cble;

	cbl->tail = cble;

	cbl->count++;
	DEBUG(
		LOG_START("<< cbl = 0x%08" PRIxPTR, (uintptr_t)cbl);
		LOG_END(", count = 0x%08x", cbl->count)
	);
}

static void _register_callback_lifo(callback_qlist_ref cbl,
	callback_qlist_elem_ref cble)
{
	DEBUG(
		LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl);
		_LOG_(", cble = 0x%08" PRIxPTR, (uintptr_t)cble);
		LOG_END(", count = 0x%08x", cbl->count)
	);

	cble->next = cbl->head;
	cble->prev = 0;

	if(cbl->head) {
		ERR_IF(cbl->head->prev);
		cbl->head->prev = cble;
	}

	cbl->head = cble;

	if(!cbl->tail)
		cbl->tail = cble;

	cbl->count++;
	DEBUG(
		LOG_START("<< cbl = 0x%08" PRIxPTR, (uintptr_t)cbl);
		LOG_END(", count = 0x%08x", cbl->count)
	);
}

/* **** */

void callback_qlist_init(callback_qlist_ref cbl, const unsigned int type)
{
	_callback_qlist_init(cbl, type);
}

void callback_qlist_alloc_init(callback_qlist_href h2cbl, const unsigned int type)
{
	callback_qlist_ref cbl = handle_calloc(h2cbl, 1, sizeof(callback_qlist_t));
	STDERR_NULL(cbl);

	_callback_qlist_init(cbl, type);
}

void callback_qlist_ptrrocess(callback_qlist_ref cbl)
{
	ERR_NULL(cbl);

	DEBUG(
		LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl);
		LOG_END(", count = 0x%08x", cbl->count);
	);

	callback_qlist_elem_ptr cble = 0;
	callback_qlist_elem_ptr next = cbl->head;

	unsigned i = 0;
	while(next) {
		cble = next;
		next = cble->next;

		DEBUG(
			LOG_START("-- cbl = 0x%08" PRIxPTR, (uintptr_t)cbl);
			_LOG_(", cble = 0x%08" PRIxPTR, (uintptr_t)cble);
			_LOG_(", count = 0x%08x", cbl->count);
			LOG_END(", i = 0x%08x", i++)
		);

		if(cble->fn)
			cble->fn(cble->param);
	};

	DEBUG(LOG("<<"));
}

void callback_qlist_ptrrocess_singleton_list(callback_qlist_ref cbl)
{
	ERR_NULL(cbl);

	DEBUG(
		LOG_START(">> cbl = 0x%08" PRIxPTR, (uintptr_t)cbl);
		LOG_END(", count = 0x%08x", cbl->count)
	);

	callback_qlist_elem_ptr cble = 0;
	callback_qlist_elem_ptr next = cbl->head;

	unsigned i = 0;
	while(next) {
		cble = next;
		next = cble->next;

		cbl->head = next;
		cble->next = 0;

		DEBUG(
			LOG_START("-- cbl = 0x%08" PRIxPTR, (uintptr_t)cbl);
			_LOG_(", cble = 0x%08" PRIxPTR, (uintptr_t)cble);
			_LOG_(", count = 0x%08x", cbl->count);
			LOG_END(", i = 0x%08x", i++)
		);

		if(cble->fn)
			cble->fn(cble->param);
	};

	if(!next)
		cbl->tail = next;

	DEBUG(LOG("<<"));
}

void callback_qlist_register_callback(callback_qlist_ref cbl,
	callback_qlist_elem_ref cble)
{
	ERR_NULL(cbl);
	if(0 == cbl->type) {
		DEBUG(LOG("-- cbl = 0x%08" PRIxPTR, (uintptr_t)cbl));
	}

	assert(0 != cbl->type);

	ERR_NULL(cble);

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
