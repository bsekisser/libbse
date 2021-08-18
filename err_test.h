#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LOG(_f, ...) \
    do { \
	    printf("%s:%04u: " _f "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }while(0)

#define LOG_ACTION(_action) \
    do { \
	LOG("%s", #_action); \
	_action; \
    }while(0);

#define _ERR(_test) \
    do { \
	if((_test)) \
	{ \
	    LOG("%s:: %s:: %04u:: %s", \
		__FILE__, \
		__FUNCTION__, \
		__LINE__, \
		strerror(errno)); \
	    abort(); \
	} \
    }while(0)

#define ERR(_test) _ERR(-1 == (_test))
#define ERR_NULL(_test) _ERR(0 == (_test))

#define assert_abort(_test) _ERR(_test)

#define assert_abort_msg(_test, _f, ...) \
    do { \
	if((_test)) \
	{ \
	    LOG(_f, ##__VA_ARGS__); \
	    abort(); \
	} \
    }while(0)

#define ucs_assert_err(_ucs, _expect, _test) \
    do { \
	_ucs ## _err __err = (_test); \
	assert_abort_msg(__err != _expect, "%s", _ucs ## _strerror(__err)); \
    }while(0)

#define cs_assert_success(_err)  ucs_assert_err(cs, CS_ERR_OK, _err)
#define uc_assert_success(_err)  ucs_assert_err(uc, UC_ERR_OK, _err)

#define OK(x)   uc_assert_success(x)
