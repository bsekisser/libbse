#pragma once

/* **** */

typedef enum action_enum {
	_ACTION_INVALID,
	_ACTION_ALLOC,
	_ACTION_ALLOC_INIT,
	_ACTION_EXIT,
	_ACTION_INIT,
	_ACTION_RESET,
	_ACTION_STOP,
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

#define ACTION_LOG(_x, ...) \
	({ if(action_log.at._x) LOG(__VA_ARGS__); })
