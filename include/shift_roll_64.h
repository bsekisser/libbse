#pragma once

/* **** */

#include <stdint.h>

/* **** */

#undef __SHIFT_TYPE_SIGNED
#define __SHIFT_TYPE_SIGNED int64_t

#undef __SHIFT_TYPE_UNSIGNED
#define __SHIFT_TYPE_UNSIGNED uint64_t

#undef __SHIFT_BITSv
#define __SHIFT_BITSv 64

/* **** */

#include "shift_roll_functions.h"
