#include "action.h"

#include "log.h"

/* **** */

action_log_t action_log;

/* **** */

//#define DEBUG(_x) _x

#include "debug.h"

/* **** */

#include <inttypes.h>
#include <stdint.h>

/* **** */

int _action_handler(int err, void *const param, action_ref action, action_handler_ref handler, const int)
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
		_LOG_(", subhandler: %u", subhandler);
		LOG_END(", is_list: %u", is_list);
	);

	if(is_list)
		return(action_handler(err, action_param, action, handler->list));

	DEBUG(
		LOG("handler->fn: 0x%016" PRIxPTR, (uintptr_t)handler->fn);
	);

	if(!handler->fn) return(err);

	return(handler->fn(err, action_param, action));
}

int action_handler(int err, void *const param, action_ref action, action_list_ref action_list)
{
	action_handler_ref handler = &action_list->list[action];
	void *const handler_param = param + handler->param_offset;

	DEBUG(
		LOG_START("action_list: 0x%016" PRIxPTR, (uintptr_t)action_list);
		_LOG_(", handler: 0x%016" PRIxPTR, (uintptr_t)handler);
		_LOG_(", handler_param: 0x%016" PRIxPTR, (uintptr_t)handler_param);
		LOG_END(", (param: 0x%016" PRIxPTR ")", (uintptr_t)param);

	);

	switch(action) {
		case _ACTION_EXIT: break;
		default: err |= _action_handler(err, handler_param, action, handler, 0); break;
	}

	action_handler_ref subhandler_list = action_list->sublist;
	if(subhandler_list) {
		for(action_handler_ptr subhandler = subhandler_list; subhandler->fn; subhandler++)
			err |= _action_handler(err, param, action, subhandler, 1);
	}

	switch(action) {
		case _ACTION_EXIT: err |= _action_handler(err, handler_param, action, handler, 0); break;
		default: break;
	}

	return(err);
}
