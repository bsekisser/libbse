#include "action.h"

/* **** */

#include "err_test.h"
#include "log.h"
#include "unused.h"

/* **** */

action_log_t action_log;

/* **** */

#define _DEBUG 0
#include "debug.h"

/* **** */

#include <inttypes.h>
#include <stdint.h>

/* **** */

static
int _action_handler(int err, void *const param, action_ref action, action_handler_ref handler, const char *const name)
{
	void* action_param = param + handler->param_offset;
	const unsigned is_list = handler->is_list;

	if(handler->dereference)
		action_param = *(void**)action_param;

	DEBUG(
		LOG_START("action: 0x%08x", action);
		_LOG_(", handler: 0x%016" PRIxPTR, (uintptr_t)handler);
		_LOG_(", action_param: 0x%016" PRIxPTR, (uintptr_t)action_param);
		_LOG_(", param: 0x%016" PRIxPTR, (uintptr_t)param);
		_LOG_(", is_list: %u", is_list);
		if(name) {
			LOG_END(" -- %s", name);
		} else {
			LOG_END();
		}
	);

	if(is_list)
		return(action_handler(err, action_param, action, handler->list));

	DEBUG(
		LOG("handler->fn: 0x%016" PRIxPTR, (uintptr_t)handler->fn);
	);

	if(!handler->fn) return(err);

	return(handler->fn(err, action_param, action));
	UNUSED(name); // debug use only
}

static
void _action_handler_link(void *const param, action_linklist_ptr link)
{
	if(!link) return;

	for(; link->fn; link++) {
		void* (*fn)(void) = link->fn;
		void* *const p = param + link->member_offset;

		*p = fn();

		DEBUG(
			LOG_START("((param: 0x%016" PRIxPTR, (uintptr_t)param);
			_LOG_(", offset: %08x), p: 0x%016" PRIxPTR, link->member_offset, (uintptr_t)p);
			LOG_END(", fn: 0x%016" PRIxPTR ")<-- 0x%016" PRIxPTR, (uintptr_t)fn, (uintptr_t)*p);
		);

		ERR_NULL(*p);
	}
}

int action_handler(int err, void *const param, action_ref action, action_list_ref action_list)
{
	action_handler_ref handler = &action_list->list[action];
	void *const handler_param = param + handler->param_offset;
	void* *const self = (void**)action_list->self;

	DEBUG(
		LOG_START("action_list: 0x%016" PRIxPTR, (uintptr_t)action_list);
		_LOG_(", handler: 0x%016" PRIxPTR, (uintptr_t)handler);
		_LOG_(", handler_param: 0x%016" PRIxPTR, (uintptr_t)handler_param);
		_LOG_(", (param: 0x%016" PRIxPTR ")", (uintptr_t)param);
		if(action_list->name) {
			LOG_END(" -- %s", action_list->name);
		} else {
			LOG_END();
		}
	);

	if(self) *self = param;

	switch(action) {
		case _ACTION_EXIT: break;
		case _ACTION_LINK: _action_handler_link(param, action_list->link); break;
		default: err |= _action_handler(err, handler_param, action, handler, 0); break;
	}

	action_handler_ref subhandler_list = action_list->sublist;
	if(subhandler_list) {
		for(action_handler_ptr subhandler = subhandler_list; subhandler->fn; subhandler++)
			err |= _action_handler(err, param, action, subhandler, action_list->sublist_name);
	}

	switch(action) {
		case _ACTION_EXIT: err |= _action_handler(err, handler_param, action, handler, 0); break;
		default: break;
	}

	if(self) *self = 0;

	return(err);
}
