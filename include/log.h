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


#define _LOGv(_x, _log_action) \
	({ typeof(_x) __x = _x; _LOG_(_log_action(_x, __x)); _x; })

#define LOGv(_x, _log_action) \
	({ LOG_START(); _LOG_(_log_action(_x, _x)); LOG_END(); });

#define __LOGp64(_xs, _x) #_xs ": 0x%016" PRIxPTR, (uintptr_t)_x
#define __LOGu(_xs, _x) #_xs ": %u", _x
#define __LOGx64(_xs, _x) #_xs ": 0x%016" PRIx64, (uint64_t)_x
#define __LOGx32(_xs, _x) #_xs ": 0x%08x", _x
#define __LOGzu(_xs, _x) #_xs ": %zu", _x
#define __LOGzx32(_xs, _x) #_xs ": 0x%08zx", _x

#define LOGp64(_x) LOGv(_x, __LOGp64)
#define _LOGp64(_x) _LOGv(_x, __LOGp64)
#define LOGu(_x) LOGv(_x, __LOGu)
#define _LOGu(_x) _LOGv(_x, __LOGu)
#define LOGx64(_x) LOGv(_x, __LOGx64)
#define _LOGx64(_x) _LOGv(_x, __LOGx64)
#define LOGx32(_x) LOGv(_x, __LOGx32)
#define _LOGx32(_x) _LOGv(_x, __LOGx32);
#define LOGzu(_x) LOGv(_x, __LOGzu)
#define _LOGzu(_x) _LOGv(_x, __LOGzu)
#define LOGzx32(_x) LOGv(_x, __LOGzx32)
#define _LOGzx32(_x) _LOGv(_x, __LOGzx32)
