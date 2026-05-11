#pragma once

/* **** system includes */

#include <inttypes.h>
#include <stdio.h>

/* **** */

#define LOG_TRACE_START(_f, ...) \
	{ \
		printf("%s:%s:%04u: " _f, __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
	}

#define LOG_START(_f, ...) \
	{ \
		printf("%s:%04u: " _f, __func__, __LINE__, ##__VA_ARGS__); \
	}

#define _LOG_(_f, ...) \
	{ \
		printf(_f, ##__VA_ARGS__); \
	}

#define LOG_END(_f, ...) \
	{ \
		printf(_f "\n", ##__VA_ARGS__); \
	}

#define LOG(_f, ...) \
	{ \
		LOG_START(_f "\n", ##__VA_ARGS__); \
	}

#define LOG_ERR(_f, ...) \
	{ \
		fprintf(stderr, "%s:%04u: " _f "\n", __func__, __LINE__, ##__VA_ARGS__); \
	}

#define LOG_ACTION(_action) \
	{ \
		LOG("%s", #_action); \
		_action; \
	}


#define LOGp64(_x) LOG("%s: 0x%016" PRIxPTR, #_x, (uintptr_t)_x)
#define _LOGp64(_x) ({ typeof(_x) __x = _x; LOGp64(__x); __x; })
#define LOGu(_x) LOG("%s: %u", #_x, _x)
#define _LOGu(_x) ({ typeof(_x) __x = _x; LOGu(__x); __x; })
#define LOGx64(_x) LOG("%s: 0x%016" PRIx64, #_x, (uint64_t)_x)
#define _LOGx64(_x) ({ typeof(_x) __x = _x; LOGx64(__x); __x; })
#define LOGx32(_x) LOG("%s: 0x%08x", #_x, _x)
#define _LOGx32(_x) ({ typeof(_x) __x = _x; LOGx32(__x); __x; })
#define LOGzu(_x) LOG("%s: %zu", #_x, _x)
#define _LOGzu(_x) ({ typeof(_x) __x = _x; LOGzu(__x); __x; })
#define LOGzx32(_x) LOG("%s: 0x%08zx", #_x, _x)
#define _LOGzx32(_x) ({ typeof(_x) __x = _x; LOGzx32(__x); __x; })
