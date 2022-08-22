#pragma once

typedef struct trace_t* trace_p;
typedef struct trace_t {
    char*				file;
    char*				function;
    int				line;
}trace_t;

#define TRACE(_f, _args...) \
    ({ \
	trace_t trace; \
	TRACE_T_TRACE(TRACE_T(), _f, ##_args); \
    })

static trace_p _trace_enter(trace_p trace, const char* file, const char* function, const int line)
{
    trace->file = (char*)file;
    trace->function = (char*)function;
    trace->line = (int)line;
    return(trace);
}

#define TRACE_T() \
    _trace_enter(&trace, __FILE__, __FUNCTION__, __LINE__ )
    
#define TRACE_T_TRACE(_trace, _f, _args...) \
    ({ \
	printf("%s:%s:@%06u: " _f "\n", _trace->file, _trace->function, _trace->line, ##_args); \
    })

#define TRACE_IF_ABORT(_test) \
    ({ \
	if(_test) \
	    TRACE("%s", #_test); \
    })
