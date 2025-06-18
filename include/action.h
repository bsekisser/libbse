#pragma once

/* **** */

#include "log.h"

/* **** */

typedef enum action_enum {
	_ACTION_INVALID,
	_ACTION_ALLOC,
	_ACTION_ALLOC_INIT,
	_ACTION_EXIT,
	_ACTION_INIT,
	_ACTION_LINK,
	_ACTION_PAUSE,
	_ACTION_PAUSE_CHECK,
	_ACTION_RESET,
	_ACTION_RESUME,
	_ACTION_STOP,
//
	__ACTION_COUNT_,
}action_enum;
typedef enum action_enum const action_ref;

typedef struct action_log_tag {
	union {
		unsigned raw_flags;
		struct {
			unsigned alloc:1;
			unsigned alloc_init:1;
			unsigned exit:1;
			unsigned init:1;
			unsigned reset:1;
			unsigned stop:1;
		}at;
	};
}action_log_t;

extern action_log_t action_log;

typedef int (*action_handler_fn)(int err, void *const param, action_ref action);

typedef struct action_handler_tag* action_handler_ptr;
typedef action_handler_ptr const action_handler_ref;

typedef struct action_linklist_tag* action_linklist_ptr;
typedef action_linklist_ptr const action_linklist_ref;

typedef struct action_list_tag* action_list_ptr;
typedef action_list_ptr const action_list_ref;

typedef struct action_handler_tag {
	union {
		action_handler_fn fn;
		action_list_ref list;
	};
	struct {
		unsigned dereference:1;
		unsigned is_list:1;
	};
	int param_offset;
}action_handler_t;

typedef struct action_linklist_tag {
	int member_offset;
	void* fn;
}action_linklist_t;

typedef struct action_list_tag {
	action_linklist_ref link;
	action_handler_t list[__ACTION_COUNT_];
	const void *const self;
	action_handler_ref sublist;
	const char *const sublist_name;
	const char *const name;
}action_list_t;

#define ACTION_LIST(_x, ...) action_list_t _x = { .name = #_x, ##__VA_ARGS__ }
#define SUBLIST(_x) .sublist = _x, .sublist_name = #_x

int action_handler(int err, void *const param, action_ref action, action_list_ref action_list);

#define ACTION_LOG(_x, ...) \
	({ if(action_log.at._x) LOG(__VA_ARGS__); })
