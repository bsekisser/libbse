#pragma once

/* **** system includes */

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
