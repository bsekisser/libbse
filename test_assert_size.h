#pragma once

/* **** */

#include <assert.h>
#include <endian.h>
#include <stddef.h>
#include <stdio.h>

/* **** */

#undef STRINGIFY
#define STRINGIFY(_x) #_x

#undef __test_assert_size
#if 1
	#define __test_assert_size(_test) \
		{ \
			if((_test)) { \
				printf("%s -- size = 0x%08zx", STRINGIFY(_test), size); \
				assert((_test)); \
			} \
		}
#endif
