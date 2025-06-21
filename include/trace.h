#pragma once

typedef struct trace_tag* trace_ptr;
typedef trace_ptr const trace_ref;

typedef struct trace_tag {
    char* file;
    char* function;
    int line;
}trace_t;

#define TRACE(_f, ...) \
    { \
	trace_t trace; \
	TRACE_T_TRACE(TRACE_T(), _f, ##__VA_ARGS__); \
    }

static
trace_ptr _trace_enter(trace_ref trace, const char *const file, const char *const function, const int line)
{
    trace->file = (char*)file;
    trace->function = (char*)function;
    trace->line = (int)line;
    return(trace);
}

#define TRACE_T() \
    _trace_enter(&trace, __FILE__, __func__, __LINE__ )

#define TRACE_T_TRACE(_trace, _f, ...) \
    { \
	printf("%s:%s:@%06u: " _f "\n", _trace->file, _trace->function, _trace->line, ##__VA_ARGS__); \
    }

#define TRACE_IF_ABORT(_test) \
    { \
	if(_test) \
	    TRACE("%s", #_test); \
    }
