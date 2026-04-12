#pragma once

#warning !! untested, tests not currently implemented.

/* **** */

#include <stdint.h>

/* **** */

#undef __BITOP_TYPE
#define __BITOP_TYPE uint64_t

#undef __BITOP_BITSv
#define __BITOP_BITSv 64

#include "bitop_functions.h"
