#pragma once

/* **** */

#include <stdint.h>

/* **** */

typedef signed shift_type_st;
typedef unsigned shift_type_ut;

#define __SHIFT_BITSv

#define asr _asr
#define lsl _lsl
#define lsr _lsr
#define rol _rol
#define ror _ror
#define _rrx_c(_v) rrx_c(_v, 0)
#define _rrx_v(_v, _co) rrx_v(_v, _co)

#include "shift_roll_x.h"
