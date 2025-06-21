#pragma once

/* **** */

#include "log.h"

/* **** */

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* **** */

#define ERR_LOG(_f, ...) \
	{ \
		LOG("%s:: %s:: %04u::" _f, \
			__FILE__, \
			__func__, \
			__LINE__, ##__VA_ARGS__); \
	}

#define _ERR_TEST_ABORT(_test) \
	{ \
		if((_test)) { \
			ERR_LOG("%s", #_test); \
			abort(); \
		} \
	}

#define ERR(_test) _ERR_TEST_ABORT(-1 == (_test))
#define ERR_IF(_test) _ERR_TEST_ABORT(_test)
#define ERR_NULL(_test) _ERR_TEST_ABORT(0 == (_test))

#define STDERR_LOG(_f, ...) \
	{ \
		LOG("%s:: %s:: %04u:: %s::" _f, \
			__FILE__, \
			__func__, \
			__LINE__, \
			strerror(errno), ##__VA_ARGS__); \
	}

#define _STDERR_TEST_ABORT(_test) \
	{ \
		if((_test)) { \
			STDERR_LOG("%s", #_test); \
			abort(); \
		} \
	}

#define STDERR(_test) _STDERR_TEST_ABORT(-1 == (_test))
#define STDERR_IF(_test) _STDERR_TEST_ABORT(_test)
#define STDERR_NULL(_test) _STDERR_TEST_ABORT(0 == (_test))

#define assert_abort_msg(_test, _msg, ...) \
	{ \
		int result = _test; \
		if(!result) { \
			ERR_LOG(_msg, ##__VA_ARGS__); \
			assert(_test); \
		} \
	}
