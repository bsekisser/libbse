#pragma once

/* **** */

#include <stdint.h>

/* **** */

#undef __SHIFT_TYPE_SIGNED
#define __SHIFT_TYPE_SIGNED int32_t

#undef __SHIFT_TYPE_UNSIGNED
#define __SHIFT_TYPE_UNSIGNED uint32_t

#undef __SHIFT_BITSv
#define __SHIFT_BITSv 32

/* **** */

#include "shift_roll_functions.h"
